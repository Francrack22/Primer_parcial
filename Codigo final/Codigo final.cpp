// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>      
#include <cmath>         
#include <stack>         
#include <forward_list>  
#include <string>        
#include <stdexcept>     
using namespace std;

// BinarySearchTree
template <typename T>
class BinarySearchTree
{
public:
    // Clase interna para representar cada nodo del árbol
    class Node
    {
    public:
        T data;        // Valor que guarda el nodo
        Node* left;    
        Node* right;   
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    BinarySearchTree();    
    ~BinarySearchTree();   

    void Add(T value);   
    bool Contains(T value);
    void Remove(T value); 
    void PrintInOrder();   

    void PostOrderIterativo();
    void BorrarSubarbol(Node* nodo); 

private:
    Node* root; 

    Node* AddRec(Node* node, T value); 
    void PrintInOrderRec(Node* node);  
    void RemoveRec(Node*& node, T value); 
    Node* FindMin(Node* node); // Encontrar el mínimo de un subárbol
};


// BinarySearchTree
template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr; 
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    // Cuando se destruye el árbol, borramos todos los nodos
    BorrarSubarbol(root);
}

template <typename T>
void BinarySearchTree<T>::BorrarSubarbol(Node* nodo)
{
    if (!nodo) return; // Si el nodo es nulo, no hacemos nada
    BorrarSubarbol(nodo->left);  
    BorrarSubarbol(nodo->right); 
    delete nodo; // Al final borramos el nodo actual
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::AddRec(Node* node, T value)
{
    if (!node) return new Node(value); // Si no existe, creamos un nuevo nodo
    if (value < node->data)
        node->left = AddRec(node->left, value);  
    else
        node->right = AddRec(node->right, value); 
    return node;
}

template <typename T>
void BinarySearchTree<T>::Add(T value)
{
    root = AddRec(root, value); // Insertamos usando la función recursiva
}

template <typename T>
bool BinarySearchTree<T>::Contains(T value)
{
    Node* actual = root; // Comenzamos desde la raíz
    while (actual) 
    {
        if (actual->data == value) return true; 
        actual = (value < actual->data) ? actual->left : actual->right; 
    }
    return false; 
}

template <typename T>
void BinarySearchTree<T>::PrintInOrderRec(Node* node)
{
    if (!node) return;
    PrintInOrderRec(node->left); 
    cout << node->data << " ";   // Imprimimos el nodo actual
    PrintInOrderRec(node->right);
}

template <typename T>
void BinarySearchTree<T>::PrintInOrder()
{
    PrintInOrderRec(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::RemoveRec(Node*& node, T value)
{
    if (!node) return; // No hay nada que borrar si es nulo
    if (value < node->data)
        RemoveRec(node->left, value);
    else if (value > node->data)
        RemoveRec(node->right, value);
    else
    {
        if (!node->left)
        {
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (!node->right)
        {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else
        {
            Node* temp = FindMin(node->right);
            node->data = temp->data;
            RemoveRec(node->right, temp->data);
        }
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::FindMin(Node* node)
{
    while (node && node->left)
        node = node->left; // El mínimo siempre está lo más a la izquierda posible
    return node;
}

template <typename T>
void BinarySearchTree<T>::Remove(T value)
{
    RemoveRec(root, value);
}

template <typename T>
void BinarySearchTree<T>::PostOrderIterativo()
{
    if (!root) return;
    stack<Node*> pila; // Pila para recorrer
    Node* ultimoVisitado = nullptr;
    Node* actual = root;

    while (!pila.empty() || actual)
    {
        if (actual)
        {
            pila.push(actual);
            actual = actual->left;
        }
        else
        {
            Node* tope = pila.top();
            if (tope->right && ultimoVisitado != tope->right)
            {
                actual = tope->right;
            }
            else
            {
                cout<<tope->data << " ";
                ultimoVisitado = tope;
                pila.pop();
            }
        }
    }
    cout<<endl;
}

// Clase HashTableChaining del curso

template <typename T>
class HashTableChaining
{
protected:
    forward_list<T>* data; // Arreglo de listas enlazadas
    unsigned int arraySize; // Tamaño de la tabla

    int HashFunction(T key)
    {
        return key % arraySize; // Función hash sencilla
    }

public:
    HashTableChaining(unsigned int size)
    {
        data = new forward_list<T>[size]; // Reservamos memoria
        arraySize = size;
    }

    virtual void Add(T element)
    {
        int index = HashFunction(element);
        data[index].push_front(element); // Insertamos al inicio de la lista
    }

    void Remove(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];
        for (auto i : listAtIndex)
        {
            if (i == element)
            {
                listAtIndex.remove(i);
                return;
            }
        }
        throw runtime_error("No existe el elemento " + to_string(element));
    }

    bool Contains(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];
        for (auto i : listAtIndex)
        {
            if (i == element)
            {
                return true;
            }
        }
        return false;
    }

    void Print()
    {
        for (int i = 0; i < arraySize; i++)
        {
            cout<<"Lista en índice "<<i<<": ";
            for (auto j : data[i])
                cout<<j<<", ";
            cout<<endl;
        }
    }
};

// Clase HashSet 

template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    HashSet(unsigned int size) : HashTableChaining<T>(size) {}

    void Add(T element) override
    {
        int index = this->HashFunction(element);
        for (auto val : this->data[index])
        {
            if (val == element) return; // Evitamos duplicados
        }
        this->data[index].push_front(element);
    }
};

// Funciones de cálculo de altura mínima

double log_base_n(double x, double base)
{
    return log(x) / log(base);
}

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    int formula = ((maximoDeHijosPorNodo - 1) * numeroDeNodos + 1);
    int altura = ceil(log_base_n(formula, maximoDeHijosPorNodo)) - 1; // en el código original se usaba una variable incorrecta en logBase(...) 
// Ahora usamos 'formula' para que el cálculo sea correcto.

    return altura;
}

// Función principal para probar

int main()
{
    cout<<"Altura mínima con 9 nodos y máx 2 hijos: "
        <<MinimaAlturaDeArbol(9, 2)<<endl;

    BinarySearchTree<int> arbol;
    arbol.Add(5);
    arbol.Add(3);
    arbol.Add(8);
    arbol.Add(2);
    arbol.Add(4);
    arbol.Add(7);
    arbol.Add(9);

    cout<<"Búsqueda de 7: "<<(arbol.Contains(7) ? "Encontrado" : "No encontrado")<<endl;

    cout<<"Post-order iterativo: ";
    arbol.PostOrderIterativo();

    HashSet<int> conjunto(5);
    conjunto.Add(10);
    conjunto.Add(20);
    conjunto.Add(10);
    cout<<"Contenido de HashSet:"<<endl;
    conjunto.Print();

    return 0;
}

// Utilizamos un video de YT para apoyarnos: Hash Tables and Hash Functions
// Y tambien utilizamos la IA para poyarnos a encontrar el error en el codigo que dejo usted
// primero lo checamos nosotros y ya que creiamos haberlo encontrado lo confirmamos con Chatgpt y nos dio algunas recomendaciones
// creo que si si entendimos bien lo que nos pide, ya quedó bien profe
