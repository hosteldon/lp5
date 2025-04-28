#include <iostream>
#include <omp.h>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int phase = i % 2;
        #pragma omp parallel for shared(a, phase)
        for (int j = phase; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

int main() {
    int *a, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;
    a = new int[n];
    cout << "\nEnter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    bubble(a, n);
    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
    delete[] a;
    return 0;
}
