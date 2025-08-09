// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>        
#include <cmath>           
#include <stack>           
#include <vector>          
#include <list>            
using namespace std;

// Error corregido
double logBase(double valor, double base) 
{
    return log(valor) / log(base); 
}

// Calcula la altura mínima de un árbol según el número de nodos y máximo de hijos
int calcularAlturaMinima(int nodos, int hijosMax) 
{
    int formula = (hijosMax - 1) * nodos + 1;                      
    int altura = ceil(logBase(formula, hijosMax)) - 1;              // usa el logaritmo y redondeo hacia arriba
    return altura;                                                  // Regresae la altura mínima
}

// Clase Nodo del Árbol Binario de Búsqueda
struct Nodo 
{
    int valor;           // Dato almacenado
    Nodo* izquierdo;     // Puntero al hijo izquierdo
    Nodo* derecho;       // Puntero al hijo derecho

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

// Clase Binary Search Tree
class BST 
{
private:
    Nodo* raiz; // Nodo raíz del árbol

    // Inserción recursiva
    Nodo* insertar(Nodo* nodo, int valor) 
    {
        if (!nodo) return new Nodo(valor);            // Si el nodo está vacío, se crea uno nuevo
        if (valor < nodo->valor) nodo->izquierdo = insertar(nodo->izquierdo, valor);
        else nodo->derecho = insertar(nodo->derecho, valor);
        return nodo;
    }

    // post-order
    void borrarSubarbol(Nodo* nodo) 
    {
        if (!nodo) return;
        borrarSubarbol(nodo->izquierdo);   // Primero subárbol izquierdo
        borrarSubarbol(nodo->derecho);     // Luego subárbol derecho
        delete nodo;                       // al final borra el nodo actual
    }

public:
    BST() : raiz(nullptr) {}
    ~BST() { borrarSubarbol(raiz); } // Destructor para liberar memoria

    // Inserción pública
    void insertar(int valor) 
    {
        raiz = insertar(raiz, valor);
    }

    // Búsqueda iterativa
    bool buscar(int valor) 
    {
        Nodo* actual = raiz;
        while (actual) 
        {
            if (valor == actual->valor) return true;
            actual = (valor < actual->valor) ? actual->izquierdo : actual->derecho;
        }
        return false;
    }

    // Recorrido Post-order iterativo
    void postOrderIterativo() 
    {
        if (!raiz) return;
        stack<Nodo*> pila;
        Nodo* ultimoVisitado = nullptr;
        Nodo* actual = raiz;

        while (!pila.empty() || actual) 
        {
            if (actual) 
            {
                pila.push(actual);
                actual = actual->izquierdo;
            }
            else 
            {
                Nodo* tope = pila.top();
                if (tope->derecho && ultimoVisitado != tope->derecho) 
                {
                    actual = tope->derecho;
                }
                else 
                {
                    cout<<tope->valor<<" ";
                    ultimoVisitado = tope;
                    pila.pop();
                }
            }
        }
        cout<<endl;
    }
};

// Clase HashTable 
class HashTableChaining 
{
protected:
    vector<list<int>> tabla; // Tabla con listas para manejar colisiones
    int capacidad;           // Número de posiciones

    int hashFuncion(int clave) const 
    {
        return clave % capacidad;
    }

public:
    HashTableChaining(int cap) : capacidad(cap) 
    {
        tabla.resize(capacidad);
    }

    virtual void insertar(int valor) 
    {
        int indice = hashFuncion(valor);
        tabla[indice].push_back(valor);
    }

    // Muestra la tabla
    void mostrar() const 
    {
        for (int i = 0; i < capacidad; i++) 
        {
            cout<<i<<": ";
            for (int val : tabla[i]) cout<<val << " -> ";
            cout<<"NULL\n";
        }
    }
};

// Clase HashSet 
class HashSet : public HashTableChaining 
{
public:
    HashSet(int cap) : HashTableChaining(cap) {}

    void insertar(int valor) override 
    {
        int indice = hashFuncion(valor);
        for (int val : tabla[indice]) 
        {
            if (val == valor) return; 
        }
        tabla[indice].push_back(valor);
    }
};

// La funcion para probar
int main() {
    cout<<"Altura minima con 9 nodos y max 2 hijos: "
        <<calcularAlturaMinima(9, 2)<<endl;

    BST arbol;
    arbol.insertar(5);
    arbol.insertar(3);
    arbol.insertar(8);
    arbol.insertar(2);
    arbol.insertar(4);
    arbol.insertar(7);
    arbol.insertar(9);

    cout<<"Busqueda de 7: "<<(arbol.buscar(7) ? "Encontrado" : "No encontrado")<<endl;

    cout<<"Post-order iterativo: ";
    arbol.postOrderIterativo(); 

    HashSet conjunto(5);
    conjunto.insertar(10);
    conjunto.insertar(20);
    conjunto.insertar(10); 
    cout<<"Contenido de HashSet:\n";
    conjunto.mostrar();

    return 0;
}

// Utilizamos un video de YT para apoyarnos: Hash Tables and Hash Functions
// Y tambien utilizamos la IA para poyarnos a encontrar el error en el codigo que dejo usted
// primero lo checamos nosotros y ya que creiamos haberlo encontrado lo confirmamos con Chatgpt y nos dio algunas recomendaciones