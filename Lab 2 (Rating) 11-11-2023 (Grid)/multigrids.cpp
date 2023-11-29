#include <iostream>
#include <cassert>

template <typename T, size_t dim>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    Grid<T, dim - 1>* data;
    size_type d_size;

public:
    Grid(Grid<T, dim - 1>* data, size_type d_size) : data(data), d_size(d_size) {}

    Grid() : d_size(1), data(new Grid<T, dim - 1>[1]) {}

    Grid(const Grid<T, dim>& other) {
        data = other.data;
        d_size = other.d_size;
    }

    Grid(Grid<T, dim>&& other) {
        std::swap(data, other.data);
        std::swap(d_size, other.d_size);
    }

    Grid<T, dim>& operator=(const Grid<T, dim>& other) {
        if (this != &other) {
            delete[] data;
            d_size = other.d_size;
            data = new Grid<T, dim - 1>[d_size];
            for (size_type i = 0; i < d_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Grid<T, dim>& operator=(Grid<T, dim>&& other) {
        std::swap(data, other.data);
        std::swap(d_size, other.d_size);
        return *this;
    }

    ~Grid() {
        delete[] data;
    }

    template <typename... Args>
    T operator()(size_type d_idx, Args... idxes) const {
        return data[d_idx](idxes...);
    }

    template <typename... Args>
    T& operator()(size_type d_idx, Args... idxes) {
        return data[d_idx](idxes...);
    }

    template <typename... Args>
    Grid<T, dim>& operator=(T const& t) {
        for (auto it = data, end = data + d_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    Grid(T const& t) : d_size(1), data(new Grid<T, dim - 1>[1]) {
        data[0] = Grid<T, dim - 1>(t);
    }

    template <typename... Args>
    Grid(size_type d, Args... dims) : d_size(d), data(new Grid<T, dim - 1>[d]) {
        for (auto it = data, end = data + d; it != end; ++it) {
            *it = Grid<T, dim - 1>(dims...);
        }
    }

    template <typename... Args>
    Grid(size_type d, Args... dims, T const& t) : d_size(d), data(new Grid<T, dim - 1>[d]) {
        for (auto it = data, end = data + d; it != end; ++it) {
            *it = Grid<T, dim - 1>(dims..., t);
        }
    }

    Grid<T, dim - 1>& operator[](size_type idx) const {
        return data[idx];
    }
};

template <typename T>
class Grid<T, 2> final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type y_size, x_size;

public:
    Grid(T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

    Grid(const Grid<T, 2>& other) : y_size(other.y_size), x_size(other.x_size), data(new T[y_size * x_size]) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Grid(Grid<T, 2>&& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    Grid() : y_size(1), x_size(1), data(new T[1]) {
        data[0] = T();
    }

    Grid<T, 2>& operator=(const Grid<T, 2>& other) {
        if (this != &other) {
            delete[] data;
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size];
            for (size_type i = 0; i < y_size * x_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Grid<T, 2>& operator=(Grid<T, 2>&& other) {
        std::swap(data, other.data);
        std::swap(x_size, other.x_size);
        std::swap(y_size, other.y_size);
        return *this;
    }

    ~Grid() {
        delete[] data;
    }

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T, 2>& operator=(const T& t) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
        return *this;
    }

    Grid(const T& t) : x_size(1), y_size(1), data(new T[1]) {
        data[0] = t;
    }

    Grid(size_type y, size_type x) : x_size(x), y_size(y), data(new T[x * y]) {
        for (size_type i = 0; i < x * y; ++i) {
            data[i] = T();
        }
    }

    Grid(size_type y, size_type x, const T& t) : x_size(x), y_size(y), data(new T[x * y]) {
        for (size_type i = 0; i < x * y; ++i) {
            data[i] = t;
        }
    }

    size_type get_y_size() const {
        return y_size;
    }

    size_type get_x_size() const {
        return x_size;
    }

    T* operator[](size_type idx) {
        return &data[idx * x_size];
    }
};

int main()
{
    // What required workability in this fucking lab
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    // Example of output to the console of different grid parameters
    Grid<float, 2> g(53, 62, 5.0);
    std::cout << g.get_x_size() << " " << g.get_y_size() << std::endl;
    std::cout << g[1][2] << " " << g(0, 0) << std::endl << std::endl;

    Grid<float, 4> G = Grid<float, 4>(15, 25, 35, 43, 17.0);
    std::cout << G(4,4,4,2);

    // Example usage for a 2D grid
    Grid<float, 2> g2d(3, 4, 1.0f);
    assert(1.0f == g2d(1, 1));

    return 0;
}