#include <iostream>
#include <vector>
#include <algorithm>

// Интерфейс стратегии (контракт для всех сортировок)
class SortingStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0; // Метод сортировки
    virtual ~SortingStrategy() {}
};

// Пузырьковая сортировка
/*
Проходит по массиву несколько раз,
Сравнивает пары соседних элементов,
Если элементы в неправильном порядке — меняет местами.
Сложность — O(n^2) в худшем и среднем случае, O(n) — в лучшем.
*/
class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = 0; j < data.size() - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

// Быстрая сортировка
/*
Разделяет массив на части,
Сортирует каждую часть рекурсивно.
Сложность — O(n log n) в среднем и лучшем случае, O(n^2) — в худшем.
*/
class QuickSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        qsort(data, 0, data.size() - 1);
    }

    void qsort(std::vector<int>& data, int l, int r) {
        int i = l, j = r;
        int pivot = data[(l + r) / 2];

        while (i <= j) {
            while (data[i] < pivot) i++;
            while (data[j] > pivot) j--;
            if (i <= j) std::swap(data[i++], data[j--]);
        }

        if (l < j) qsort(data, l, j);
        if (i < r) qsort(data, i, r);
    }
};

// Сортировка вставками
/*
Берёт элементы по одному,
Вставляет каждый на правильное место в отсортированной части.
Сложность — O(n^2) в худшем и среднем, O(n) — в лучшем случае.
*/
class InsertionSort : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 1; i < data.size(); i++) {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }
};

// Класс, использующий стратегию
class Sorter {
    SortingStrategy* strategy;
public:
    Sorter(SortingStrategy* strategy) : strategy(strategy) {}

    void sortData(std::vector<int>& data) {
        strategy->sort(data);
    }
};

// Утилита для вывода массива
void printVector(const std::vector<int>& vec) {
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {4, 3, 9, 1, 4, 7};

    // Создаём стратегии сортировки
    BubbleSort bubble;
    QuickSort quick;
    InsertionSort insertion;

    // Создаём сортировщики с конкретными стратегиями
    Sorter bubbleSorter(&bubble);
    Sorter quickSorter(&quick);
    Sorter insertionSorter(&insertion);

    // Копируем массивы для сортировки
    std::vector<int> numbers1 = numbers;
    std::vector<int> numbers2 = numbers;
    std::vector<int> numbers3 = numbers;

    // Сортируем
    bubbleSorter.sortData(numbers1);
    quickSorter.sortData(numbers2);
    insertionSorter.sortData(numbers3);

    // Выводим результаты
    std::cout << "Исходный массив: ";
    printVector(numbers);

    std::cout << "Пузырьковая сортировка: ";
    printVector(numbers1);

    std::cout << "Быстрая сортировка: ";
    printVector(numbers2);

    std::cout << "Сортировка вставками: ";
    printVector(numbers3);

    return 0;
}
