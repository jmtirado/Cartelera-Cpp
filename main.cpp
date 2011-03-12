/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
|																															|
|												   CARTELERA CINE															|
|																															|
|																															|
| COMPILADO EN: LINUX  Y WINDOWS //solo cambiando en la funcion limpiar por system("cls");									|
|---------------------------------------------------------------------------------------------------------------------------|
|                                        			Ver.1.1																	|
|																															|
| Esta práctica la he hecho sin enumerados, por lo que los datos hay que ponerlo en valores numericos. 						|
| He intentado ponerle algunas funciones con enumerados pero no me ha salido, asique lo he dejadoc como estaba.				|
| 																															|
| v.1.0																														|
| Realización del programa.																									|
| 																															|
| v.1.1																														|
| Corrección de bugs, optimización del código y le he añadido una nueva función al menu, que muestra todas las peliculas	|
| del cine durante la semana, me ha parecido práctico.																		|		
|																															|
|																															|
|////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

//Contantes
const unsigned int SESIONES=5;
const unsigned int SALAS=6;
const unsigned int CINES=4;
const unsigned int DIAS=7;
const char INTRO ='\n';

//DECLARACION DE ESTRUCTURAS

struct TPelicula{
	int hora, min;
	//string titulo;
	char titulo[256];
	string prota1, prota2;
	int calif;
	bool vacio;
};



typedef TPelicula TSesion[SESIONES];
typedef TSesion TSala[SALAS];
typedef TSala TDia[DIAS];
typedef TDia TCine[CINES];

//FUNCIONES DEL PROGRAMA

TPelicula leerpelicula();
void escribirpelicula(const TPelicula &datos);
void escribircine(unsigned int l);
void escribirdia(unsigned int d);
bool confirmarSalir();
void pausa();
char Menu();
void resultadobusqueda();
void  muestraPorEdades(const TCine &cartelera, const unsigned int edad);
bool comprobar(unsigned int c, unsigned int d, unsigned int s, unsigned int se);
void verCartelera(const TCine &cartelera, const unsigned int c);
void escogercine();
void escogersala();
void escogerdia();
void info();
void limpiar();



int main()
{
	char opcion;
	TPelicula p;
	TSesion s;
	TSala sal;
	TDia dia;
	TCine cartelera;
	bool salir=false;
	int contador=0;
	unsigned int j, k, l,d, calificacion;
	int cine;
	//----------------------INICIAMOS LOS ARRAYS-------------------------
	for (unsigned int c = 0; c < CINES; c++)
		for(unsigned int d=0; d<DIAS; d++)
			for (unsigned int s = 0; s <SALAS; s++)
				for (unsigned int ses=0; ses < SESIONES; ses++){
						cartelera[c][d][s][ses].vacio=true;
					}
	//--------------------------------------------------------------------	
	do{
	    opcion=Menu();	
    	switch(toupper(opcion)){
			case 'A': 
					//LEER PELICULA
					info();
					p = leerpelicula();
					escogercine();
					cin>> l;
					escogerdia();
					cin >> d;
					escogersala();
					cin >> k;
					cout<<"Sesion(1-5): ";
					cin >> j;
					if(comprobar(l,d,k,j))
					{
						cartelera[l-1][d-1][k-1][j-1]=p;
					}
					else
					{
						cout << "***** Los valores del cine, dia, sala o sesion no han sido correctos. Vuelva a escribirlos. *****"<<endl;
						pausa();
					}
					break;
					
			case 'B':
					//VISUALIZAR INFORMACION DE UNA SALA CONCRETA
					escogercine();
					cin>> l;
					escogerdia();
					cin >> d;
					escogersala();
					cin >> k;
					cout<<"Sesion(1-5): ";
					cin >> j;
					if(comprobar(l,d,k,j))// Comprueba que los datos introducidos son correctos.
					{   
						if(!cartelera[l-1][d-1][k-1][j-1].vacio)//Comprobamos que la pelicula ha sido creada
						{
							limpiar();
							resultadobusqueda();
							cout << "\tCine: "; escribircine(l);
							cout << "\tDia: "; escribirdia(d);
							cout << "\tSala: " << k << endl;
							cout << "\tSesion: " << j << endl;
							escribirpelicula(cartelera[l-1][d-1][k-1][j-1]);
						}
						else
						cout<<"****No hay ninguna pelicula para los datos introducido.****" <<endl;
					}
					else
					cout << "***Los Parametros introducido no son correctos. Vuelva a intentarlo.***" <<endl;
					pausa();
					break;
			case 'C':	
						//BUSCAR PELICULA
						/* Aqui al no utilizar los numerados, las comparaciones se hacen con cadenas de caracteres, y se comparan caracter a caracter*/
						limpiar();
						cout << "Introduzca el nombre de la pelicula a buscar: ";
						cin>>ws;	
						char cad1[256];
						cin.getline(cad1,sizeof(cad1));
						contador=0; // aquí pongo otra vez contador a 0 porque sino cuando salga de la opcion se queda guardado el ultimo valor de contador, y cuando haga una busqueda vuelva a sumar el valor que tenga.
						resultadobusqueda();
						for (unsigned int c = 0; c < CINES; c++){
							for(unsigned int d=0; d<DIAS; d++){
								for (unsigned int s = 0; s <SALAS; s++){
									for (unsigned int ses=0; ses < SESIONES; ses++){
										
										int i=0;
										i=strcmp(cad1, cartelera[c][d][s][ses].titulo);
										if(!i)
										{
											contador++;
											cout << "\tCine: "; escribircine(c+1);
											cout << "\tDia: "; escribirdia(d+1);
											cout << "\tSala: " << s+1 << endl;
											cout << "\tSesion: " << ses+1 << endl;
											escribirpelicula(cartelera[c][d][s][ses]);
										}
									}
								}
							}
						}
						if(contador==0)
						{
							cout<<"No se han encontrado resultados. Vuelva a intentarlo."<<endl;
						}
						else if(contador==1)
						{
							cout<<"Se ha encontado "<<contador<<" resultado."<<endl;
						}
						else
						{
							cout<<"Se han encontado "<<contador<<" resultados."<<endl;
						}
						pausa();			
			
						break;
			case 'D': 
						//LISTAR PELICULA POR EDADES
						limpiar();
						cout <<" Calificacion: "<<endl <<" 1 -> TP"<<endl<<" 2 -> M13 "<<endl<<" 3 -> M18 "<<endl;
						cout << "Escriba calificacion: ";
						cin >> calificacion;
						muestraPorEdades(cartelera, calificacion);
						pausa();
						break;
			case 'E':	
						//MOSTRAR PELICULAS DE UN CINE
						limpiar();
						escogercine();
						cin>> cine;
						verCartelera(cartelera,cine);
						pausa();
						break;
			case 'X':
						//SALIR
						salir=confirmarSalir();
						break;
			default:
					cout<<" La opcion introducida no es correcta."<<endl;
						break;
			}
    	}while(!salir);
	
	
	
	
	return 0;
	
	
}

	
TPelicula leerpelicula()
{
	TPelicula datos;
	cout << " Inserte hora(sin minutos): ";
	cin >> datos.hora;
	cout << " Inserte minutos: ";
	cin >> datos.min;
	cout <<" Nombre de la pelicula: ";
	cin >> ws;
	//getline(cin,datos.titulo);
	cin.getline(datos.titulo, sizeof(datos.titulo));
	//strupr(datos.titulo);
	cout <<" Prota1: ";
	getline(cin, datos.prota1);
	cout<<" Prota2: ";
	getline(cin,datos.prota2);
	cout <<" Calificacion 1:TP 2:M13 3:M18: ";
	cin >> datos.calif;
	datos.vacio=false;
	return datos;
}

void escribirpelicula(const TPelicula &datos)
{
	cout << "\tHora de inicio: " << datos.hora <<":"<<datos.min <<endl;
	cout << "\tPelicula: " << datos.titulo <<endl;
	cout << "\tProtagonistas: " << datos.prota1 << " y " << datos.prota2 << endl;
	if(datos.calif == 1)
	{
		cout<<"\tCalificacion: TP"<<endl;
	}else if(datos.calif==2)
	{
		cout<<"\tCalificacion: M13"<<endl;
	}else
	{
		cout<<"\tCalificacion: M18"<<endl;
	}
	cout<<"*******************************************************"<<endl;
}

	
bool confirmarSalir()
{
	char salir;
	cout << "Desea Salir? (S/N)";
	cin >> salir;
	
	return (toupper(salir) == 'S');
}
void pausa()
{
	char tecla;
	cout << endl << "Pulse ENTER para continuar...";
	cin.ignore();
	do
	{
		tecla=cin.get();
	}while(tecla!=INTRO);
}

char Menu(){
  char opcion;

  limpiar();
  
  cout <<"------------------------------------" <<endl;
  cout <<"|           Cartelera v.1.1        |" <<endl;
  cout <<"------------------------------------"<<endl;
  cout <<"               MENU                 "<<endl;
  cout <<"A -> Leer pelicula."<<endl;
  cout <<"B -> Visualizar informacion en una sala concreta."<<endl;
  cout <<"C -> Buscar pelicula"<<endl;
  cout <<"D -> Listar pelicula por edades"<<endl;
  cout <<"E -> Mostrar peliculas de un cine"<<endl;
  cout <<"X -> Salir"<<endl;
  cout <<"Introduzca su opcion: ";
  cin >> opcion;

  return opcion;    
}

void  muestraPorEdades(const TCine &cartelera, const unsigned int edad){
	int contador=0;
	for (unsigned int c = 0; c < CINES; c++){
		for(unsigned int d=0; d<DIAS; d++){
			for (unsigned int s = 0; s <SALAS; s++){
				for (unsigned int ses=0; ses < SESIONES; ses++){
					if (!(cartelera[c][d][s][ses].vacio)&&(cartelera[c][d][s][ses].calif==edad))
					{
						escribirpelicula(cartelera[c][d][s][ses]);
						contador++;
					}
				}
			}
		}
	}
	if(contador==0)
	{
		cout << "**** No existen peliculas para esa edad. ****"<<endl;
	}
}

void verCartelera(const TCine &cartelera, const unsigned int c)
{
	cout<<"/////////////////////////////////////////////////////////////////////////////"<<endl;
	cout<<"                          Cine ";escribircine(c);
	cout<<"////////////////////////////////////////////////////////////////////////////"<<endl;
	for(unsigned int d=0; d<DIAS; d++)
	{
		
		cout<<endl;
		cout<<"****************************************"<<endl;
		cout<<"            ";escribirdia(d+1);
		cout<<"****************************************"<<endl;

		for(unsigned int s=0; s<4;s+=3)
		{
			cout <<endl;
			cout << "\t Sala "<<s+1<<" \t\t  Sala "<<s+2<<" \t\t\t  Sala "<<s+3;
			for(unsigned int ses=0; ses<SESIONES; ses++)
			{
				//SALA 1
				cout<<endl;
				if(!(cartelera[c-1][d][s][ses].vacio))
				{
					cout<<" ";cout << cartelera[c-1][d][s][ses].hora;cout<<":";cout << cartelera[c-1][d][s][ses].min;cout<<" ";cout << cartelera[c-1][d][s][ses].titulo;					
				}
				else
				cout<<" No existe pelicula. ";
				
				//SALA 2
				if(!(cartelera[c-1][d][s+1][ses].vacio))
				{
						cout<<"\t\t";cout << cartelera[c-1][d][s+1][ses].hora;cout<<":";cout << cartelera[c-1][d][s+1][ses].min;cout<<" ";cout << cartelera[c-1][d][s+1][ses].titulo;
				}
				else
					cout<<"\t\t No existe pelicula. ";
				//SALA 3
				if(!(cartelera[c-1][d][s+2][ses].vacio))
					{cout<<"\t\t\t";cout << cartelera[c-1][d][s+2][ses].hora;cout<<":";cout << cartelera[c-1][d][s+2][ses].min;cout<<" ";cout << cartelera[c-1][d][s+2][ses].titulo;}
				else
					cout<<"\t\t No existe pelicula. ";
	
			}
		}
	}
}

void escribircine(unsigned int l)
{
	if(l==1)
	{
		cout << "Alameda"<<endl;}
	else if(l==2)
	{
		cout << "PlazaMayor"<<endl;
	}
	else if (l==3)
	{
		cout << "Larios" <<endl;
	}
	else if (l==4)
	{
		cout << "Albeniz" <<endl;
	}
}
void escribirdia(unsigned int d)
{
	if(d==1)
	{
		cout << "Lunes"<<endl;
	}
	else if(d==2)
	{
		cout << "Martes"<<endl;
	}
	else if(d==3)
	{
		cout << "Miercoles"<<endl;
	}
	else if(d==4)
	{
		cout << "Jueves"<<endl;
	}
	else if(d==5)
	{
		cout << "Viernes"<<endl;
	}
	else if(d==6)
	{
		cout << "Sabado"<<endl;
	}
	else if(d==7)
	{
		cout << "Domingo"<<endl;
	}
}
void resultadobusqueda()
{
	cout << "*****************************************" << endl;
	cout << "**       RESULTADO DE LA BUSQUEDA      **" << endl;
	cout << "*****************************************" << endl;
}
bool comprobar(unsigned int c, unsigned int d, unsigned int s, unsigned int se)
{
	if(c>4 || c<1)
	{
		return false;
	}
	if(d>7 || d<1)
	{
		return false;
	}
	if(s>6 || s<1)
	{
		return false;
	}
	if(se>5 || se<1)
	{
		return false;
	}
	else
	return true;
}
void escogercine(){
	
	cout << "Escoga cine:" <<endl;
	cout << "1 -> Alameda"<<endl;
	cout << "2 -> PlazaMayor"<<endl;
	cout << "3 -> Larios " <<endl;
	cout << "4 -> Albeniz" <<endl;
	
}
void escogersala()
{
	
	cout << "Escoga Sala:" <<endl;
	cout << "1 -> Sala 1"<<endl;
	cout << "2 -> Sala 2"<<endl;
	cout << "3 -> Sala 3 " <<endl;
	cout << "4 -> Sala 4" <<endl;
	cout << "5 -> Sala 5"<<endl;
	cout << "6 -> Sala 6"<<endl;
}
void escogerdia()
{
	
	cout << "Escoga Dia:" <<endl;
	cout << "1 -> Lunes"<<endl;
	cout << "2 -> Martes"<<endl;
	cout << "3 -> Miercoles " <<endl;
	cout << "4 -> Jueves" <<endl;
	cout << "5 -> Viernes"<<endl;
	cout << "6 -> Sabado"<<endl;
	cout << "7 -> Domingo"<<endl;
}
void limpiar()
{
	
	system("clear");
}
void info()
{
	limpiar();
	cout << "*****************************************" << endl;
	cout << "**             LEER PELICULA           **" << endl;
	cout << "*****************************************" << endl;
}
