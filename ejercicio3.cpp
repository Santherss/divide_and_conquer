#include <iostream>
#include <vector>

using namespace std;
using ll = long long;


ll mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;    
    int j = mid + 1; 
    int k = left;    
    ll inversions = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += (mid - i + 1);
        }
    }

    // Copiar los elementos restantes de la mitad izquierda, si quedan
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copiar los elementos restantes de la mitad derecha, si quedan
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copiar de vuelta al arreglo original
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

ll mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    ll inversions = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        inversions += mergeSortAndCount(arr, temp, left, mid);
        inversions += mergeSortAndCount(arr, temp, mid + 1, right);

        inversions += mergeAndCount(arr, temp, left, mid, right);
    }
    return inversions;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        vector<int> temp(n);
        ll totalinversions = mergeSortAndCount(arr, temp, 0, n - 1);
        
        cout << "\n" << totalinversions;
    }

    return 0;
}
