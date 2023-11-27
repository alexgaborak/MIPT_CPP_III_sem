#include <cassert>
#include <vector>

template <typename T, size_t Dimension>
class Grid {
public:
    using value_type = T;
    using size_type = unsigned;

    // Constructor for grids of higher dimensions
    template <typename... Args>
    Grid(size_type dim, Args... args) : dimensions{dim, static_cast<size_type>(args)...}, data(calculateTotalSize(dimensions)) {
        static_assert(sizeof...(args) == Dimension - 1, "Incorrect number of arguments");
    }

    // Parenthesis operator for accessing elements directly
    const T& operator()(size_type index) const {
        assert(index < data.size());
        return data[index];
    }

    T& operator()(size_type index) {
        assert(index < data.size());
        return data[index];
    }

private:
    std::vector<size_type> dimensions;
    std::vector<T> data;

    // Calculate the total size of a grid given its dimensions
    size_type calculateTotalSize(const std::vector<size_type>& dims) const {
        size_type result = 1;
        for (auto dim : dims) {
            result *= dim;
        }
        return result;
    }
};

int main() {
    // Example usage
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1 * 3 * 4 + 1 * 4 + 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1 * 5 + 1));

    return 0;
}
