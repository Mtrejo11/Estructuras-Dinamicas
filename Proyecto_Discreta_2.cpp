#include <iostream>
#include <cstdlib>   // for srand and rand
#include <ctime>     // for time
#include <cmath>
using namespace std;

struct carta{
    int number;
    int valor;
    carta *sig;
}*pInicio;


struct grupo{
	int number;
	int valor;
	bool primo;
	bool par;
	bool mayor;
	grupo *sig;
};
struct grupo* sel;
struct grupo* cartaElegida;



void CrearLista(carta **lista, int array, int cont){
    
    carta *nuevo = new carta;
    nuevo->number = cont;
    nuevo->valor = array;
    nuevo->sig = NULL;
    
    if(*lista == NULL){  
        *lista = nuevo;
    }else
    {
        carta *saltarin = *lista;
        while(saltarin->sig != NULL){
            saltarin = saltarin->sig;
        }
        
        saltarin->sig = nuevo;
    }
}

void mostrar(carta *s){
    if(s!= NULL){
        cout << "Carta: " << s->number << "   ";
        mostrar(s->sig);
    }
}

int Contar_cartas(carta *s){
    int c=0;
    while(s!= NULL){
        c++;
        s=s->sig;
    }
    return c;
}

int valor_carta(carta *list,int n){
    while(list != NULL){
    if(list->number == n){
            return list->valor;
    }
            list = list->sig;
    }
}

//Funcion para crear la lista de las cartas seleccionadas por el jugador
//recibe de parametros la carta buscada, la lista de seleccion, y las características de la carta seleccionada
void crear_seleccion(carta* c,grupo **l, bool prim,bool par, bool may){
	grupo *nuevo = new grupo;
    nuevo->valor = c->valor;
    nuevo->number = c->number;
    nuevo->mayor = may;
    nuevo->primo=prim;
    nuevo->par=par;
    nuevo->sig=NULL;
    
    if(*l == NULL){  
        *l = nuevo;
    }else
    {
        grupo *saltarin = *l;
        while(saltarin->sig != NULL){
            saltarin = saltarin->sig;
        }
        
        saltarin->sig = nuevo;
    }
}


//funcion que busca la carta que selecciono el jugador para mandar a guardarla en la lista de la seleccion

void lista_seleccion(carta *l,int n,bool prim,bool par, bool may){
	while(l != NULL){
    if(l->number == n){
            crear_seleccion(l,&sel,prim,par,may);
    }
            l = l->sig;
    }
}



void mostrar_seleccion(grupo *l){
	while(l!=NULL){
		cout<<l->number<<endl;
		l=l->sig;
	}
}

//Funcion para buscar la carta que selecciona el jugador 

void buscar_carta(grupo *l,int c){
		while(l != NULL){
    if(l->number == c){
           cartaElegida = l; //Cuando se encuentra la carta se guarda en cartaElegida
           break;
    }
            l = l->sig;
    }
}


float ncartas;
int main() {
    pInicio = NULL;
    sel = NULL;
    int num, op, n=10, valor;
    float pri;
    float probpar=0, probimp=0, probMa=0, probMe=0, probPri=0;
    int seleccion=5;
    int val[]={5,10,19,25,30,33,50,75,83,100}; 
    srand(time(0));  // semilla generadora
    
    //--- Shuffle los elementos de manera que se cambien de lugar
        
    bool flag = true;
    
    while(flag){
    	
    	for (int i=0; i<n; i++) {
            int r = rand() % n;  // genera una posicion random 
            int temp = val[i]; 
            val[i] = val[r]; 
            val[r] = temp;
        }
                
        for(int j=0; j<n ; j++){
            CrearLista(&pInicio,val[j],j+1);
        }
    
    ncartas = Contar_cartas(pInicio);
    cout << "Hay un total de " << ncartas << " cartas: " << endl;
    
    mostrar(pInicio);
    cout << endl << endl << "-------------- Que comience el juego --------------" << endl;
    
    	
        int conta=0, contpri=0, contMay50=0, contMen50=0, contpares=0, contimpares=0;
        bool flagPrimo, flagPar, flagMayor;
        bool jugadorPrimo, jugadorPar, jugadorMayor;
        cout << "Debe de escoger " << seleccion << " cartas." << endl;
            for(int j=0; j<seleccion ; j++){
                cout << endl << "¿Qué carta desea escoger?: ";
                cin >> num;
                valor = valor_carta(pInicio,num);
                cout << valor << " "; //Por si desea conocer el valor que tiene la carta
        
                conta=0;
                
                //Para saber si es primo
                for (int i=1; i<=valor; i++){
                    if(valor%i==0){
                        conta++;
                    }
                }
                
                if (conta == 2){
                    contpri++;
                    flagPrimo=true;
                }
				else{
					flagPrimo=false;
				}                    
                
                //Para evaluar si es impar o par
                if(valor%2 == 0){
                    contpares++;
                    flagPar=true;
                }else{
                	contimpares++;
                	flagPar=false;
				}
                    
                
                //Para evaluar si es mayor-igual que 50 o menor
                if(valor >= 50){
                    contMay50++;
                    flagMayor=true;
                }else{
                    contMen50++;
					flagMayor=false;
				}
				
				//Funcion para buscar el nodo de la lista que se busca
				//se envian los valores de las banderas para posteriormente guardarlos en la funcion creadora de la lista 
				//como caracteristicas de cada nodo en la lista de seleccion
				lista_seleccion(pInicio,num,flagPrimo, flagPar, flagMayor);
        }
        
        cout<<endl<<"Lista seleccionada"<<endl;
        mostrar_seleccion(sel);
        
        
       /* cout << endl << contpares << " " << contimpares << " " << contMay50 << " ";
        cout << contMen50 << " " << contpri << " "; //Por si desea saber cuanto se conto de c/u
        */
        
        
        //CALCULANDO LA PROBABILIDAD Numcasosfav/Numcasospos
        
        cout << "La probabilidad que los valores sean pares: ";
        probpar = (float)(contpares*100)/seleccion;
        cout << " %" << probpar << endl;
        
        cout << "La probabilidad que los valores sean impares: ";
        probimp = (float)(contimpares*100)/seleccion;
        cout << " %" << probimp << endl;
        
        cout << "La probabilidad que los valores sean mayores que 50: ";
        probMa = (float)(contMay50*100)/seleccion;
        cout << " %" << probMa << endl;
        
        cout << "La probabilidad que los valores sean menotes que 50: ";
        probMe = (float)(contMen50*100)/seleccion;
        cout << " %" << probMe << endl;
        
        cout << "La probabilidad que los valores sean primos: ";
        probPri = (float)(contpri*100)/seleccion;
        cout << " %" << probPri << endl;
        
        int card;
        
        cout<<"Seleccione una carta: "<<endl;
        cin>>card;
    
        buscar_carta(sel,card);
        
        //Pregunta por las caracteristicas de la carta seleccionada
        
        char pr, pa, ma;
        
        cout<<"El valor de la carta es primo? (s/n)"<<endl;
        cin>>pr;
        
        cout<<"El valor de la carta es par? (s/n)"<<endl;
        cin>>pa;
        
        cout<<"El valor de la carta es mayor que 50? (s/n)"<<endl;
        cin>>ma;
        
        
        // Elige que es par/impar
        if(pa=='s'){
        	jugadorPar=true;
		}
		else if(pa=='n'){
			jugadorPar=false;
		}
        
        //Elige que es/no es primo
        if(pr=='s'){
        	jugadorPrimo=true;
		}
		else if(pr=='n'){
			jugadorPrimo=false;
		}
		
		//Elige que es mayor/menor
		if(ma=='s'){
        	jugadorMayor=true;
		}
		else if(ma=='n'){
			jugadorMayor=false;
		}
        
        
        int cont_aciertos=0;
        
        //Verificar si las caracteristicas de la carta coinciden con los que eligió el jugador
        
        if(cartaElegida->primo==jugadorPrimo){

        	cont_aciertos++;
		}
        
        if(cartaElegida->par==jugadorPar){
        	cont_aciertos++;
		}
		
		if(cartaElegida->mayor==jugadorMayor){
        	cont_aciertos++;
		}
		
		
		//Se imprime el valor de la carta seleccionada
		cout<<"La carta es: "<<endl;
		cout<<cartaElegida->valor<<endl;
		
		//Si acertó dos o más veces gana el juego
		if(cont_aciertos>=2){
			cout<<"Ganaste!"<<endl;
		}
        else{
        	cout<<"Sigue participando :("<<endl;
		}
		
		
        seleccion--;
        cout << endl << "¿Desea seguir jugando?: 1.Si 2.No ";
        cin >> op;
        
        if(op == 1){
            flag = true;
            sel = NULL;
            delete cartaElegida;
        }else if(op == 2)
        {
            flag = false;
            cout << endl << "Gracias por jugar!";
            break;
        }
        
    }
            
   return 0;
}
