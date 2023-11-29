#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <algorithm>

template <typename T, typename Compare = std::less<T>>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> forward;

        Node(const T& val, size_t level) : value(val), forward(level + 1, nullptr) {}

        friend class Iterator;
    };

    static constexpr double PROBABILITY = 0.5;
    size_t maxLevel;
    size_t size;
    Node* header;
    Compare comparator;

    size_t randomLevel() {
        size_t level = 0;
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        while (distribution(generator) < PROBABILITY && level < maxLevel) {
            level++;
        }

        return level;
    }

public:
    class Iterator {
    public:
        explicit Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->value;
        }

        Iterator& operator++() {
            current = current->forward[0];
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }

        Node* getCurrent() const {
            return current;
        }

    private:
        Node* current;
    };

    // Constructors, destructors, and other methods as needed

    SkipList() : maxLevel(0), size(0), header(new Node(T(), 0)) {}

    explicit SkipList(const Compare& comp) : maxLevel(0), size(0), header(new Node(T(), 0)), comparator(comp) {}

    ~SkipList() {
        clear();
        delete header;
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void insert(const T& value) {
        std::vector<Node*> update(header->forward.size(), nullptr);
        Node* current = header;

        for (int i = static_cast<int>(header->forward.size()) - 1; i >= 0; --i) {
            while (current->forward[i] != nullptr && comparator(current->forward[i]->value, value)) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        size_t newLevel = randomLevel();

        if (newLevel > maxLevel) {
            update.resize(newLevel + 1, header);
            maxLevel = newLevel;
        }

        Node* newNode = new Node(value, newLevel);

        for (size_t i = 0; i <= newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        size++;
    }

    Iterator find(const T& key) {
        Node* current = header;

        for (int i = static_cast<int>(header->forward.size()) - 1; i >= 0; --i) {
            while (current->forward[i] != nullptr && comparator(current->forward[i]->value, key)) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];

        if (current != nullptr && !comparator(key, current->value)) {
            return Iterator(current);
        } else {
            return end();
        }
    }

    void erase(const Iterator& it) {
        Node* current = header;
        std::vector<Node*> update(header->forward.size(), nullptr);

        for (int i = static_cast<int>(header->forward.size()) - 1; i >= 0; --i) {
            while (current->forward[i] != nullptr && current->forward[i] != it.getCurrent()) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == it.getCurrent()) {
            for (size_t i = 0; i < current->forward.size(); ++i) {
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            // Update maxLevel if necessary
            while (maxLevel > 0 && header->forward[maxLevel] == nullptr) {
                maxLevel--;
            }

            size--;
        }
    }

    Iterator begin() const {
        return Iterator(header->forward[0]);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    // Other methods and operators...

    // Helper functions...

    void clear() {
        Node* current = header->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }

        header->forward.clear();
        maxLevel = 0;
        size = 0;
    }

    // Other helper functions...
};

int main() {
    // Example usage

    SkipList<int> skipList;

    // Insert elements
    skipList.insert(3);
    skipList.insert(1);
    skipList.insert(4);
    skipList.insert(1);
    skipList.insert(5);

    // Print elements using iterators
    std::cout << "Elements in sorted order: ";
    for (const auto& value : skipList) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Find an element
    int key = 4;
    auto it = skipList.find(key);
    if (it != skipList.end()) {
        std::cout << "Element " << key << " found in the list." << std::endl;
    } else {
        std::cout << "Element " << key << " not found in the list." << std::endl;
    }

    // Erase an element
    skipList.erase(it);

    // Print elements after erasing
    std::cout << "Elements after erasing: ";
    for (const auto& value : skipList) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
