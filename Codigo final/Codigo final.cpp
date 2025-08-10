// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>
#include <forward_list>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

// BinarySearchTree.h
template <typename T>
class BinarySearchTree
{
public:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
	};

	Node* root;

	BinarySearchTree();
	void Insert(Node*& node, T data);
	void Insert(T data);
	void InOrder(Node* node);
	void InOrder();
	void PreOrder(Node* node);
	void PreOrder();
	void PostOrder(Node* node);
	void PostOrder();
	bool Search(T data); // en el original era recursivo, ahora será iterativo
	void borrarSubarbol(Node* nodo); 
	void PostOrderIterativo();      
};

// BinarySearchTree.cpp 
template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}

template <typename T>
void BinarySearchTree<T>::Insert(Node*& node, T data)
{
	if (node == nullptr)
	{
		node = new Node{ data, nullptr, nullptr };
	}
	else
	{
		if (data < node->data)
			Insert(node->left, data);
		else
			Insert(node->right, data);
	}
}

template <typename T>
void BinarySearchTree<T>::Insert(T data)
{
	Insert(root, data);
}

template <typename T>
void BinarySearchTree<T>::InOrder(Node* node)
{
	if (node != nullptr)
	{
		InOrder(node->left);
		cout<<node->data<<" ";
		InOrder(node->right);
	}
}

template <typename T>
void BinarySearchTree<T>::InOrder()
{
	InOrder(root);
	cout<<endl;
}

template <typename T>
void BinarySearchTree<T>::PreOrder(Node* node)
{
	if (node != nullptr)
	{
		cout<<node->data<<" ";
		PreOrder(node->left);
		PreOrder(node->right);
	}
}

template <typename T>
void BinarySearchTree<T>::PreOrder()
{
	PreOrder(root);
	cout << endl;
}

template <typename T>
void BinarySearchTree<T>::PostOrder(Node* node)
{
	if (node != nullptr)
	{
		PostOrder(node->left);
		PostOrder(node->right);
		cout<<node->data<<" ";
	}
}

template <typename T>
void BinarySearchTree<T>::PostOrder()
{
	PostOrder(root);
	cout << endl;
}

// FUNCIONES NUEVAS

// Búsqueda iterativa
template <typename T>
bool BinarySearchTree<T>::Search(T data)
{
	Node* actual = root;
	while (actual)
	{
		if (data == actual->data) return true;
		actual = (data < actual->data) ? actual->left : actual->right;
	}
	return false;
}

// post-order rescursivo
template <typename T>
void BinarySearchTree<T>::borrarSubarbol(Node* nodo)
{
	if (!nodo) return;
	borrarSubarbol(nodo->left);
	borrarSubarbol(nodo->right);
	delete nodo;
}

// Post-order iterativo
template <typename T>
void BinarySearchTree<T>::PostOrderIterativo()
{
	if (!root) return;
	stack<Node*> pila;
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
				cout << tope->data << " ";
				ultimoVisitado = tope;
				pila.pop();
			}
		}
	}
	cout << endl;
}

// HashTableChaining.h 
template <typename T>
class HashTableChaining
{
	forward_list<T>* data;
	unsigned int arraySize;

public:
	HashTableChaining(unsigned int size)
	{
		data = new forward_list<T>[size];
		arraySize = size;
	}

	int HashFunction(T key)
	{
		return key % arraySize;
	}

	virtual void Add(T element)
	{
		int index = HashFunction(element);
		data[index].push_front(element);
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
		throw runtime_error("no element " + to_string(element) + " in this hash table.");
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
			cout<<"lista del índice: "<<std::to_string(i)<<": ";
			for (auto j : data[i])
				cout<<j<<", ";
			cout<<endl;
		}
	}
};

// HashSet 
template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
	HashSet(unsigned int size) : HashTableChaining<T>(size) {}

	void Add(T element) override
	{
		if (!this->Contains(element))
		{
			HashTableChaining<T>::Add(element);
		}
	}
};

// nuestra función auxiliar
// Error corregido la fórmula usaba mal el número de nodos
double logBase(double valor, double base)
{
	return log(valor) / log(base);
}

int calcularAlturaMinima(int nodos, int hijosMax)
{
	int formula = (hijosMax - 1) * nodos + 1;
	int altura = ceil(logBase(formula, hijosMax)) - 1;
	return altura;
}

// Función principal para probar
int main()
{
	cout<<"Altura mínima con 9 nodos y max 2 hijos: "
	<<calcularAlturaMinima(9, 2)<<endl;

	// Prueba de BinarySearchTree con funciones nuevas
	BinarySearchTree<int> arbol;
	arbol.Insert(5);
	arbol.Insert(3);
	arbol.Insert(8);
	arbol.Insert(2);
	arbol.Insert(4);
	arbol.Insert(7);
	arbol.Insert(9);

	cout<<"Busqueda de 7: "<<(arbol.Search(7) ? "Encontrado" : "No encontrado")<<endl;

	cout<<"Post-order iterativo: ";
	arbol.PostOrderIterativo();

	// Prueba de HashSet
	HashSet<int> conjunto(5);
	conjunto.Add(10);
	conjunto.Add(20);
	conjunto.Add(10); // repetido
	cout<<"Contenido de HashSet:\n";
	conjunto.Print();

	return 0;
}

// Utilizamos un video de YT para apoyarnos: Hash Tables and Hash Functions
// Y tambien utilizamos la IA para poyarnos a encontrar el error en el codigo que dejo usted
// primero lo checamos nosotros y ya que creiamos haberlo encontrado lo confirmamos con Chatgpt y nos dio algunas recomendaciones
// creo que si si entendimos bien lo que nos pide, ya quedó bien profe
