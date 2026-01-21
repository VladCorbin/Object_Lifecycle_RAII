#include <iostream>
#include <stdexcept>
#include <algorithm>  // для std::copy

// Класс умного массива с автоматическим расширением
class smart_array {
private:
    int* data;           // указатель на динамический массив
    size_t capacity;     // выделенная ёмкость
    size_t size;         // текущее количество элементов

    // Вспомогательная функция: увеличивает ёмкость массива вдвое
    void resize() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        // Копируем существующие элементы с помощью std::copy
        if (data != nullptr) {
            std::copy(data, data + size, new_data);
            delete[] data;  // освобождаем старую память
        }

        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор: выделяет память на заданное количество элементов
    explicit smart_array(size_t initial_capacity)
        : data(nullptr), capacity(initial_capacity), size(0) {
        if (initial_capacity == 0) {
            data = nullptr;
        }
        else {
            data = new int[initial_capacity];
        }
    }

    // Конструктор копирования
    smart_array(const smart_array& other)
        : capacity(other.capacity), size(other.size) {
        if (capacity == 0) {
            data = nullptr;
        }
        else {
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }
    }

    // Оператор присваивания (с защитой от самоприсваивания)
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;
        }

        // Освобождаем текущую память
        delete[] data;

        // Копируем данные из other
        capacity = other.capacity;
        size = other.size;

        if (capacity == 0) {
            data = nullptr;
        }
        else {
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }

        return *this;
    }

    // Деструктор: освобождает выделенную память
    ~smart_array() {
        delete[] data;
    }

    // Добавление элемента в массив
    void add_element(int value) {
        if (size >= capacity) {
            resize();  // увеличиваем ёмкость при необходимости
        }
        data[size] = value;
        ++size;
    }

    // Получение элемента по индексу (с проверкой границ)
    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Дополнительные методы для информации о состоянии
    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }
};

int main() {
    // Устанавливаем локаль для корректного отображения кириллицы
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        smart_array arr(5);  // начальный размер 5

        // Добавляем элементы
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        // Выводим элемент с индексом 1
        std::cout << arr.get_element(1) << std::endl;  // 4

        // Добавляем ещё элемент (произойдёт resize)
        arr.add_element(999);
        std::cout << arr.get_element(5) << std::endl;  // 999

        // Проверяем размеры
        std::cout << "Размер: " << arr.get_size() << std::endl;
        std::cout << "Ёмкость: " << arr.get_capacity() << std::endl;

    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
