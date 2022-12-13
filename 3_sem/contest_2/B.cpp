#include <functional>
#include <iostream>
#include <utility>

template<typename Functor1, typename Functor2>
class Composition {
public:
    Composition(Functor1& outer, Functor2& inner)
            : inner_(inner)
            , outer_(outer)
    {}
    template<typename Argument>
    using ReturnValue = decltype(std::declval<Functor1>()(std::declval<Functor2>()(std::declval<Argument>())));
    template<typename Argument>
    ReturnValue<Argument> operator()(Argument argument) {
        return outer_(inner_(argument));
    }
private:
    Functor1& outer_;
    Functor2& inner_;
};
// lvalue/rvalue, const operator
// lvalue, non-const operator

template<typename Functor1, typename Functor2>
Composition<Functor1, Functor2> make_function_composition(Functor1& function1, Functor2& function2) {
    return Composition<Functor1, Functor2>(function1, function2);
}

struct NonCopyableFunction {
    NonCopyableFunction() = default;
    NonCopyableFunction(const NonCopyableFunction&) = delete;
    double operator()(double x) const {
        return x * x;
    }
};

double f(double x) {
    return x + x;
}

int main() {
    NonCopyableFunction g;
    auto h1 = make_function_composition(f, g); // f(g())
    auto res1 = h1(2.0); // res1 <- 8.0

    auto h2 = make_function_composition(g, f); // g(f())
    auto res2 = h2(2.0); // res2 <- 16.0
    std::cout << res1 << ' ' << res2 << std::endl;

    std::cout << make_function_composition(g, g)(2.0);
    return 0;
}
