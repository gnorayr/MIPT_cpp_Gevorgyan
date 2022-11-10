struct DoubleAbstractStack {
    // some code goes here
public:
    bool push(double next_element) {
        // some code goes here
        before_push();
        // push code
        after_push(next_element);
        return true;
    }

    // other public methods
protected:
    virtual void before_push() = 0;
    virtual void after_push(double pushed_element) = 0;
    virtual void before_pop() = 0;
    virtual void after_pop(double popped_element) = 0;
};

#include "4ex.hpp"

void operate_stack(DoubleAbstractStack &stack);
void check_min(DoubleStackWithMin const &stack);
int main() {
    DoubleStackWithMin min_stack;
    min_stack.push(3.);
    std::cout << min_stack.get_min() << std::endl;
    min_stack.push(1.);
    std::cout << min_stack.get_min() << std::endl;
    min_stack.push(2.);
    std::cout << min_stack.get_min() << std::endl;
    min_stack.pop();
    std::cout << min_stack.get_min() << std::endl;
    min_stack.pop();
    std::cout << min_stack.get_min() << std::endl;
    min_stack.pop();
    check_min(min_stack);
}
