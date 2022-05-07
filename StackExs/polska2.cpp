#include <iostream>
#include <cstdlib>
#include <unordered_map>

template<typename Element>
struct Node {
    Element val;
    Node *next;
};

template<typename Element>
struct Stack {
    unsigned size;
    Node<Element> *head;
    Node<Element> *tail;
};

template<typename Element>
Node<Element> *createNode(Element value) {
    return new Node<Element>{value, nullptr};
}

template<typename Element>
Node<Element> *ith_node(Stack<Element> *list, unsigned idx) {
    Node<Element> *node = list->head;
    for (int i = 0; i < idx; ++i) {
        node = node->next;
    }
    return node;
}

template<typename Element>
void push(Stack<Element> *stack, Element new_val) {
    Node<Element> *new_node = createNode<Element>(new_val);
    if (stack->size != 0) {
        stack->tail->next = new_node;
        stack->tail = new_node;
    } else {
        stack->tail = new_node;
        stack->head = new_node;
    }
    stack->size++;
}

template<typename Element>
int pop(Stack<Element> *stack) {
    if (stack->size == 0) {
        std::cout << "WRONG" << std::endl;
        return 0;
    }
    int tail_val = stack->tail->val;
    delete stack->tail;

    stack->size--;
    if (stack->size != 0) {
        Node<Element> *new_tail = ith_node(stack, stack->size - 1);
        stack->tail = new_tail;
        new_tail->next = nullptr;
    } else {
        stack->head = nullptr;
        stack->tail = nullptr;
    }
    return tail_val;
}

template<typename Element>
int top(Stack<Element> *list) {
    if (list->size == 0)
        return 0;
    return list->tail->val;
}

template<typename Element>
bool empty(Stack<Element> *stack) {
    return stack->size == 0;
}

template<typename Element>
void print(Stack<Element> *list) {
    if (list->size != 0) {
        for (int idx = 0; idx < list->size; ++idx) {
            std::cout << ith_node(list, idx)->val << " ";
        }
        std::cout << std::endl;
    } else
        std::cout << "list is empty" << std::endl;
}

template<typename Element>
void clear(Stack<Element> *list) {
    for (unsigned i = list->size; i > 0; --i) {
        pop(list);
    }
}

template<typename Element>
Stack<Element> *createStack(unsigned size) {
    auto *tmp = new Stack<Element>{0, nullptr, nullptr};
    for (int i = 0; i < size; ++i) {
        push<Element>(tmp, i);
    }
    return tmp;
}

template<typename Element>
char *copy_array(int oldSize, int newSize, const Element *arr) {
    char *newArr = new char[newSize];
    for (int i = 0; i < oldSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    return newArr;
}

int digitCount(int number) {
    int count = 0;
    while (number != 0) {
        ++count;
        number /= 10;
    }
    return count;
}

struct BigPupul {
    operator int() { return x_; }

    BigPupul(int x) {
        x_ = x;
    }

    int x_;
};

int operator+(BigPupul bigBaby, BigPupul smallBaby) { return bigBaby.operator int() + (int) smallBaby; }

int operator-(BigPupul bigBaby, BigPupul smallBaby) { return (int) bigBaby - (int) smallBaby; }

int operator*(BigPupul bigBaby, BigPupul smallBaby) { return (int) bigBaby * (int) smallBaby; }

int operator/(BigPupul bigBaby, BigPupul smallBaby) { return (int) bigBaby / (int) smallBaby; }

int main() {
    BigPupul x(8);
    std::unordered_map<char, int (*)(BigPupul, BigPupul)> punisher = {
            {'+', &operator+},
            {'-', &operator-},
            {'*', &operator*},
            {'/', &operator/},
    };

    int size = 1;
    char *arr = new char[size];
    char n;
    for (std::istreambuf_iterator i(std::cin); i != std::istreambuf_iterator<char>(); ++i) {
        n = *i;
        if (n == '^')
            break;
        arr[size - 1] = n;
        ++size;
        arr = copy_array(size - 1, size, arr);
    }
    size -= 2;
    Stack<char> signs = *createStack<char>(0);
    Stack<int> numbers = *createStack<int>(0);
    Stack<bool> first_operand = *createStack<bool>(0);

    int result;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == '-' || arr[i] == '+' || arr[i] == '*' || arr[i] == '/') {
            push(&signs, arr[i]);
            push(&first_operand, false);
        }
        if (arr[i] >= '0' and arr[i] <= '9') {
            int b = atoi(arr + i);
            i += digitCount(b) - 1;
            while (signs.size != 0 and first_operand.tail->val) {
                int a = pop(&numbers);
                char sign = pop(&signs);
                b = (*punisher[sign])(a, b);
                pop(&first_operand);
            }
            if (first_operand.size != 0) {
                first_operand.tail->val = true;
                push<int>(&numbers, b);
            } else
                result = b;
        }
    }
    std::cout << "result: " << result << std::endl;
    delete[] arr;
}
