#include <iostream>
#include <stdexcept>
#include <cstring>

class smart_array {
private:
    int* data;
    size_t capacity;
    size_t size;

    void resize() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        if (data != nullptr) {
            std::memcpy(new_data, data, size * sizeof(int));
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор
    explicit smart_array(size_t initial_capacity) {
        if (initial_capacity < 0) {
            throw std::invalid_argument("Capacity must be non-negative");
        }
        data = new int[initial_capacity];
        capacity = initial_capacity;
        size = 0;
    }

    // Конструктор копирования
    smart_array(const smart_array& other) {
        data = new int[other.capacity];
        capacity = other.capacity;
        size = other.size;
        std::memcpy(data, other.data, size * sizeof(int));
    }

    // Оператор присваивания
    smart_array& operator=(const smart_array& other) {
        // Защита от самоприсваивания
        if (this == &other) {
            return *this;
        }

        // Освобождаем текущую память
        delete[] data;

        // Копируем данные из other
        data = new int[other.capacity];
        capacity = other.capacity;
        size = other.size;
        std::memcpy(data, other.data, size * sizeof(int));

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
