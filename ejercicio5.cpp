#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int particion(vector<int>& arr, int bajo, int alto) {
    int randomIndex = bajo + rand() % (alto - bajo + 1);
    intercambiar(arr[randomIndex], arr[alto]); // Movemos el pivote al final temporalmente
    
    int pivote = arr[alto];
    int i = bajo;

    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
            intercambiar(arr[i], arr[j]);
            i++;
        }
    }
    intercambiar(arr[i], arr[alto]); // Colocamos el pivote en su posición final definitiva
    return i; 
}

int quickSelect(vector<int>& arr, int bajo, int alto, int objetivo) {
    if (bajo == alto) {
        return arr[bajo]; 
    }

    int pivotIndex = particion(arr, bajo, alto);

    // Comparamos la posición del pivote con el índice que buscamos
    if (pivotIndex == objetivo) {
        return arr[pivotIndex];
    } else if (pivotIndex > objetivo) {
        return quickSelect(arr, bajo, pivotIndex - 1, objetivo); 
    } else {
        return quickSelect(arr, pivotIndex + 1, alto, objetivo);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    srand(time(nullptr));

    int objetivo = n - k;

    int resultado = quickSelect(arr, 0, n - 1, objetivo);

    cout << resultado << "\n";

    return 0;
}
