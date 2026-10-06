#include <ostream>
#include <stdexcept>
#include "List.h"
using namespace std
template <typename T> 
class ListArray : public List<T> {

    private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE;
		void resize(int new_size);


        // miembros privados

    public:
			
			void insert(int pos, T e) override {
				int tam=size();
				if(pos < tam){
					resize(tam+1);
				for(int i=tam;i>pos;i--){
					arr[i]=arr[i-1];
				}
				arr[pos]=e;
				}else{
					throw out_of_range("posicion fuera del vector");
				}
			}

			void append(T e) override {
				resize(size()+1);
				arr[size()-1]=e;
			}
			
			void prepend(T e) override {
                                resize(size()+1);
				for(int i=size()-1;i>0;i--){
                                        arr[i]=arr[i-1];
                                }
				arr[0]=e;

			}

			T remove(int pos) override {
				if(pos < tam){
					T aux = arr[pos];
                                	for(int i=pos;i<size()-1;i++){
                                        	arr[i]=arr[i+1];
					}
					resize(size()-1);
					return aux;
                                }


                                }else{
                                       throw out_of_range("posicion fuera del vector");
                                }




			ListArray(){
				arr=new T[MINSIZE];
				n=0;
				max=MINSIZE;
			}

			~ListArray() override {
				delete arr;
			}

			T operator[](int pos){
				if(pos>n||pos<0){
					throw std::out_of_range ("posicion de vector incorrecta");

				return arr[pos];

			friend std::ostream& operator<<(std::ostream &out, ListArray<T> &list){
				for(int i=0; i<

					




        // miembros públicos, incluidos los heredados de List<T>
    
};
