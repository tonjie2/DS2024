#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// ��������
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ��������
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ѡ������
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// �鲢����
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ��������
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ������
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void testSortingAlgorithm(void (*sortFunc)(vector<int>&), vector<int> arr, const string& name) {
    vector<int> testArr = arr;

    auto start = high_resolution_clock::now();
    sortFunc(testArr);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << name << duration.count() << "΢��\n";
}

int main() {
    vector<int> ascending(1000), descending(1000), randomSeq(1000);

    for (int i = 0; i < 1000; ++i) {
        ascending[i] = i;
        descending[i] = 1000 - i;
        randomSeq[i] = rand() % 1000;
    }

    cout << "˳��:\n";
    testSortingAlgorithm(bubbleSort, ascending, "��������");
    testSortingAlgorithm(insertionSort, ascending, "��������");
    testSortingAlgorithm(selectionSort, ascending, "ѡ������");
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, ascending, "�鲢����");
    testSortingAlgorithm([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, ascending, "��������");
    testSortingAlgorithm(heapSort, ascending, "������");

    cout << "\n����:\n";
    testSortingAlgorithm(bubbleSort, descending, "��������");
    testSortingAlgorithm(insertionSort, descending, "��������");
    testSortingAlgorithm(selectionSort, descending, "ѡ������");
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, descending, "�鲢����");
    testSortingAlgorithm([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, descending, "��������");
    testSortingAlgorithm(heapSort, descending, "������");

    cout << "\n�������:\n";
    testSortingAlgorithm(bubbleSort, randomSeq, "��������");
    testSortingAlgorithm(insertionSort, randomSeq, "��������");
    testSortingAlgorithm(selectionSort, randomSeq, "ѡ������");
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, randomSeq, "�鲢����");
    testSortingAlgorithm([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, randomSeq, "��������");
    testSortingAlgorithm(heapSort, randomSeq, "������");

    return 0;
}
