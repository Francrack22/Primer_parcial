// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>
using namespace std;

// Directiva para contar las copias en el arreglo dinámico
#define COUNT_DYNAMIC_ARRAY_COPIES 1

// Función template para imprimir un array de cualquier tipo
template <typename T>
void PrintArray(T* array, int size) 
{
    // Recorremos el array e imprimimos cada elemento
    for (int i = 0; i < size; ++i)
        cout<<array[i] << " ";
    cout<<endl;
}

// Clase DynamicArray usando plantillas 
template <typename T>
class DynamicArray 
{
private:
    T* data;           // Apuntador al arreglo dinámico
    int capacity;      // Capacidad total
    int count;         // Número de elementos actuales

#if COUNT_DYNAMIC_ARRAY_COPIES
    int copyCounter = 0; // Contador de copias para debug
#endif

    // Función privada para redimensionar el arreglo
    void resize(int newCapacity) 
    {
        T* newData = new T[newCapacity]; // Nuevo arreglo
        for (int i = 0; i < count; ++i) 
        {
            newData[i] = data[i]; // Copiamos datos
#if COUNT_DYNAMIC_ARRAY_COPIES
            copyCounter++;        // Contamos copias solo si está activado
#endif
        }
        delete[] data; // Liberamos memoria anterior
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor inicializa todo en 0 
    DynamicArray() : data(nullptr), capacity(0), count(0) {}

    // Agrega un nuevo elemento al final
    void Append(const T& value) 
    {
        if (count >= capacity) 
        {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[count++] = value;
    }

    // Sobrecarga del operador para acceder a elementos como array
    T& operator[](int index) 
    {
        return data[index];
    }

    // push_back: agrega un nuevo elemento al final
    void push_back(const T& value) 
    {
        Append(value);
    }

    // pop_back: elimina el último elemento
    void pop_back() 
    {
        if (count > 0)
            count--;
    }

    // shrink_to_fit: ajusta la capacidad al número de elementos reales
    void shrink_to_fit() 
    {
        if (capacity > count)
            resize(count);
    }

    // Devuelve número de elementos actuales
    int size() const { return count; }

    // Devuelve número de copias hechas (solo si se activa el define)
    int getCopyCount() const 
    {
#if COUNT_DYNAMIC_ARRAY_COPIES
        return copyCounter;
#else
        return -1;
#endif
    }

    // Destructor libera la memoria usada
    ~DynamicArray() 
    {
        delete[] data;
    }
};

    // Clase LinkedList tipo forward list
template <typename T>
class LinkedList 
{
private:
    // Estructura interna para nodos
    struct Node 
    {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head; // Puntero al primer nodo

public:
    // Constructor: lista vacía
    LinkedList() : head(nullptr) {}

    // Inserta al inicio
    void push_front(const T& value) 
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Elimina primer nodo
    void pop_front() 
    {
        if (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp; // Libera memoria del nodo eliminado
        }
    }

    // Imprime los elementos de inicio a fin
    void Print() 
    {
        Node* curr = head;
        while (curr) 
        {
            cout<<curr->data<<" ";
            curr = curr->next;
        }
        cout << endl;
    }

    // Libera toda la memoria usada por la lista
    void Clear() 
    {
        Node* curr = head;
        while (curr) 
        {
            Node* next = curr->next;
            delete curr; // Se libera memoria nodo por nodo
            curr = next;
        }
        head = nullptr;
    }

    // Se asegura de liberar memoria al final
    ~LinkedList() 
    {
        Clear(); // Llama a función que libera nodo por nodo
    }
};

int main() 
{
    // DynamicArray
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    cout<<"Contenido del DynamicArray:\n";
    PrintArray(&arr[0], arr.size()); // Imprime el arreglo dinámico

    cout<<"Elemento en posición 0: "<<arr[0]<<endl;

    arr.pop_back(); // Elimina el último elemento
    arr.shrink_to_fit(); // Ajusta la capacidad a la cantidad de elementos

    cout<<"Copias realizadas: "<<arr.getCopyCount()<<endl;

    // LinkedList
    LinkedList<string> list;
    list.push_front("mundo");
    list.push_front("Hola");

    cout<<"\nContenido de la LinkedList:\n";
    list.Print(); // Imprime la lista

    list.pop_front(); // Elimina el primer nodo
    cout<<"Después de pop_front:\n";
    list.Print(); // Imprime otra vez

    return 0;
}

// Nos apoyamos de la IA para averiguar si hacía falta liberar memoria en LinkedList.
// Videos de YT que nos ayudaron tambien: C++ Tutorial - LINKED LISTS.   Curso de Programacion en C++ | 06 Directivas de preprocesador
