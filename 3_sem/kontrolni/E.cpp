class Kwama: public Creature {
public:
    Kwama(double x, double y, double vx, double vy, int age)
            : Creature(x, y, vx, vy)
            , age(age)
    {}
    ~Kwama() = default;
    virtual unsigned int slaughter() = 0;
    virtual void pouch() = 0;
    virtual void act_like_a_kwama() = 0;
protected:
    int age;
};

