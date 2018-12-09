#include <iostream>
using namespace std;

#define n 4

struct celda{
	int dato;
	int nFil;
	int nCol;
	celda *sigFil;
	celda *sigCol;
};

struct celda *hoja;

void filas_base(celda **lista,int row){
	cout<<"creando fila base"<<endl;
	celda *nueva = new celda;
	nueva->nFil=0;
	nueva->nCol=row;
	celda *s = *lista;
	celda *ref = s;
	while(s->sigFil!=ref){
		s=s->sigFil;
	}
	nueva->sigCol=nueva;
	s->sigFil=nueva;
	nueva->sigFil=*lista;
	cout<<"Termina fila"<<endl;
}

void columnas_base(celda **lista, int col){
	cout<<"Creando columna base"<<endl;
	celda *nueva = new celda;
	nueva->nFil=col;
	nueva->nCol=0;
	celda *s = *lista;
	celda *ref = s;
	while(s->sigCol!=ref){
		s=s->sigCol;
	}
	nueva->sigFil=nueva;
	s->sigCol=nueva;
	nueva->sigCol=*lista;
	cout<<"Termina columna"<<endl;
}

void crearHojasBase(celda **lista){
	
	celda *empty = new celda;
	cout<<"Creando celda base"<<endl;
	empty->nCol=0;
	empty->nFil=0;
	empty->sigCol=empty;
	empty->sigFil=empty;
	
	*lista=empty;
	
	for(int i=1;i<=4;i++){
		cout<<"Creando filas y columnas: "<<i<<endl;
		filas_base(lista,i);
		columnas_base(lista,i);	
	}
	
}




void InsertarNodo(int unDato, int Fil, int Col) {
	//Si el nodo ya existe en la primera fila
	if (Fil == 0) {
		//Desplazarse a la columna deseada
		struct celda *s1 = hoja;
		while (s1->nCol != Col) {
			s1 = s1->sigFil;
		}
		//Almacenar el dato
		s1->dato = unDato;
	}

	//Si el nodo ya existe en la primera columna
	if (Col == 0) {
		//Desplazarse a la fila deseada
		struct celda *s2 = hoja;
		while (s2->nFil != Fil) {
			s2 = s2->sigCol;
		}
		//Almacenar el dato
		s2->dato = unDato;
	}

	//Si el nodo no está ni en la primera fila ni en la primera columna
	if (Fil != 0 && Col != 0) {
		//Desplazarse a la columna deseada
		struct celda *s3 = hoja;
		while (s3->nCol != Col) {
			s3 = s3->sigCol;
		}
		//Desplazarse a la fila deseada
		struct celda *s4 = s3;
		//Repetir mientras no haya me haya pasado ni haya regresado al principio
		while ((s4->sigFil->nFil) <= Fil && (s4->sigFil->nFil) != 0) {
			s4 = s4->sigFil;
		}

		//Hay dos posibilidades: 1) el nodo ya existe
		if (s4->nFil == Fil) {
			s4->dato = unDato;
		}
		//2) el nodo no existe, entonces hay que crearlo
		else {
			//Creacion del nodo y almacenar valor
			struct celda *nuevo = new celda;
			nuevo->dato = unDato;

			//Desplazarse a la fila deseada
			struct celda *s5 = hoja;
			while (s5->nFil != Fil) {
				s5 = s5->sigFil;
			}

			//Buscar nodo que estara justo antes, en la misma columna
			struct celda *s6 = s5;
			//Repetir mientras no haya me haya pasado ni haya regresado al principio
			while ((s6->sigCol->nCol) <= Col && (s6->sigCol->nCol) != 0) {
				s6 = s6->sigCol;
			}

			//Arreglar punteros: s4 (nodo que va antes en la misma fila)
			//s6 (nodo que va antes en la misma columna)
			//1) despues del nuevo nodo, tiene que ir lo que hay
			//   despues del nodo anterior al nuevo nodo
			nuevo->sigFil = s4->sigFil;
			nuevo->sigCol = s6->sigCol;
			//2) finalmente, despues del nodo anterior al nuevo nodo
			//   tiene que ir el nuevo nodo
			s4->sigFil = nuevo;
			s6->sigCol = nuevo;
		}
	}	
}



int main(){
	hoja = NULL;
	int Fil=0,Col=0;
	cout << "Bienvenido, ahora esta creandose la hoja electronica..." << endl;
	crearHojasBase(&hoja);
	cout << "Hoja creada." << endl;

	char c = 's';
	do {
		//1) Preguntar al usuario que desea hacer
		cout << "Desea almacenar un nuevo valor (s/n)? ";
		do {
			cin >> c;
			//Validar que el usuario digite 's' o 'n'
			if (c != 's'&&c != 'n')
				cout << "Favor digite una opcion valida: ";

			//Repetir hasta que el usuario no se equivoque
		} while (c != 's' && c != 'n');

		//2) Si la respuesta fue 's' entonces ingresar un nuevo valor
		if (c == 's') {
			cout << "Ingrese numero de la fila donde quiere agregar el nuevo dato: ";
			cin >> Fil;
			cout << "Ingrese el numero la columna donde quiere agregar el nuevo dato: ";
			cin >> Col;

			//Mas validaciones...
			if (Fil >= 0 && Fil <= 4 && Col >= 0 && Col <= 4) {
				int unDato = 0;
				printf("Ingrese el valor deseado: ");
				cin >> unDato;
				InsertarNodo(unDato, Fil, Col);
			}
			else
				printf("Error en el ingreso de fila y columna\n");
		}

		//Repetir hasta que el usuario desee detenerse
	} while (c == 's');
	return 0;
}
