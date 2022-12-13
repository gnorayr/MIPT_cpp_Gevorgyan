#include <iostream>
#include <cmath>
#include <stack>

struct Point {
    int x, y;

    Point(int x, int y) :
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
    Point rha;
public:
    Rectangle() : rha((Point(0, 0))) {}

    Rectangle(const Point &rha) : rha(rha) {}

    Rectangle(int x, int y): Rectangle(Point(x, y)) {}

    Rectangle operator+(Rectangle const &rh) {
        return Rectangle(rha.maxx(rh.rha).x, rha.maxy(rh.rha).y);
    }

    Rectangle operator*(Rectangle const &rh) {
        return Rectangle(rha.minx(rh.rha).x, rha.miny(rh.rha).y);
    }

    void print() {
        std::cout << '(' << rha.x << ',' << rha.y << ')' << std::endl;
    }
};

void slice_string(std::string string, int begin, int *coordinates, int num, int base_condition) {
    if (num >= base_condition)
        return;
    while (string[begin] < '0' or string[begin] > '9') {
        ++begin;
    }
    int end = begin;
    while (string[end] >= '0' and string[end] <= '9') {
        ++end;
    }
    int point_coordinate = 0;
    for (int j = 0; j < end - begin; ++j) {
        point_coordinate += ((int)(string[end - j - 1]) - '0') * pow(10, j);
    }
    coordinates[num] = point_coordinate;
    slice_string(string, end + 1, coordinates, ++num, base_condition);
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

    std::stack<Rectangle> sum_stack;
    std::stack<int> used_coord_stack;
    for (int i = 0; i <= sign_num; ++i) {
        if (i == 0 || signs[i - 1] == '+') {
            int begin = i;
            while (i < sign_num and signs[i] != '+') {
                ++i;
            }
            Rectangle rect_1 = Rectangle(coord[2 * begin], coord[2 * begin + 1]);
            for (int k = ++begin; k < i + 1; ++k) {
                Rectangle rect_2 = (Rectangle(coord[2 * k], coord[2 * k + 1]));
                rect_1 = rect_1 * rect_2;
            }
            sum_stack.push(rect_1);
        }
    }

    int sum_stack_size = sum_stack.size();
    Rectangle answer;
    for (int i = 0; i < sum_stack_size; ++i) {
        answer = answer + sum_stack.top();
        sum_stack.pop();
    }

    delete[] signs;
    delete[] coord;

    answer.print();
    //(5,5) *(2, 7) + (7,7) * (2,6) * (1, 8) + (2, 4) * (3, 2)
    //answer = (2, 6)
}
