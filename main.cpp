#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

class BubbleSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        bool swapped;
        for (size_t i = 0; i < data.size(); i+=1) {
            swapped = false;
            for (size_t j = 0; j < data.size() - i - 1; j+=1) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
};

class QuickSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j+=1) {
            if (data[j] < pivot) {
                i+=1;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
};

class StdSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

class InsertionSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 1; i < data.size(); i+=1) {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j-=1;
            }
            data[j + 1] = key;
        }
    }
};

class Sorter {
public:
    Sorter(std::unique_ptr<SortingStrategy>&& strategy) : strategy_(std::move(strategy)) {}

    void sortData(std::vector<int>& data) {
        strategy_->sort(data);
    }

private:
    std::unique_ptr<SortingStrategy> strategy_;
};

void printVector(const std::vector<int>& data) {
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> data = {5, 2, 7, 1, 3};

    std::cout << "Original data: ";
    printVector(data);

    // Bubble Sort
    {
        std::vector<int> dataCopy = data;
        Sorter sorter(std::make_unique<BubbleSortStrategy>());
        sorter.sortData(dataCopy);
        std::cout << "Bubble sorted: ";
        printVector(dataCopy);
    }

    // Quick Sort
    {
        std::vector<int> dataCopy = data;
        Sorter sorter(std::make_unique<QuickSortStrategy>());
        sorter.sortData(dataCopy);
        std::cout << "Quick sorted: ";
        printVector(dataCopy);
    }

    // Std Sort
    {
        std::vector<int> dataCopy = data;
        Sorter sorter(std::make_unique<StdSortStrategy>());
        sorter.sortData(dataCopy);
        std::cout << "Std sorted: ";
        printVector(dataCopy);
    }

    // Insertion Sort
    {
        std::vector<int> dataCopy = data;
        Sorter sorter(std::make_unique<InsertionSortStrategy>());
        sorter.sortData(dataCopy);
        std::cout << "Insertion sorted: ";
        printVector(dataCopy);
    }

    return 0;
}