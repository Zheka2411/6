#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Конструктор за замовчуванням
    Array(size_t init_capacity = 10)
        : size(0), capacity(init_capacity) {
        data = new T[capacity];
    }

    // Конструктор ініціалізації списком
    Array(std::initializer_list<T> init) : size(init.size()), capacity(init.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const auto& el : init) {
            data[i++] = el;
        }
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Отримання кількості елементів
    size_t getSize() const {
        return size;
    }

    // Отримання ємності
    size_t getCapacity() const {
        return capacity;
    }

    // Метод для додавання елемента в кінець
    void append(const T& value) {
        if (size == capacity) {
            reserve(capacity * 2); // Подвоюємо ємність
        }
        data[size++] = value;
    }

    // Метод для видалення елемента по індексу
    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // Очищаємо всі елементи
    void clear() {
        size = 0;
    }

    // Збільшуємо ємність
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    }

    // Стискаємо ємність до мінімуму
    void shrink() {
        if (size < capacity) {
            T* new_data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = size;
        }
    }

    // Оператор [] для доступу до елементів
    T& operator[](size_t index) {
        return data[index];
    }

    // Оператор [] (const) для доступу до елементів
    const T& operator[](size_t index) const {
        return data[index];
    }

    // Оператор = для копіювання
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Оператор = для переміщення
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Оператор виводу в потік
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i] << " ";
        }
        return os;
    }

    // Конструктор ініціалізації списком
    Array(std::initializer_list<T> init) : size(init.size()), capacity(init.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const auto& el : init) {
            data[i++] = el;
        }
    }

    // Оператор = для ініціалізації списком
    Array& operator=(std::initializer_list<T> init) {
        if (init.size() > capacity) {
            delete[] data;
            capacity = init.size();
            data = new T[capacity];
        }
        size = init.size();
        size_t i = 0;
        for (const auto& el : init) {
            data[i++] = el;
        }
        return *this;
    }

    int main() {
        Array<int> arr = { 1, 2, 3, 4, 5 };
        std::cout << "Array: " << arr << std::endl;

        arr.append(6);
        std::cout << "After append: " << arr << std::endl;

        arr.erase(2); // Видалити елемент за індексом 2
        std::cout << "After erase: " << arr << std::endl;

        arr.reserve(20); // Збільшуємо ємність
        std::cout << "After reserve: " << arr << std::endl;

        arr.shrink(); // Зменшуємо ємність до мінімуму
        std::cout << "After shrink: " << arr << std::endl;

        Array<int> arr2 = arr;
        std::cout << "Copy of arr: " << arr2 << std::endl;

        Array<int> arr3 = { 10, 20, 30 };
        arr3 = { 100, 200, 300 };
        std::cout << "After assignment: " << arr3 << std::endl;

        return 0;
    }

};
