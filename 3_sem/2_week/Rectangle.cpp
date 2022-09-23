#include <iostream>
#include <cmath>
#include <stack>


struct Point {
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y) :
            x(x), y(y) {}

    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const {
        std::cout << '(' << x << ',' << y << ')';
    }
};


class Rectangle {
private:
    Point *rha;
public:
    Rectangle() : rha((new Point(0, 0))) {}

    Rectangle(Point &rha) : rha(&rha) {}

    Rectangle operator+(Rectangle const &rh) {
        return Rectangle(*(new Point(rha->maxx(*rh.rha).x, rha->maxy(*rh.rha).y)));
    }

    Rectangle operator*(Rectangle const &rh) {
        return Rectangle(*(new Point(rha->minx(*rh.rha).x, rha->miny(*rh.rha).y)));
    }

    void print() {
        std::cout << '(' << rha->x << ',' << rha->y << ')' << std::endl;
    }
};

Rectangle *create_rect(int x, int y) {
    return new Rectangle(*(new Point(x, y)));
}

int slice_string(std::basic_string<char> string, int begin, int *coordinates, int num, int base_condition) {
    if (num >= base_condition)
        return 0;
    while (string[begin] < '0' or string[begin] > '9') {
        ++begin;
    }
    int end = begin;
    while (string[end] >= '0' and string[end] <= '9') {
        ++end;
    }
    int point_coordinate = 0;
    for (int j = 0; j < end - begin; ++j) {
        point_coordinate += ((int) (string[end - j - 1]) - 48) * pow(10, j);
    }
    coordinates[num] = point_coordinate;
    slice_string(string, ++end, coordinates, ++num, base_condition);
}

int main() {
    std::string expression;
    std::getline(std::cin, expression);

    int sign_num = 0;
    for (int i = 0; i < expression.size(); ++i) {
        if (expression[i] == '+' or expression[i] == '*')
            ++sign_num;
    }
    char *signs = new char[sign_num];
    int *coord = new int[2 * (sign_num + 1)];

    int j = 0;
    for (int i = 0; i < expression.size(); ++i) {
        if (expression[i] == '+' or expression[i] == '*') {
            signs[j] = expression[i];
            ++j;
        }
    }

    slice_string(expression, 0, coord, 0, 2 * (sign_num + 1));

    auto *sum_stack = new std::stack<Rectangle>;
    auto *num_stack = new std::stack<int>;
    for (int i = 0; i < sign_num; ++i) {
        if (signs[i] == '*') {
            int begin = i;
            ++i;
            while (signs[i] == '*') {
                ++i;
            }
            Rectangle rect_1 = *(create_rect(coord[2 * begin], coord[2 * begin + 1]));
            num_stack->push(2 * begin);
            for (int k = ++begin; k < i + 1; ++k) {
                Rectangle rect_2 = *(create_rect(coord[2 * k], coord[2 * k + 1]));
                rect_1 = rect_1.operator*(rect_2);
                num_stack->push(2 * k);
            }
            sum_stack->push(rect_1);
        }
    }

    int *num_massive = new int[num_stack->size()];
    int num_stack_size = num_stack->size();

    for (int i = 0; i < num_stack_size; ++i) {
        num_massive[i] = num_stack->top();
        num_stack->pop();
    }
    int sum_stack_size = sum_stack->size();
    Rectangle answer = *(create_rect(0, 0));
    for (int i = 0; i < sum_stack_size; ++i) {
        answer = answer.operator+(sum_stack->top());
        sum_stack->pop();
    }

    for (int i = 0; i <= sign_num; ++i) {
        bool is_mul = false;
        for (int k = 0; k < num_stack_size; ++k) {
            if (num_massive[k] == 2 * i)
                is_mul = true;
        }
        if (is_mul)
            continue;
        Rectangle rect_2 = *(create_rect(coord[2 * i], coord[2 * i + 1]));
        answer = answer.operator+(rect_2);
    }

    int i = 0;
    while (expression[i] != '+' and expression[i] != '*') {
        ++i;
    }

    answer.print();
}
