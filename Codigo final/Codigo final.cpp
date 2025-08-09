// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>        
#include <cmath>           
#include <stack>           
#include <vector>          
#include <list>            

// Error corregido en, habia un menos 1 al final que hacia que devolviero mal el resultado
double logBase(double valor, double base) 
{
    return std::log(valor) / std::log(base); 
}

// Calcula la altura mínima de un árbol según el número de nodos y máximo de hijos
int calcularAlturaMinima(int nodos, int hijosMax) 
{
    int formula = (hijosMax - 1) * nodos + 1;                       
    int altura = static_cast<int>(std::ceil(logBase(formula, hijosMax))); // corregido sin restar 1
    return altura;                                                  // Regresa la altura mínima
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

    // Inserción recursiva con control para evitar duplicados
    Nodo* insertar(Nodo* nodo, int valor) 
    {
        if (!nodo) return new Nodo(valor);            // Si el nodo está vacío, se crea uno nuevo
        if (valor < nodo->valor) nodo->izquierdo = insertar(nodo->izquierdo, valor);
        else if (valor > nodo->valor) nodo->derecho = insertar(nodo->derecho, valor);
        // Si valor == nodo->valor, no inserta para evitar duplicados
        return nodo;
    }

    // post-order iterativo usando dos stacks (más sencillo y confiable)
    void postOrderIterativoAux(Nodo* nodo) 
    {
        if (!nodo) return;
        std::stack<Nodo*> pila1, pila2;
        pila1.push(nodo);
        while (!pila1.empty()) 
        {
            Nodo* actual = pila1.top();
            pila1.pop();
            pila2.push(actual);
            if (actual->izquierdo) pila1.push(actual->izquierdo);
            if (actual->derecho) pila1.push(actual->derecho);
        }
        while (!pila2.empty()) 
        {
            std::cout << pila2.top()->valor << " ";
            pila2.pop();
        }
    }

    // Liberar memoria recursivamente
    void borrarSubarbol(Nodo* nodo) 
    {
        if (!nodo) return;
        borrarSubarbol(nodo->izquierdo);
        borrarSubarbol(nodo->derecho);
        delete nodo;
    }

public:
    BST() : raiz(nullptr) {}
    ~BST() { borrarSubarbol(raiz); } // Destructor para liberar memoria

    // Inserción pública
    void insertar(int valor) 
    {
        raiz = insertar(raiz, valor);
    }

    // Búsqueda iterativa que regresa puntero a nodo o nullptr si no encuentra
    Nodo* buscar(int valor) 
    {
        Nodo* actual = raiz;
        while (actual) 
        {
            if (valor == actual->valor) return actual;
            actual = (valor < actual->valor) ? actual->izquierdo : actual->derecho;
        }
        return nullptr;
    }

    // Post-order iterativo público
    void postOrderIterativo() 
    {
        postOrderIterativoAux(raiz);
        std::cout << std::endl;
    }
};

// Clase HashTable con encadenamiento para colisiones
class HashTableChaining 
{
protected:
    std::vector<std::list<int>> tabla; // Tabla con listas para manejar colisiones
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

    // Busca si el valor está en la tabla (útil para evitar duplicados)
    bool buscar(int valor) const
    {
        int indice = hashFuncion(valor);
        for (int val : tabla[indice]) 
        {
            if (val == valor) return true;
        }
        return false;
    }

    // Muestra la tabla
    void mostrar() const 
    {
        for (int i = 0; i < capacidad; i++) 
        {
            std::cout << i << ": ";
            for (int val : tabla[i]) std::cout << val << " -> ";
            std::cout << "NULL\n";
        }
    }
};

// Clase HashSet sin elementos repetidos (hereda de HashTableChaining)
class HashSet : public HashTableChaining 
{
public:
    HashSet(int cap) : HashTableChaining(cap) {}

    void insertar(int valor) override 
    {
        if (!buscar(valor)) // Solo inserta si no está repetido
        {
            HashTableChaining::insertar(valor);
        }
    }
};

// Función principal para probar
int main() {
    std::cout << "Altura minima con 9 nodos y max 2 hijos: "
              << calcularAlturaMinima(9, 2) << std::endl;

    BST arbol;
    arbol.insertar(5);
    arbol.insertar(3);
    arbol.insertar(8);
    arbol.insertar(2);
    arbol.insertar(4);
    arbol.insertar(7);
    arbol.insertar(9);

    Nodo* resultadoBusqueda = arbol.buscar(7);
    std::cout << "Busqueda de 7: " << (resultadoBusqueda ? "Encontrado" : "No encontrado") << std::endl;

    std::cout << "Post-order iterativo: ";
    arbol.postOrderIterativo();

    HashSet conjunto(5);
    conjunto.insertar(10);
    conjunto.insertar(20);
    conjunto.insertar(10); // No se inserta porque ya existe
    std::cout << "Contenido de HashSet:\n";
    conjunto.mostrar();

    return 0;
}

// Utilizamos un video de YT para apoyarnos: Hash Tables and Hash Functions
// Y tambien utilizamos la IA para poyarnos a encontrar el error en el codigo que dejo usted
// primero lo checamos nosotros y ya que creiamos haberlo encontrado lo confirmamos con Chatgpt y nos dio algunas recomendaciones
