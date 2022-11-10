#include <cstdint>
#include <cmath>
#include <utility>

uint64_t gcdu(uint64_t a, uint64_t b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

class Fraction final {
public:
    Fraction() = delete;
    Fraction(Fraction const& rhs) = default;
    Fraction(int64_t numerator, uint64_t denominator)
            : numerator(numerator)
            , denominator(denominator)
    {
        reduce_();
    }

    Fraction& operator=(Fraction const& rhs) = default;
    Fraction& operator+=(Fraction const& rhs) { return *this = *this + rhs; }
    Fraction& operator-=(Fraction const& rhs) { return *this = *this - rhs; }
    Fraction& operator*=(Fraction const& rhs) { return *this = *this * rhs; }

    Fraction operator+(Fraction const& rhs) const {
        uint64_t commonDenominator = denominator / gcdu(denominator, rhs.denominator) * rhs.denominator;
        int64_t leftFactor = commonDenominator / denominator;
        int64_t rightFactor = commonDenominator / rhs.denominator;
        Fraction result(numerator * leftFactor + rhs.numerator * rightFactor, commonDenominator);
        return result.reduce_();
    }
    Fraction operator-(Fraction const& rhs) const {
        return -rhs + *this;
    }
    Fraction operator*(Fraction const& rhs) const {
        int64_t numeratorFactor = gcdu(std::abs(numerator), rhs.denominator);
        int64_t denominatorFactor = gcdu(denominator, std::abs(rhs.numerator));
        Fraction result(numerator / numeratorFactor * (rhs.numerator / denominatorFactor),
                        denominator / denominatorFactor * (rhs.denominator / numeratorFactor));
        return result.reduce_();
    }
    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }
private:
    // Do NOT rename
    int64_t numerator;
    uint64_t denominator;

    // Do NOT delete
    template <class T>
    friend bool operator==(const Fraction& lhs, const T& rhs);

    Fraction& reduce_() {
        uint64_t factoru = gcdu(std::abs(numerator), denominator);
        numerator /= static_cast<int64_t>(factoru);
        denominator /= factoru;
        return *this;
    }
};
