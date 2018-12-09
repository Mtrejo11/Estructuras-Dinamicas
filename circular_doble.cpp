#include <iostream>
using namespace std;

struct nodo{
	
	int dato;
	nodo *sig;
	nodo *ant;
}*lista;


void llenar(nodo **l,int num){
	nodo *nuevo = new nodo;
	nuevo->dato = num;
	if(*l==NULL){
		nuevo->ant=nuevo;
		nuevo->sig=nuevo;
		*l=nuevo;
	}else{
		nodo *s = *l;
		nodo *ref = s;
		while(s->sig!=ref){
			s=s->sig;
		}
		s->sig=nuevo;
		nuevo->ant=s;
		nuevo->sig=*l;
		(*l)->ant=nuevo;
	}
	
}

void mostrar(nodo *l,nodo *ref){

	if(l->sig!=ref){
		cout<<l->dato<<endl;
		mostrar(l->sig,ref);
	}else{
		cout<<l->dato<<endl;
		
	}	
}




void mostrar2(nodo *l,nodo *ref){

	if(l->ant!=ref){
		cout<<l->ant->dato<<endl;
		mostrar(l->ant,ref);
	}else{
	//	cout<<"se sale"<<endl;
	//	cout<<l->dato<<endl;
		
	}	
}

void retroceso(nodo *l,nodo *ref){
	if(l->sig!=ref){
		retroceso(l->sig,ref);
	}
	else{
			mostrar2(l,l);	
	}

}

void inversa(nodo *l){
	nodo *s=l;
	s=s->ant;
	do{
		cout<<s->dato<<endl;
		s=s->ant;
	}while(s!=l);
		cout<<s->dato<<endl;
	
}


int main(){
	lista=NULL;
	
	cout<<"Lista circular doble"<<endl<<endl;
	
	for(int i=1;i<=5;i++){
		cout<<"llena"<<endl;
		llenar(&lista,i);
	}
	
	mostrar(lista,lista);
	cout<<"--------"<<endl;
//	inversa(lista);
	retroceso(lista,lista);
	
}
