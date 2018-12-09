#include <iostream>
using namespace std;

struct nodo{
	int dato;
	nodo *sig;
}*pInicio;


void insertar_cabeza(nodo **lista){
	nodo *nuevo = new nodo;
	cout<<"Ingrese el nuevo dato"<<endl;
	cin>>nuevo->dato;
	
	if(*lista==NULL){
		nuevo->sig=nuevo;
		
	}
	else{
		nodo *s= *lista;
		nodo *test = s;
		nuevo->sig=s;
		
		while(s->sig!=test){
			s=s->sig;
		}
		s->sig=nuevo;	
	}
	*lista=nuevo;
}


void insertar_cola(nodo **lista){
	nodo *nuevo = new nodo;
	cout<<"Ingrese el nuevo dato"<<endl;
	cin>>nuevo->dato;
	
	if(*lista==NULL){
		nuevo->sig=nuevo;
		*lista=nuevo;
	}
	else{
		nodo *s= *lista;
		nodo *test = s;
		nuevo->sig=test;

		while(s->sig!=test){
			s=s->sig;
		}

		s->sig=nuevo;
			
	}
}


void mostrar(nodo *s){
		
	nodo *aux=s;
	do{
		cout<<s->dato<<endl;
		s=s->sig;
	}while(s!=aux);
}



int main(){
	pInicio=NULL;
	for(int i=0;i<4;i++){
		insertar_cola(&pInicio);
	}
	cout<<"La lista es: "<<endl;
	mostrar(pInicio);	
	return 0;
}
