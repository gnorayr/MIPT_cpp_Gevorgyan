class DerivativeFunction: public RealFunction {
public:
    DerivativeFunction(RealFunction const &f) : underlying_(f) {}

    double operator()(unsigned idx) const {
        return derivative(idx, underlying_);
    }
private:
    RealFunction const &underlying_;
};
