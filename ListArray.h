#include <iostream>
#include <ostream>
#include <stdexcept>
#include "List.h"

using namespace std;

template <typename T>
class ListArray : public List<T> {

    private:
        T* arr;
        int n;
        static const int MINSIZE = 2;
        int max = MINSIZE;

        void resize(int new_size) {
            T* nuevoarr = new T[new_size];
            for (int i = 0; i < n; i++) {
                nuevoarr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevoarr;
            max = new_size;
        }

        // miembros privados

    public:
        ListArray() {
            arr = new T[MINSIZE];
            n = 0;
            max = MINSIZE;
        }

        ~ListArray() override {
            delete[] arr;
        }

        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw out_of_range("posicion fuera del vector");
            }
            if (n == max) {
                resize(max * 2);
            }
            for (int i = n; i > pos; i--) {
                arr[i] = arr[i - 1];
            }
            arr[pos] = e;
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
                throw out_of_range("posicion fuera del vector");
            }
            T aux = arr[pos];
            for (int i = pos; i < n - 1; i++) {
                arr[i] = arr[i + 1];
            }
            n--;
            return aux;
        }

        T get(int pos) override {
            if (pos < 0 || pos >= n) {
                throw out_of_range("posicion fuera del vector");
            }
            return arr[pos];
        }

        int search(T e) override {
            for (int i = 0; i < n; i++) {
                if (arr[i] == e) {
                    return i;
                }
            }
            return -1;
        }

        bool empty() override {
            return n == 0;
        }

        int size() override {
            return n;
        }

        T& operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("posicion de vector incorrecta");
            }
            return arr[pos];
        }

        friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
            out << "[";
            for (int i = 0; i < list.n; ++i) {
                out << list.arr[i];
                if (i + 1 < list.n) {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }

        // miembros públicos, incluidos los heredados de List<T>

};
