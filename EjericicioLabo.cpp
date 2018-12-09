#include <iostream>
using namespace std;

/*

Una clase tiene dos partes, una privada y una publica.

 	- La parte publica nos permite acceso a todo lo que este dentro de ella desde CUALQUIER PARTE DEL PROGRAMA utilizando
 	  siempre una instancia de esta clase. Instanciar una clase es crear una variable del tipo de esta  clase.
 	- La parte privada solamente puede ser trabajada por cosas que sean de la misma clase. Es decir que si yo tengo funciones 
 	  privadas, solo puedo acceder a ellas desde alguna instruccion en la que el usuario no tenga contacto con ella directamente.



*/

class AdministradorLista{
public:
	//Constructor - siempre publico
	AdministradorLista();
	//Metodos publicos
	void InsertarNodoFinal(int dato);
	void MostrarLista();
	void EliminarNodo(int dato);
	void ActualizarNodo(int viejoDato, int nuevoDato);
private:
	//Atributos privados
	struct nodo{
		int dato;
		struct nodo* siguiente;
	};
	struct nodo* cabeza;
	//Metodos privados
	void ImprimirListaRecursivo(struct nodo* saltarin);
	void QuitarNumeroRecursivo(struct nodo** saltarin, int unNumero);
};

//Constructor
AdministradorLista::AdministradorLista(){
	cabeza = NULL;
}

//Insertar nodos
void AdministradorLista::InsertarNodoFinal(int dato)
{
//	struct nodo* nuevo_nodo =(struct nodo*)malloc(sizeof(struct nodo));
	nodo *nuevo_nodo = new nodo;
	(*nuevo_nodo).dato = dato;
	(*nuevo_nodo).siguiente = NULL;

	if (cabeza == NULL)
	{
		cabeza = nuevo_nodo;
	}
	else
	{
		struct nodo* saltarin = cabeza;
		while((*saltarin).siguiente != NULL)
		{
			saltarin = (*saltarin).siguiente;
		}
		(*saltarin).siguiente = nuevo_nodo;
	}
}

//Mostrar nodos - funcion base
void AdministradorLista::MostrarLista(){
	ImprimirListaRecursivo(cabeza);
}
//Mostrar nodos - funcion recursiva
void AdministradorLista::ImprimirListaRecursivo(struct nodo* saltarin)
{
	if(saltarin == NULL){
		cout << "Lista vacia!" << endl;
		return;
	}
	else{
		cout << (*saltarin).dato << endl;

		if((*saltarin).siguiente != NULL)
			ImprimirListaRecursivo((*saltarin).siguiente);
	}
}

//Eliminar nodos - funcion base
void AdministradorLista::EliminarNodo(int dato){
	QuitarNumeroRecursivo(&cabeza, dato);
}
//Eliminar nodos - funcion recursiva
void AdministradorLista::QuitarNumeroRecursivo(struct nodo** saltarin, int unNumero)
{
	if(*saltarin != NULL){
		if((*(*saltarin)).dato == unNumero){
			*saltarin = (*(*saltarin)).siguiente;
			QuitarNumeroRecursivo(saltarin, unNumero);
		}
		else
			QuitarNumeroRecursivo(&((*(*saltarin)).siguiente), unNumero);
	}
}

//Actualizar nodos
void AdministradorLista::ActualizarNodo(int viejoDato, int nuevoDato)
{
	if (cabeza != NULL)
	{
		struct nodo* saltarin = cabeza;
		while((*saltarin).siguiente != NULL)
		{
			//Buscar en todos los nodos, excepto el ultimo
			if((*saltarin).dato == viejoDato) (*saltarin).dato = nuevoDato;

			saltarin = (*saltarin).siguiente;
		}
		//Buscar en ultimo nodo
		if((*saltarin).dato == viejoDato) (*saltarin).dato = nuevoDato;
	}
}

int main(){
	AdministradorLista unaLista; //Para poder usar los metodos que tiene una clase, necesitamos instanciar
								 //un objeto de esta misma

	int opcion = 0, numeroI = 0, numeroE = 0, numeroViejo = 0, numeroNuevo = 0;
	do{
		cout << endl << "Menu: 1)Insertar 2)Mostrar 3)Eliminar 4)Actualizar 5)Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;

		switch(opcion){
		case 1: //Si queremos insertar
			cout << "Numero a insertar: ";
			cin >> numeroI; //leemo el numero que queremos ingresar al nodo
			unaLista.InsertarNodoFinal(numeroI); //llamamos al metodo insertar del objeto unaLista utilizando '.' para acceder a el
			break;								 //y le pasamos el numero que queremos ingresar
		case 2:
			cout << "Mostrando lista: " << endl;
			unaLista.MostrarLista(); //llamamos al metodo mostrar del objeto unaLista utilizando '.' para acceder a el
			break;
		case 3:
			cout << "Numero a eliminar: ";
			cin >> numeroE;
			unaLista.EliminarNodo(numeroE); //llamamos al metodo eliminar del objeto unaLista utilizando '.' para acceder a el
			break;							// y le pasamos el numero que queremos eliminar
		case 4:
			cout << "Numero viejo: ";
			cin >> numeroViejo; //leemos el dato que queremos buscar 
			cout << "Numero nuevo: ";
			cin >> numeroNuevo; //leemos el dato por el que lo vamos a cambiar
			unaLista.ActualizarNodo(numeroViejo, numeroNuevo); //llamamos al metodo actualizar del objeto unaLista utilizando '.' para acceder a el
			break; 											   //y le pasamos el numero que buscamos y por el que lo cambiaremos
		};
	}while(opcion >= 1 && opcion <= 4);

	cout << "Muchas gracias!" << endl;

	return 0;
}
