//
// Created by alexg on 11/15/2023.
//

#ifndef MIPT_CPP_III_SEM_COMPARATOR_H
#define MIPT_CPP_III_SEM_COMPARATOR_H

#endif //MIPT_CPP_III_SEM_COMPARATOR_H

// Comparator interface
template <typename T>
struct Comparator {
    virtual bool operator()(const T&, const T&) const = 0;
};

// Integer comparator implementation
struct IntComparator final : Comparator<int> {
    bool operator()(const int& lhs, const int& rhs) const override {
        return lhs < rhs;
    }
};

// String comparator implementation
struct StringComparator final : Comparator<std::string> {
    bool operator()(const std::string& lhs, const std::string& rhs) const override {
        return lhs < rhs;
    }
};

// Float comparator implementation
struct FloatComparator final : Comparator<float> {
    bool operator()(const float& lhs, const float& rhs) const override {
        return lhs < rhs;
    }
};