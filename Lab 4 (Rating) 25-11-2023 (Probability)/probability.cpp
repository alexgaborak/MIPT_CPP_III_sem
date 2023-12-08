//
// Created by alexg on 11/29/2023.
//
#include <iostream>
#include <set>
#include <random>

class State {
public:
    virtual bool contains(int s) const = 0;
};

class DiscreteState : public State {
private:
    int const state;

public:
    DiscreteState(int state) : state(state) {}

    bool contains(int s) const override {
        return s == state;
    }
};

class SegmentState : public State {
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) {}
    SegmentState(int beg, int end) : beg(beg), end(end) {}

    bool contains(int s) const override {
        return s >= beg && s <= end;
    }
};

class SetState : public State {
private:
    std::set<int> const states;

public:
    SetState() : states() {}
    SetState(std::set<int> const &src) : states(src) {}

    bool contains(int s) const override {
        return states.count(s) > 0;
    }
};


class ContinuousStatesWithOmissions : public State {
private:
    int const beg, end, omission;

public:
    ContinuousStatesWithOmissions(int beg, int end, int omission) : beg(beg), end(end), omission(omission) {}

    bool contains(int s) const override {
        return s >= beg && s <= end && s != omission;
    }
};

class ContinuousStatesWithAdditions : public State {
private:
    int const beg, end, addition;

public:
    ContinuousStatesWithAdditions(int beg, int end, int addition) : beg(beg), end(end), addition(addition) {}

    bool contains(int s) const override {
        return (s >= beg && s <= end) || s == addition;
    }
};

class ContinuousStatesWithOmissionsAndAdditions : public State {
private:
    int const beg, end, omission, addition;

public:
    ContinuousStatesWithOmissionsAndAdditions(int beg, int end, int omission, int addition)
            : beg(beg), end(end), omission(omission), addition(addition) {}

    bool contains(int s) const override {
        return (s >= beg && s <= end) && s != omission || s == addition;
    }
};

class UnionState : public State {
private:
    const State &state1;
    const State &state2;

public:
    UnionState(const State &state1, const State &state2) : state1(state1), state2(state2) {}

    bool contains(int s) const override {
        return state1.contains(s) || state2.contains(s);
    }
};

class IntersectionState : public State {
private:
    const State &state1;
    const State &state2;

public:
    IntersectionState(const State &state1, const State &state2) : state1(state1), state2(state2) {}

    bool contains(int s) const override {
        return state1.contains(s) && state2.contains(s);
    }
};


class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count)
            : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) {}

    float operator()(const State &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng)))
                ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

int main(int argc, const char *argv[]) {
    DiscreteState d(1);
    SegmentState s(0, 10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});

    ContinuousStatesWithOmissions co(0, 10, 5);
    ContinuousStatesWithAdditions ca(0, 10, 15);
    ContinuousStatesWithOmissionsAndAdditions coa(0, 10, 5, 15);
    UnionState unionState(ss, ca);
    IntersectionState intersectionState(s, co);

    ProbabilityTest pt(10, 0, 100, 100000);

    std::cout << "DiscreteState: " << pt(d) << std::endl;
    std::cout << "SegmentState: " << pt(s) << std::endl;
    std::cout << "SetState: " << pt(ss) << std::endl;
    std::cout << "ContinuousStatesWithOmissions: " << pt(co) << std::endl;
    std::cout << "ContinuousStatesWithAdditions: " << pt(ca) << std::endl;
    std::cout << "ContinuousStatesWithOmissionsAndAdditions: " << pt(coa) << std::endl;
    std::cout << "UnionState: " << pt(unionState) << std::endl;
    std::cout << "IntersectionState: " << pt(intersectionState) << std::endl;

    return 0;
}
