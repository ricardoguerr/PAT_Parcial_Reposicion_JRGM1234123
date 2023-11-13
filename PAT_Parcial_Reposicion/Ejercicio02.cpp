#include "Ejercicio02.h"

Node<char>* Ejercicio02::reverseKGroup(Node<char>* head, int k)
{
    Node<char>* actual = head;
    Node<char>* sig = nullptr;
    Node<char>* anterior = nullptr;
    int size = 0;

    Node<char>* temp = head;
    while (temp != nullptr && size < k) {
        temp = temp->next;
        size++;
    }

    if (size == k) {
        while (size > 0) {
            sig = actual->next;
            actual->next = anterior;
            anterior = actual;
            actual = sig;
            size--;
        }

        if (sig != nullptr) {
            head->next = reverseKGroup(sig, k);
        }

        return anterior;
    }
    else {
        return head;
    }
}
