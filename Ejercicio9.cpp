


/**** 
***** En este ejercicio pasamos por referencia la lista porque asi nos permitimos 
***** acceder a la direccion de memoria exacta donde se ubica esta lista y poder
***** modificar los valores directamente en ella. 
***** Por eso, como en la funcion recibimos una dirrecion, utilizamos el doble puntero para decir
***** que estamos apuntando a la direccion de memoria de un puntero. 
****/ 


#include <iostream>
using namespace std;

struct nodo{
	string nombre;
	string apellido;
	int edad;
	struct nodo *siguiente;
}*lista;


void insertar(nodo **list){ //Recibimos doble puntero porque estamos apuntando a la direccion de memoria de un puntero
	nodo *persona = new nodo; //Creamos una nueva cajita para ingresar una persona
	cout<<"Ingrese el nombre de la persona: "<<endl;
	cin>>persona->nombre; // Guardamos el nombre
	cout<<"Ingrese el apellido de la persona: "<<endl;
	cin>>persona->apellido; // Guardamos el apellido
	cout<<"Ingrese la edad de la persona"<<endl;
	cin>>persona->edad; // Guardamos la edad
	persona->siguiente=NULL; // Como insertamos al final de la lista, el siguiente del nodo que creeemos siempre
							 //apuntará a NULL


	if(*list==NULL){ // Si la lista está vacía
		*list=persona; //Guardamos en l lista el nodo que acabamos de crear
	}
	else{ //Si no está vacía
		struct nodo* saltarin = *list; //Creamos un puntero que guarde los valores de la lista
		while((*saltarin).siguiente != NULL){ //Recorremos con el puntero 
			saltarin = (*saltarin).siguiente; //hasta llegar al fnal
		}
		(*saltarin).siguiente = persona; //Cuando llegamos al final, hacemos que este último nodo apunte 
										 //al al nuevo nodo que acabamos de crear
	}
}


void eliminar(struct nodo** list, string name){//Recibimos los valores de la lista y el nombre que vamos a buscar
											   //para eliminar
	if(*list != NULL){ //Mientras podamos recorrer la lista porque no hemos llegado al final que es NULL
		if((*(*list)).nombre == name){ //Probamos si el puntero que tiene los valores de la lista, en el campo del nombre
									   //Es igual al parámetro name que es el nombre que buscábamos eliminar	
									   
			*list=(*(*list)).siguiente; //Si lo es, hacemos que el puntero cambie al siguiente valor e ignore ese en el 
									    //que encontró la coincidencia, quitándolo de la lista
									    
			eliminar(list, name); //Luego regresamos para verificar si hay más nombres como el que estamos buscando
		}
		else //Si no lo encuentra
			eliminar(&((*(*list)).siguiente), name); //Retornamos la dirección de memoria que trae el puntero en 
													//su campo siguiente y tambiénel nombre que estamos buscando
	}
}


/**** Para actualizar nombre, apellido o edad es básicamente lo mismo, nada más se comprueba el campo que nos interesa ****/


void actualizar_nombre(struct nodo** list, string name){ //Recibimos la lista y el nombre de la persona a modificar
	if(*list != NULL){ //Mientras podamos recorrer
		if((*(*list)).nombre == name){ //Probamos si donde estamos con el puntero, en el campo del nombre es igual al 
									   //nombre que estamos buscando 
			cout<<"Ingrese el nuevo nombre"<<endl;
			cin>>(*(*list)).nombre; //Guardamos el nombre nuevo en el campo de nombre del nodo en el que estamos
		}
		else
			actualizar_nombre(&((*(*list)).siguiente), name); //Si no, seguimos avanzando en la lista mandándole siempre 
															  //la dirección de la memoria para poder salvar los cambios
															  //en la variable global
	}
}



void actualizar_apellido(struct nodo** list, string name){	
	if(*list != NULL){
		if((*(*list)).nombre == name){
			cout<<"Ingrese el nuevo apellido"<<endl;
			cin>>(*(*list)).apellido;

		}
		else
			actualizar_apellido(&((*(*list)).siguiente), name);
	}
}



void actualizar_edad(struct nodo** list, string name){	
	if(*list != NULL){
		if((*(*list)).nombre == name){
			cout<<"Ingrese la nueva edad"<<endl;
			cin>>(*(*list)).edad;

		}
		else
			actualizar_edad(&((*(*list)).siguiente), name);
	}
}


void mostrar(nodo *p,int i){ //Recibimos la list y un contador
	nodo *s=p;
	if(s!=NULL){ //Mientras este nodo pueda seguir saltando
		cout<<"Persona "<<i<<endl; //Mostramos todos los datos de la persona 
		cout<<"El nombre es: "<<s->nombre<<endl;
		cout<<"El apellido es: "<<s->apellido<<endl;
		cout<<"La edad es: "<<s->edad<<endl<<endl;
		mostrar(s->siguiente,i+1); //Avanzamos a los siguientes datos de la lista
		
	}	
}


void ingresar(){ //Ingresar una persona
	int opc;
	cout<<"Desea agregar una persona?"<<endl;
	cout<<"1- Si 2- No"<<endl;
	cin>>opc;
	switch(opc){ //Preguntamos qué quiere hacer
		
		case 1:  { // Si quiere ingresar
					insertar(&lista); //Enviamos la lista a la funcion ingresar, lo enviamos con & porque nos permite 
									  //ir a la dirección de memoria directamente donde está guardado este puntero que se 
									  //llama lista y es global y poder modificar directamente sus valores
					ingresar(); break; //Llamada recursiva solamente para repetir
				}
		case 2: return; break; // Si no quiere seguir regresamos
	}
}

void menu(){ //Menu que nos pregunta lo que queremos realizar
	while(true){
		int opcion;
		cout<<"Que desea hacer?"<<endl;
		cout<<"1- Ingresar 2- Eliminar 3- Actualizar 4- Mostrar 5- Salir"<<endl;
		cin>>opcion; //Leemos la opcion que queremos
		switch(opcion){
			case 1:{  //En caso de querer ingresar
				ingresar(); //mandamos a llamar ingresar
				break;
			}
			case 2:{ //En caso de querer eliminar
				string n; 
				cout<<"Escriba el nombre de la persona a eliminar:"<<endl;
				cin>>n; //Guardamos el nombre de la persona que queremos eliminar
				eliminar(&lista,n); //Enviamos la dirrecion de la lista para poder modificar los valores directamente
									//y tambien el nombre que leimos que queremos eliminar
				break;
			}
			case 3:{ //En caso de querer actualizar
				string n;
				cout<<"Escriba el nombre de la persona a actualizar:"<<endl;
				cin>>n; //Leemos el nombre de la persona que queremos modificar
				int o;
				cout<<"Que desea modificar?"<<endl;
				cout<<"1- Nombre 2- Apellido 3- Edad"<<endl;
				cin>>o; //Preguntamos que quiere modificar de esa persona
				switch(o){
					case 1:{
						actualizar_nombre(&lista,n);
						break;
					}
					case 2:{
						actualizar_apellido(&lista,n);
						break;
					}
					case 3:{
						actualizar_edad(&lista,n);
						break;
					}
				}
				break;
			}
			case 4:{ //En caso de querer mostrar
				mostrar(lista,1); //Enviamos la lista nada tal cual porque no queremos modificar nada en ella asi que 
								  //no es necesario pasar su direccion y el valor de inicio del contador
				break;
			}
			case 5:{ //En caso de salir
				return; //Regresamos
				break;
			}
			
		}

	}
	
}


int main(){
	lista=NULL; //Iniciamos la lista como NULL
	
	menu(); //llamamos al menu 
	
	cout<<"Hasta pronto!"<<endl;
	return 0;
}
