#include <chrono>
#include <iostream>
#include <set>
#include <random>

std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

class State {
    public:
    virtual bool contains(int s) const =0;
};

class DiscreteState: public State{
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState: public State{
private:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: public State {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class CombiningSets: public State {
private:
    State &a;
    State &b;
public:
    CombiningSets(State &a, State &b): a(a), b(b) { }

    bool contains(int s) const {
        return (a.contains(s) or b.contains(s));
    }
};

class IntersectionSets: public State {
private:
    State &a;
    State &b;
public:
    IntersectionSets(State &a, State &b): a(a), b(b) { }

    bool contains(int s) const {
        return (a.contains(s) and b.contains(s));
    }
};

class DifferenceSets: public State {
private:
    State &a;
    State &b;
public:
    DifferenceSets(State &a, State &b): a(a), b(b) { }

    bool contains(int s) const {
        return (a.contains(s) and !b.contains(s));
    }
};


class ProbabilityTest {
private:
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(int test_min, int test_max, unsigned test_count): test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(State const &s) const {
        std::uniform_int_distribution<int> distrib(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(distrib(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main() {
    DiscreteState d(1);
    SegmentState s(0,9);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    CombiningSets c(s, ss);
    IntersectionSets i(s, ss);
    DifferenceSets ds(s, ss);

    ProbabilityTest pt(0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(c) << std::endl;
    std::cout << pt(i) << std::endl;
    std::cout << pt(ds) << std::endl;
    return 0;
}
