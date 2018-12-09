#include <iostream>

using namespace std;

struct Entrenamiento{
    float distancia;
    float tiempo;

};

struct Persona{
    string nombre;
    int nEnt;
    float totalDist;
    float totalTime;
    Entrenamiento* ejercicio;
};

void Mostrar(int t, int c,int tam, Persona* PuntPer,Entrenamiento* puntEnt){
    
    if (c<t){ //Para ir contando hasta que la cantidad de personas se cumpla
        if(tam<PuntPer->nEnt){ //para ir contando hasta que la cantidad de entrenamientos por persona se cumpla
        PuntPer->totalDist += puntEnt->distancia; //Sumamos al total lo que cada lista de entrenamiento por persona traiga
        PuntPer->totalTime += puntEnt->tiempo;
        Mostrar(t, c,tam+1,PuntPer,puntEnt+1); //Avanzamos 1 en los entrenamientos

        }
        else{  //al llegar al final de los entrenamientos enseñamos el total por persona
        cout<<endl<<"Para "<< PuntPer->nombre<<endl; //mostramos el nombre de la persona en la lista
        cout << "Total distancia recorrida: " << PuntPer->totalDist << endl; //mostramos la distancia total correspondiente  la persona
        cout << "Tiempo total: " << PuntPer->totalTime; //mostramos el tiempo total que le corresponde a la persona
        PuntPer++;  //avanzamos uno en la lista de personas
        Mostrar(t, c+1,0,PuntPer,PuntPer->ejercicio); //enviamos el contador c para persona aumentado en 1, el tam de ejericios de nuevo en 
        											 //cero, el puntero que ahora avanzó en una posición y la lista de ejercicios correspondiente
        											//a esa posición en el puntero
        }
    }
    

}

Entrenamiento* Llenar(int tam, int i, Entrenamiento* Puntero){

    if(i<tam){ //Llenamos hasta que se alcance el numero de entrenamientos que tendrá cada persona
        cout<< "Ingrese distancia en km: " ;
        cin >> Puntero->distancia; //Leemos y guardamos en la lista de entrenamientos en el campo de distancia
        cout << "Ingrese tiempo en horas: ";
        cin >> Puntero->tiempo; //Leemos y guardamos en la lista de entrenamientos en el campo de tiempo
        cout << endl;
        return Llenar(tam, i+1, Puntero+1); //Aumentamos uno el contador y avanzamos una posición en la lista
    }else{
		
		Puntero -= tam; //Regresamos al inicio de la lista
        
        return Puntero; //Retornamos el puntero 
    }
    
}

int main() {

    
    int num;
    Entrenamiento* PuntEjer; //puntero para listado de ejercicios
    Persona* PuntPer; //puntero para listado de personas
    
    cout << "Ingrese numero de personas: ";
    cin >> num; cout << endl;  
    
    PuntPer= new Persona[num]; //Asignamos memoria a la cantidad de personas

    
    //Llenado iterativo de las personas 
    for(int i=0; i<num ; i++){
        int ent; //para numero de entrenamientos por persona
        string n; //para nombre de persona
        
        cout << "Ingrese el nombre: ";
        cin >> n;  // leemos el nombre
        
        cout << "Ingrese numero de entrenamientos: ";
        cin >> ent; cout << endl; //leemos el numero de entrenamientos 
        PuntEjer= new Entrenamiento[ent]; //Asignamos memoria dependiendo del numero de entrenamientos 
    
        PuntPer->nombre = n ; //Asignamos el nombre leido a la lista de personas
        PuntPer->nEnt=ent; //Asignamos el numero de entrenamientos a la persona
        PuntPer->ejercicio = Llenar(ent,0,PuntEjer); //Asignamos la lista de ejercicios que realiza la persona llenandolos en la funcion LLenar
        PuntPer->totalDist=0; //Seteamos los totales en cero
        PuntPer->totalTime=0;
        PuntPer++; // avanzamos uno en la lista de personas
    }
    
    PuntPer-=num; //regresamos al inicio en la lista de personas para poder enviar
    
    Mostrar(num,0,0,PuntPer,PuntPer->ejercicio);  //enviamos la cantidad de personas, 0 y 0 para contadores, la lista de personas
												  // y el listado de ejercicios
    
    //Quitamos la memoria otorgada a los punteros
    delete[] PuntEjer; 
    delete[] PuntPer;
    return 0;
    
}
