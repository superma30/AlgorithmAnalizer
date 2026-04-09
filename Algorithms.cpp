static class Algorithm {
public:
    enum AlgorithmNames {
        _BubbleSort = 1,
      };
    static int CallAlgorithmByName(AlgorithmNames name, int *array, int size) {
        switch (name) {
            case 1:
                return BubbleSort(array, size);
        }
        return -1;
    }
    static int BubbleSort(int *array, int size) {
        int iterations = 0;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                iterations++;
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
};
