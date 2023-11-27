#include <cassert>
#include <vector>

template <typename T, size_t Dimension>
class Grid {
public:
    using value_type = T;
    using size_type = unsigned;

    // Constructor for grids of higher dimensions
    template <typename... Args>
    Grid(Args... args) : dimensions{static_cast<size_type>(args)...}, data(calculateTotalSize(dimensions)) {
        static_assert(sizeof...(args) == Dimension, "Incorrect number of arguments");
    }

    // Copy constructor
    Grid(const Grid& other) : dimensions(other.dimensions), data(other.data) {}

    // Move constructor
    Grid(Grid&& other) noexcept : dimensions(std::move(other.dimensions)), data(std::move(other.data)) {}

    // Copy assignment operator
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            dimensions = other.dimensions;
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            dimensions = std::move(other.dimensions);
            data = std::move(other.data);
        }
        return *this;
    }

    // Indexing operator for accessing child grids
    const Grid& operator[](size_type index) const {
        assert(index < dimensions[0]);
        size_type subGridSize = calculateTotalSize(dimensions.begin() + 1, dimensions.end());
        return *reinterpret_cast<const Grid*>(&data[index * subGridSize]);
    }

    Grid& operator[](size_type index) {
        assert(index < dimensions[0]);
        size_type subGridSize = calculateTotalSize(dimensions.begin() + 1, dimensions.end());
        return *reinterpret_cast<Grid*>(&data[index * subGridSize]);
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

    // Calculate the total size of a grid given a range of dimensions
    size_type calculateTotalSize(std::vector<size_type>::const_iterator begin, std::vector<size_type>::const_iterator end) const {
        size_type result = 1;
        for (auto it = begin; it != end; ++it) {
            result *= *it;
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

    g2 = g3[1];
    assert(1.0f == g2(1 * 4 + 1));

    return 0;
}
