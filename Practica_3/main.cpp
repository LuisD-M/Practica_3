#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

void escribir();
void leer();

int main()
{
    //ofstream archivo;                                                 // objeto para escribir en archivo de texto
    //ifstream fin;                                                  // objeto para leer un archivo de texto
    escribir();
    leer();

}

void escribir(){
    ofstream archivo;

    archivo.open("C:\\Users\\luis\\Desktop\\Universidad\\NIVEL 9\\Informatica 2\\Laboratorio\\Practica #3\\Practica_3\\Binario.txt");

    if(archivo.fail()){
        cout<<"El archivo binario no ce pudo crear."<<endl;
        exit(1);
    }

    //archivo<<"Hola que tal"<<endl;
    //archivo<<"yo muy bien y usted ";

    archivo.close();
}

void leer(){
    string texto;
    int tamaño;


    ifstream archivo;

    archivo.open("C:\\Users\\luis\\Desktop\\Universidad\\NIVEL 9\\Informatica 2\\Laboratorio\\Practica #3\\Practica_3\\texto.txt");

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto no ce pudo abrir."<<endl;
        exit(1);
    }

    archivo.seekg(0,ios::end);                                        //Se va al final del archivo
    tamaño=archivo.tellg();                                           //Se obtiene la posicion actual.
    char catexto[tamaño];

    archivo.seekg(0,ios::beg);                                        //Volver al inicio del archivo

    archivo.read(catexto, tamaño);

    for(int i=0; i<tamaño; i++)
        cout<<catexto[i];



    archivo.close();


}
