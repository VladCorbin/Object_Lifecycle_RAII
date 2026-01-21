#include <iostream>
#include <stdexcept>
#include <algorithm>  // для std::copy

class smart_array {
private:
    int* data;
    size_t capacity;
    size_t size;

    void resize() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        if (data != nullptr) {
            std::copy(data, data + size, new_data);
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор
    explicit smart_array(size_t initial_capacity)
        : data(nullptr), capacity(initial_capacity), size(0) {
        if (initial_capacity > 0) {
            data = new int[initial_capacity];
        }
    }

    // Конструктор копирования
    smart_array(const smart_array& other)
        : capacity(other.capacity), size(other.size) {
        if (capacity > 0) {
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }
        else {
            data = nullptr;
        }
    }

    // Оператор присваивания
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;  // освобождаем текущую память

        capacity = other.capacity;
        size = other.size;

        if (capacity > 0) {
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }
        else {
            data = nullptr;
        }

        return *this;
    }

    // Деструктор
    ~smart_array() {
        delete[] data;
    }

    void add_element(int value) {
        if (size >= capacity) {
            resize();
        }
        data[size] = value;
        ++size;
    }

    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;  // Теперь безопасно!

        std::cout << "arr size: " << arr.get_size() << std::endl;      // 2
        std::cout << "arr[0]: " << arr.get_element(0) << std::endl;    // 44
        std::cout << "arr[1]: " << arr.get_element(1) << std::endl;    // 34

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
