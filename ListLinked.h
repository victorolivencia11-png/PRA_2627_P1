#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first;
        int n;

    public:
        ListLinked() {
            first = nullptr;
            n = 0;
        }

        ~ListLinked() override {
            while (first != nullptr) {
                Node<T>* aux = first;
                first = first->next;
                delete aux;
            }
        }

        int size() override {
            return n;
        }

        bool empty() override {
            return n == 0;
        }

        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                Node<T>* aux = first;
                for (int i = 0; i < pos - 1; i++) {
                    aux = aux->next;
                }
                aux->next = new Node<T>(e, aux->next);
            }
            n++;
        }

        void append(T e) override {
            insert(n, e);
        }

        void prepend(T e) override {
            insert(0, e);
        }

        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            Node<T>* aux;
            T data;

            if (pos == 0) {
                aux = first;
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                aux = prev->next;
                prev->next = aux->next;
            }

            data = aux->data;
            delete aux;
            n--;
            return data;
        }

        T get(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        int search(T e) override {
            Node<T>* aux = first;
            int i = 0;
            while (aux != nullptr) {
                if (aux->data == e) {
                    return i;
                }
                aux = aux->next;
                i++;
            }
            return -1;
        }

        T operator[](int pos) override {
            return get(pos);
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream &out, const ListLinked<U> &list);
};

template <typename U>
std::ostream& operator<<(std::ostream &out, const ListLinked<U> &list) {
    Node<U>* aux = list.first;
    out << "[";
    while (aux != nullptr) {
        out << aux->data;
        if (aux->next != nullptr) {
            out << ", ";
        }
        aux = aux->next;
    }
    out << "]";
    return out;
}

#endif
