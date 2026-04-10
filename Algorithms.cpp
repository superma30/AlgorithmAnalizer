#include <chrono>

class Algorithm {
public:
    enum AlgorithmNames {
        BubbleSort_ = 1,
        MergeSort_ = 2,
        QuickSort_ = 3,
        COUNT = 4
    };

    static std::string GetAlgorithmName(AlgorithmNames name) {
        switch (name) {
            case BubbleSort_: return "Bubble Sort";
            case MergeSort_: return "Merge Sort";
            case QuickSort_: return "Quick Sort";
        }
        return "Unknown";
    }

    static std::array<int, 3> CallAlgorithmByName(AlgorithmNames name, std::vector<int> array) {
        switch (name) {
            case AlgorithmNames::BubbleSort_:
                return BubbleSort(array);
            case AlgorithmNames::MergeSort_:
                return MergeSort(array);
            case AlgorithmNames::QuickSort_:
                return QuickSort(array);
        }
        return {-1, -1, -1}; // Iterations, Swaps, Time
    }

    static std::array<int, 3> BubbleSort(std::vector<int> array) {
        int size = array.size();
        int iterations = 0;
        int swaps = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                iterations++;
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    swaps++;
                }
            }
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        return {iterations, swaps, (int) duration.count()};
    }

    static std::array<int, 3> MergeSort(std::vector<int> array) {
        int iterations = 0;
        int writes = 0;

        auto start = std::chrono::high_resolution_clock::now();

        MergeSortRecursive(array, 0, (int) array.size() - 1, iterations, writes);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        return {iterations, writes, (int) duration.count()};
    }

    static std::array<int, 3> QuickSort(std::vector<int> array) {
        int iterations = 0;
        int swaps = 0;

        auto start = std::chrono::high_resolution_clock::now();

        QuickSortRecursive(array, 0, (int) array.size() - 1, iterations, swaps);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        return {iterations, swaps, (int) duration.count()};
    }

private:
    static void MergeSortRecursive(std::vector<int> &array, int left, int right, int &iterations, int &writes) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        MergeSortRecursive(array, left, mid, iterations, writes);
        MergeSortRecursive(array, mid + 1, right, iterations, writes);

        // Merge
        std::vector<int> temp;
        temp.reserve(right - left + 1);

        int i = left;
        int j = mid + 1;

        while (i <= mid && j <= right) {
            iterations++; // comparison
            if (array[i] <= array[j]) {
                temp.push_back(array[i++]);
                writes++;
            } else {
                temp.push_back(array[j++]);
                writes++;
            }
        }

        while (i <= mid) {
            temp.push_back(array[i++]);
            writes++;
        }

        while (j <= right) {
            temp.push_back(array[j++]);
            writes++;
        }

        for (int k = 0; k < (int) temp.size(); k++) {
            array[left + k] = temp[k];
            writes++;
        }
    }

    static void QuickSortRecursive(std::vector<int> &array, int low, int high, int &iterations, int &swaps) {
        if (low >= high) return;

        int pivotIndex = Partition(array, low, high, iterations, swaps);

        QuickSortRecursive(array, low, pivotIndex - 1, iterations, swaps);
        QuickSortRecursive(array, pivotIndex + 1, high, iterations, swaps);
    }

    static int Partition(std::vector<int> &array, int low, int high, int &iterations, int &swaps) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            iterations++; // comparison
            if (array[j] <= pivot) {
                i++;
                std::swap(array[i], array[j]);
                swaps++;
            }
        }

        std::swap(array[i + 1], array[high]);
        swaps++;

        return i + 1;
    }
};
