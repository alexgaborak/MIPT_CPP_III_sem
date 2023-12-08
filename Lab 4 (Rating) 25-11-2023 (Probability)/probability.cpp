//
// Created by alexg on 11/29/2023.
//
#include <iostream>
#include <set>
#include <random>
#include "probability.h"



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
