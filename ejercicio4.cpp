#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Punto {
    double x, y;
};

double distanciaEuclidiana(Punto p1, Punto p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double distanciaMinima(vector<Punto>& puntos, int left, int right) {
    if (right - left <= 2) {
        double minDist = 1e18; 
        for (int i = left; i <= right; i++) {
            for (int j = i + 1; j <= right; j++) {
                minDist = min(minDist, distanciaEuclidiana(puntos[i], puntos[j]));
            }
        }
        return minDist;
    }

    //dividir
    int mid = left + (right - left) / 2;
    Punto midPoint = puntos[mid];

    //Vencer
    double d_izq = distanciaMinima(puntos, left, mid);
    double d_der = distanciaMinima(puntos, mid + 1, right);
    double d = min(d_izq, d_der);

    //combinar: revisar la fraja central (strip)
    vector<Punto> franja;
    for (int i = left; i <= right; i++) {
        // Guardamos solo los puntos cuya coordenada X esté a una distancia menor que 'd' del punto medio
        if (abs(puntos[i].x - midPoint.x) < d) {
            franja.push_back(puntos[i]);
        }
    }

    // Ordenamos la franja por la coordenada Y para poder buscar eficientemente
    sort(franja.begin(), franja.end(), [](const Punto& a, const Punto& b) {
        return a.y < b.y;
    }); 

    // Comparamos los puntos dentro de la franja
    for (size_t i = 0; i < franja.size(); i++) {
        for (size_t j = i + 1; j < franja.size() && (franja[j].y - franja[i].y) < d; j++) {
            double dist = distanciaEuclidiana(franja[i], franja[j]);
            if (dist < d) {
                d = dist;
            }
        }
    }

    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        if (n == 1) {
            double x, y;
            cin >> x >> y; 
            cout << "INFINITY\n";
            continue;
        }

        vector<Punto> puntos(n);
        for (int i = 0; i < n; i++) {
            cin >> puntos[i].x >> puntos[i].y;
        }

        sort(puntos.begin(), puntos.end(), [](const Punto& a, const Punto& b) {
            return a.x < b.x;
        });

        double resultado = distanciaMinima(puntos, 0, n - 1);
        
        if (resultado >= 10000.0) {
            cout << "INFINITY\n";
        } else {
            cout << fixed << setprecision(4) << resultado << "\n";
        }
    }

    return 0;
}
