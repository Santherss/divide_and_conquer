#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Memoria {
    bool usado = false;
    vector<int> valores;
};

Memoria memoria[100][100];

vector<int> FORMAS(const string& expresion, int inicio, int largo) {
    // Si ya fue calculado, retornamos 
    if (memoria[inicio][largo].usado) {
        return memoria[inicio][largo].valores;
    }

    vector<int> R;

    for (int pos = 0; pos < largo; pos++) {
        char actual = expresion[inicio + pos];
        if (actual != '+' && actual != '-' && actual != '*')
            continue;

        // Subproblemas izquierdo y derecho
        vector<int> izq = FORMAS(expresion, inicio, pos);
        vector<int> der = FORMAS(expresion, inicio + pos + 1, largo - pos - 1);

        // Para combinar resultados cruzados
        for (int valIzq : izq) {
            for (int valDer : der) {
                int r = 0;
                if (actual == '+') r = valIzq + valDer;
                else if (actual == '-') r = valIzq - valDer;
                else r = valIzq * valDer;
                R.push_back(r);
            }
        }
    }

    // Caso en donde no hay operadores, es un número
    if (R.empty()) {
        R.push_back(stoi(expresion.substr(inicio, largo)));
    }

    // Almacenamos en la tabla de memoización
    memoria[inicio][largo].valores = R;
    memoria[inicio][largo].usado = true;

    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string expresion;
    if (!(cin >> expresion)) return 0;

    vector<int> resultado = FORMAS(expresion, 0, expresion.length());

    // Orden ascendente requerido
    sort(resultado.begin(), resultado.end());

    bool primero = true;
    for (int r : resultado) {
        cout << (primero ? "" : " ") << r;
        primero = false;
    }
    cout << "\n";

    return 0;
}
