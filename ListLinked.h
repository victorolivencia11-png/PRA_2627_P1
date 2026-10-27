#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

// Clase plantilla que implementa la interfaz List como una lista simplemente enlazada
template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first; // Puntero al primer nodo de la lista
        int n; // Cantidad de elementos en la lista

    public:
        // Constructor: inicializa la lista vacía
        ListLinked() {
            first = nullptr;
            n = 0;
        }

        // Destructor: recorre la lista y elimina uno a uno todos los nodos
        ~ListLinked(){
            while (first != nullptr) {
                Node<T>* aux = first;
                first = first->next;
                delete aux;
            }
        }

        // Devuelve el número de elementos actual de la lista
        int size() override {
            return n;
        }

        // Comprueba si la lista está vacía
        bool empty() override {
            return n == 0;
        }

        // Inserta un elemento e en la posición pos
        void insert(int pos, T e) override {
            // Verifica rango válido de inserción [0, n]
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            // Inserción en la primera posición
            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                // Avanza hasta el nodo anterior a la posición deseada
                Node<T>* aux = first;
                for (int i = 0; i < pos - 1; i++) {
                    aux = aux->next;
                }
                // Conecta el nuevo nodo con el resto de la lista y enlaza el anterior a él
                aux->next = new Node<T>(e, aux->next);
            }
            n++;
        }

        // Añade un elemento al final de la lista
        void append(T e) override {
            insert(n, e);
        }

        // Añade un elemento al principio de la lista
        void prepend(T e) override {
            insert(0, e);
        }

        // Elimina y devuelve el valor almacenado en la posición pos
        T remove(int pos) override {
            // Verifica que la posición exista [0, n-1]
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            Node<T>* aux;
            T data;

            // Eliminación del primer elemento
            if (pos == 0) {
                aux = first;
                first = first->next;
            } else {
                // Busca el nodo previo al que se va a eliminar
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                aux = prev->next;
                prev->next = aux->next;
            }

            // Recupera el dato, elimina el nodo de memoria y decrementa el contador
            data = aux->data;
            delete aux;
            n--;
            return data;
        }

        // Retorna el elemento situado en la posición pos
        T get(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango");
            }

            // Recorre los punteros hasta llegar al nodo en pos
            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        // Busca un elemento e y retorna su índice o -1 si no existe
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

        // Sobrecarga del operador [] reutilizando el método get()
        T operator[](int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posicion fuera de rango");
            }
            return get(pos);
        }

        template <typename T>
        std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            
            if(list.n == 0) {
                out << "List => []";
                return out;
            }else{
                out << "List => [\n";
            Node<T>* aux = list.first;
            while (aux != nullptr) {
                out << aux->data;
                if (aux->next != nullptr) {
                    out << ", ";
                }
                aux = aux->next;
            }
            out << "]";
            }
            return out;
        }
};

// Implementación de la sobrecarga del operador << para imprimir ListLinked



#endif