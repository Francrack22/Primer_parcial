// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes
#include <iostream>
using namespace std;

// Ejercicio 1
// Función que recibe array de booleanos y tamaño
void modificarBoolArray(bool arr[], int tam) 
{
    // Modificamos el array, índices pares son false, impares true
    for (int i = 0; i < tam; i++) 
    {
        arr[i] = (i % 2 != 0);
    }

}
// Sobrecarga, función que recibe array de enteros y tamaño
void modificarIntArray(int* ptr, int tam) 
{
    // Variable auxiliar para no modificar el puntero original
    int* aux = ptr;
    for (int i = 0; i < tam; i++) 
    {
        // Reemplaza valor por valor % 2 usando aritmética de punteros (sin usar [])
        *aux = (*aux) % 2;
        // Imprime dirección y valor resultante
        cout<<"Dirección: "<<aux<<" | Valor mod 2: "<<*aux<<endl;
        // Mueve a la siguiente dirección de memoria 
        aux++; 
    }
}

// Ejercicio 2
// Estructura Rect con coordenadas X, Y, alto y ancho
struct Rect 
{
    int x, y, alto, ancho;
    // Constructor por defecto todos en 0
    Rect() :x(0), y(0), alto(0), ancho(0) {}
    // Constructor con 4 parámetros
    Rect(int X, int Y, int A, int An) :x(X), y(Y), alto(A), ancho(An) {}
    // Constructor con alto y ancho; X,Y=0
    Rect(int A, int An) :x(0), y(0), alto(A), ancho(An) {}
};

// Función que imprime coordenadas y calcula punto final
bool imprimirRect(const Rect& r, int& xFin, int& yFin) 
{
    if (r.x < 0 || r.y < 0 || r.alto < 0 || r.ancho < 0)return false;
    xFin = r.x + r.ancho;
    yFin = r.y + r.alto;
    cout<<"Rectángulo inicia en ("<<r.x<<","<<r.y<<")\n";
    cout<<"Rectángulo termina en ("<<xFin<<","<<yFin<<")\n";
    return true;
}

// Función que verifica traslape entre dos rectángulos
bool CheckOverlap(const Rect& r1, const Rect& r2) 
{
    // Si uno está completamente a la izquierda del otro, no traslapan
    if (r1.x + r1.ancho <= r2.x || r2.x + r2.ancho <= r1.x)return false;
    // Si uno está completamente arriba o abajo del otro, no traslapan
    if (r1.y + r1.alto <= r2.y || r2.y + r2.alto <= r1.y)return false;
    return true; // sí traslapan
}

int main() 
{
    // Ejercicio 1
    // Arreglo booleano y modificación
    bool boolArr[5];
    modificarBoolArray(boolArr, 5);
    cout<<"Arreglo booleano modificado:\n";
    for (int i = 0; i < 5; i++) 
    {
        cout<<"Índice "<<i<<": " <<boolalpha<<boolArr[i]<<endl;
    }
    // Arreglo de enteros inicializado 0 a 9
    int intArr[10];
    for (int i = 0; i < 10; i++)intArr[i] = i;
    cout<<"\nArreglo entero modificado usando punteros:\n";
    modificarIntArray(intArr, 10);

    // Ejercicio 2
    // Crear rectángulos según ejemplos dados
    Rect a(0, 0, 5, 5), b(6, 6, 5, 5), c(2, 2, 2, 2), d(1, 1, 7, 2);
    int xEnd, yEnd;

    cout<<"\nRectángulo A:\n"; imprimirRect(a, xEnd, yEnd);
    cout<<"Rectángulo B:\n"; imprimirRect(b, xEnd, yEnd);
    cout<<"Rectángulo C:\n"; imprimirRect(c, xEnd, yEnd);
    cout<<"Rectángulo D:\n"; imprimirRect(d, xEnd, yEnd);

    // Mostrar los resultados de traslape 
        // aqui usamos el if de una sola linea, muestra si es verdadero o no dependiendo si sea "si" o "no"
    cout<<"\n¿A y B se traslapan? "<<(CheckOverlap(a, b) ? "Sí" : "No")<<endl;
    cout<<"¿A y C se traslapan? "<<(CheckOverlap(a, c) ? "Sí" : "No")<<endl;
    cout<<"¿A y D se traslapan? "<<(CheckOverlap(a, d) ? "Sí" : "No")<<endl;

    // Ejercicio 3
    // Declarar puntero a float y asignar nullptr
    float* ptr = nullptr;
    // Pedir memoria dinámica y asignar 7.77
    ptr = new float(7.77f);
    // Variable float con valor 6.66
    float var = 6.66f;
    // Hacer que el ptr apunte a var 
    ptr = &var;
    // Mostrara el mensaje de memory leak
    cout<<"\nCuidado, acabas de causar un memory leak!" << endl;
    // Explicación sobre el memory leak
    cout<<"Eso pasa porque estaws reservando memoria dinamica y no se esta liberando, por lo tanto se sigue consumiendo memoria RAM."<<endl;
    cout<<"Para que no pase hay que usar un delete."<<endl;

    // Pedir memoria dinámica otra vez para ptr y asignar 1984
    ptr = new float(1984.0f);
    // Nuevo puntero ptr2 apuntando a misma dirección
    float* ptr2 = ptr;
    // Liberar memoria dinámica y asignar nullptr a ptr
    delete ptr;
    ptr = nullptr;

    // Checar si ptr es nullptr
    if (ptr == nullptr)cout<<"ptr es igual a nullptr"<<endl;
    // Checar si ptr es NULL
    if (ptr == NULL)cout<<"ptr es igual a NULL"<<endl;
    // Checar ptr2 si es nullptr o NULL
    if (ptr2 != nullptr && ptr2 != NULL)cout<<"ptr2 no es nullptr ni NULL, cuidado por que ya se borro la variable a donde apunta."<<endl;

    return 0;
}
// Utilizamos un video de youtube llamado "Programación en C++ || Condicionales || La sentencia if" para entender un poco mas como hacer eso del if en una sola linea
// Y usamos chatgpt para preguntarle si lo estabamos haciendo correctamente y asi acabar de entender bien como se hace
