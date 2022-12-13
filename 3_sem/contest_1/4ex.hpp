#include <stack>
#include <utility>

class DoubleStackWithMin: public DoubleAbstractStack {
public:
    double get_min() const {
        return minimums.top();
    }
private:
    virtual void before_push() {}
    virtual void after_push(double pushed_element) {
        if (minimums.empty()) {
            minimums.push(pushed_element);
        } else {
            minimums.push(std::min(minimums.top(), pushed_element));
        }
    }
    virtual void before_pop() {}
    virtual void after_pop(double popped_element) {
        minimums.pop();
    }

    std::stack<double> minimums;
};
