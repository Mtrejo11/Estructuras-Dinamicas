#include <iostream>
#include <string>
using namespace std;

struct venta{
	string cliente, marca, modelo;
	int precio;
	struct venta* siguiente;
};
struct vendedor{
	string nombre;
	struct venta* cabeza;
};

void InsertarNodoFinal(struct venta** unaCabeza, string unCliente, string unaMarca, string unModelo, int unPrecio)
{
	struct venta* nuevo_nodo = new struct venta[1];
	(*nuevo_nodo).cliente = unCliente;
	(*nuevo_nodo).marca = unaMarca;
	(*nuevo_nodo).modelo = unModelo;
	(*nuevo_nodo).precio = unPrecio;
	(*nuevo_nodo).siguiente = NULL;

	if (*unaCabeza == NULL)
		*unaCabeza = nuevo_nodo;
	else{
		struct venta* saltarin = *unaCabeza;
		while((*saltarin).siguiente != NULL)
			saltarin = (*saltarin).siguiente;
		(*saltarin).siguiente = nuevo_nodo;
	}
}

void VentasParticular(struct venta *unaCabeza, int unContador){
	if(unaCabeza != NULL){
		unContador++;
		cout << "Venta #" << unContador << ":" << endl;
		cout << "Nombre de cliente: " << (*unaCabeza).cliente << endl;
		cout << "Marca del vehiculo: " << (*unaCabeza).marca << endl;
		cout << "Modelo del vehiculo: " << (*unaCabeza).modelo << endl;
		cout << "Precio de venta: " << (*unaCabeza).precio << endl;
		VentasParticular((*unaCabeza).siguiente, unContador);
	}
	else
		cout << "\nCantidad total de ventas: " << unContador << endl;
}

int CantidadAutosVendidos(struct venta *unaCabeza){
	if(unaCabeza == NULL)
		return 0;
	else
		return 1 + CantidadAutosVendidos((*unaCabeza).siguiente);
}

int MontoTotalVentas(struct venta *unaCabeza){
	if(unaCabeza == NULL)
		return 0;
	else
		return (*unaCabeza).precio + MontoTotalVentas((*unaCabeza).siguiente);
}

int VentasTotales(struct vendedor* vendedores, int posicion, int limMaximo){
	if(posicion == limMaximo)
		return 0;
	else
		return MontoTotalVentas(vendedores[posicion].cabeza) + VentasTotales(vendedores, posicion+1, limMaximo);
}

float PromedioVentasTotales(struct vendedor* vendedores, int cantVendedores){
	return VentasTotales(vendedores, 0, cantVendedores) / cantVendedores;
}

int main(){
	//En una compañía que se dedica a la venta de automóviles hay cierta cantidad de vendedores, n.
	int n = 0, i = 0;
	cout << "Bienvenido, favor ingrese cantidad de vendedores: ";
	cin >> n;

	//Arreglo creado dinámicamente
	struct vendedor* vendedores = new struct vendedor[n];

	//a) Ingresar los vendedores a un arreglo de n casillas. Cada casilla del 
	//   arreglo debe contener el nombre del vendedor y un puntero a una lista.
	for(i = 0; i < n; i++){
		cout << "Nombre del vendedor #" << i+1 << ": ";
		cin >> vendedores[i].nombre;
		vendedores[i].cabeza = NULL;
	}

	//b) Ingresar las ventas realizadas por cada vendedor. Cada venta se incorpora a la lista
	//   que le corresponde a cada vendedor. Las listas deben contener el nombre del cliente,
	//   la marca del vehículo, el modelo del vehículo y el precio de venta.
	string nombreCliente = "", marcaV = "", modeloV = "";
	int precioV = 0, opcion = 0;

	for(i = 0; i < n; i++){
		do{
			cout << "\nVentas del vendedor #" << i+1 << ". 1)Ingresar 2)Continuar\nOpcion: ";
			cin >> opcion;

			if(opcion == 1){
				cout << "Nombre del cliente: ";
				cin >> nombreCliente;
				cout << "Marca del vehiculo: ";
				cin >> marcaV;
				cout << "Modelo del vehiculo: ";
				cin >> modeloV;
				cout << "Precio de venta: ";
				cin >> precioV;

				InsertarNodoFinal(&vendedores[i].cabeza, nombreCliente, marcaV, modeloV, precioV);
				//cout << (*(vendedores[i].cabeza)).precio << endl;
			}
		}while(opcion == 1);
	}

	//c) Mostrar el listado de las ventas realizadas por un vendedor particular, con sus detalles
	//   y total de ventas. Su función debe recibir el nombre del vendedor, buscarlo en el
	//   arreglo y desplegar las ventas que ha realizado y el total de las mismas.
	string nombreVendedor = "";
	opcion = 0;
	do{
		cout << "\nDesea conocer las ventas de algun vendedor? 1)Si 2)No\nOpcion: ";
		cin >> opcion;

		if(opcion == 1){
			cout << "Nombre del vendedor: ";
			cin >> nombreVendedor;

			for(i = 0; i < n; i++){
				if(vendedores[i].nombre.compare(nombreVendedor) == 0){
					VentasParticular(vendedores[i].cabeza, 0);
					//Salir del ciclo for
					i==n;
				}
			}
		}
	}while(opcion == 1);

	//d) Calcular la cantidad de autos vendidos por cada vendedor. Su función debe
	//   mostrar para cada uno de los vendedores, cuantos autos ha vendido.
	cout << "\nCantidad de autos vendidos por cada vendedor:" << endl;
	for(i = 0; i < n; i++){
		cout << "Vendedor #" << i+1;
		cout << "\tNombre: " << vendedores[i].nombre;
		cout << "\tCantidad: " << CantidadAutosVendidos(vendedores[i].cabeza) << endl;
	}

	//e) Calcular el monto total de las ventas de cada vendedor. Su función debe mostrar
	//   para cada uno de los vendedores, el monto total de las ventas que ha realizado.
	cout << "\nMonto total de las ventas de cada vendedor:" << endl;
	for(i = 0; i < n; i++){
		cout << "Vendedor #" << i+1;
		cout << "\tNombre: " << vendedores[i].nombre;
		cout << "\tMonto: " << MontoTotalVentas(vendedores[i].cabeza) << endl;
	}

	//f) Indicar el nombre del vendedor que realizó más ventas.
	//Primero suponemos que el primero es el mayor
	int mayor = CantidadAutosVendidos(vendedores[0].cabeza), indiceMayor = 0, pivote = 0;
	//Ahora, verificamos los demás (del 1 hasta el n-1)
	for(i = 1; i < n; i++){
		pivote = CantidadAutosVendidos(vendedores[i].cabeza);
		//Si pivote(i) es mayor que el que ya tenemos...
		if(pivote > mayor){
			//Se actualizan los valores...
			indiceMayor = i;
			mayor = pivote;
		}
	}
	//Al salir del ciclo for, los valores son los verdaderos
	cout << "\nVendedor que realizo mas ventas:\n";
	cout << "Nombre: " << vendedores[indiceMayor].nombre << " (#" << indiceMayor+1 << ")";
	cout << " Ventas: " << mayor << endl;

	//g) Realizar el cálculo de las ventas totales realizadas por la compañía.
	cout << "\nVentas totales de la compania: " << VentasTotales(vendedores, 0, n) << endl;

	//h) Realizar el cálculo del promedio de las ventas totales realizadas por la compañía.
	cout << "\nPromedio de las ventas totales: " << PromedioVentasTotales(vendedores, n) << endl;

	return 0;
}