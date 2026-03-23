#include <iostream>
#include <windows.h>
using namespace std;

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) minIndex = j;
        }
        int t = a[i];
        a[i] = a[minIndex];
        a[minIndex] = t;
    }
}

void bubbleSortRange(int a[], int left, int right, bool ascending = true) {
    for (int i = left; i < right; i++) {
        for (int j = left; j < right - (i - left); j++) {
            if ((ascending && a[j] > a[j + 1]) || (!ascending && a[j] < a[j + 1])) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

void insertionSortRange(int a[], int left, int right, bool ascending = true) {
    for (int i = left + 1; i <= right; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= left && ((ascending && a[j] > key) || (!ascending && a[j] < key))) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int a[] = {10, -1, -5, 8, 12, 45, 1078, -45, -4, 4 ,1, 33, 11, 66};
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Исходный массив:\n";
    printArray(a, n);

    int b[100];
    for (int i = 0; i < n; i++) b[i] = a[i];
    selectionSort(b, n);
    cout << "\nПосле сортировки выбором:\n";
    printArray(b, n);

    int c[100];
    for (int i = 0; i < n; i++) c[i] = a[i];
    bubbleSortRange(c, 0, n - 1, true);
    cout << "\nПосле сортировки пузырьком:\n";
    printArray(c, n);

    int d[100];
    for (int i = 0; i < n; i++) d[i] = a[i];
    int N1 =4, N2 = 9;
    insertionSortRange(d, N1, N2, true);
    cout << "\nСортировка вставками по возрастанию на участке [" << N1 << ", " << N2 << "]:\n";
    printArray(d, n);

    int e[100];
    for (int i = 0; i < n; i++) e[i] = a[i];
    bubbleSortRange(e, N1, N2, true);
    cout << "\nПузырек по возрастанию на участке [" << N1 << ", " << N2 << "]:\n";
    printArray(e, n);

    int f[100];
    for (int i = 0; i < n; i++) f[i] = a[i];
    bubbleSortRange(f, N1, N2, false);
    cout << "\nПузырек по убыванию на участке [" << N1 << ", " << N2 << "]:\n";
    printArray(f, n);

    return 0;
}