#include <bits/stdc++.h>
#include <cassert>
using namespace std;

string sumarCadenas(string s1, string s2) {
    string resultado = "";
    int i = s1.length() - 1;
    int j = s2.length() - 1;
    int acarreo = 0;    
    //recorremos mientras haya un digito o accarreo que operar  
    while (i >= 0 || j >= 0 || acarreo > 0) {
        int suma = acarreo;

        // Si hay digitos en s1, los sumamos y movemos el índice 
        if (i >= 0) {
            suma += s1[i] - '0'; 
            i--;
        }
        // Si hay dígitos en s2, los sumamos y movemos el índice
        if (j >= 0) {
            suma += s2[j] - '0';
            j--;
        }
        acarreo = suma / 10;
        int digitoActual = suma % 10;
        resultado += to_string(digitoActual);
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}


string quitarCerosIzquierda(string s) {
    int idx = 0; //primera coincidencia de valor mayor a 0
    
    while (idx < s.length() && s[idx] == '0') {
        idx++;
    }
    // Si todo son 0
    if (idx == s.length()) {
        return "0";
    }
    // retonarmos apartir de un valor valido
    return s.substr(idx);
}
 

string restarCadenas(string s1, string s2) {
    string resultado = "";
    int i = s1.length() - 1;
    int j = s2.length() - 1;
    int prestamo = 0; 
    
    while (i >= 0) {
        int resta = (s1[i] - '0') - prestamo;
        i--;

        // Si todavía hay dígitos en s2, los restamos
        if (j >= 0) {
            resta -= (s2[j] - '0');
            j--;
        }

        // Si la resta es negativa, pedimos un préstamo de 10 a la columna siguiente
        if (resta < 0) {
            resta += 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }

        resultado += to_string(resta);
    }

    reverse(resultado.begin(), resultado.end());
    return quitarCerosIzquierda(resultado);

}

string aumentarCeros(string s, int k){
    if (s == "0" || k == 0) {
        return s;
    }
    // Concatenamos 'k' caracteres '0' al final de la cadena
    s.append(k, '0');
    
    return s;
}



string multiplicacionEnterosGrandes(string x, string y){
    x = quitarCerosIzquierda(x);
    y = quitarCerosIzquierda(y);

    if(x.length() <= 1 && y.length() <= 1){
        int val1 = x.empty() ? 0 : x[0] - '0';
        int val2 = y.empty() ? 0 : y[0] - '0';
        return to_string(val1 * val2);
    }

    //igualamos longitudes rellenando con ceros a la izquierda
    int maxLen = max(x.length(), y.length());
    while (x.length() < maxLen) x = "0" + x;
    while (y.length() < maxLen) y = "0" + y;

    //Partimos a la mitad
    int n = maxLen;
    int m = n / 2;

    string A = x.substr(0, n - m);
    string B = x.substr(n - m);
    string C = y.substr(0, n - m);
    string D = y.substr(n - m);

    string P1 = multiplicacionEnterosGrandes(A, C);
    string P2 = multiplicacionEnterosGrandes(B, D);

    string sumaAB = sumarCadenas(A, B);
    string sumaCD = sumarCadenas(C, D);
    string P3 = multiplicacionEnterosGrandes(sumaAB, sumaCD);

    //Términos cruzados = P3 - P1 - P2
    string resta1 = restarCadenas(P3, P1);
    string cruzados = restarCadenas(resta1, P2);

    //Desplazamiento por potencias de 10
    string term1 = aumentarCeros(P1, 2 * m);
    string term2 = aumentarCeros(cruzados, m);

    //Combinando sumas
    string sumaParcial = sumarCadenas(term1, term2);
    string resultadoFinal = sumarCadenas(sumaParcial, P2);

    return quitarCerosIzquierda(resultadoFinal);
}

int main(){
    string num1;
    string num2;
    cin >> num1 >> num2;
    string resultado = multiplicacionEnterosGrandes(num1, num2);
    cout << resultado <<"\n";

    return 0;
}
