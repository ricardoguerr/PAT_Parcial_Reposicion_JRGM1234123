#include "Ejercicio01.h"

Node<int>* Ejercicio01::reverseList(Node<int>* head)
{
	Node<int>* anterior = nullptr;
	Node<int>* siguiente = nullptr;
	Node<int>* actual = head;
	while (actual != nullptr) {
		siguiente = actual->next;
		actual->next = anterior;
		anterior = actual;
		actual = siguiente;
	}
	return anterior;
}

Node<int>* Ejercicio01::addTwoNumbers(Node<int>* l1, int sizeL1, Node<int>* l2, int sizeL2)
{
	Node<int>* lista1Invertida = reverseList(l1);
	Node<int>* lista2Invertida = reverseList(l2);
	Node<int>* lista3 = new Node<int>{ 0 };
	Node<int>* nodoLista3 = lista3;
	int acarreo = 0;
	while (lista1Invertida != nullptr || lista2Invertida != nullptr) {
		int suma = acarreo;
		if (lista1Invertida != nullptr) {
			suma += lista1Invertida->value;
			lista1Invertida = lista1Invertida->next;
		}
		if (lista2Invertida != nullptr) {
			suma += lista2Invertida->value;
			lista2Invertida = lista2Invertida->next;
		}
		nodoLista3->next = new Node<int>{ suma % 10 };
		nodoLista3 = nodoLista3->next;
		acarreo = suma / 10;
	}
	if (acarreo > 0) {
		nodoLista3->next = new Node<int>{ acarreo };
	}
	return reverseList(lista3->next);
}
