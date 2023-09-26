#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include <vector>

using namespace std;

int tamtex();
void binario(int tamaño, char *catexto, int *texbinario);
void metodo1(int tamaño, int semilla, int *texbinario, int *codificado);
void metodo2(int tamaño, int semilla, int *texbinario, int *codificado);
void escribir(int tamaño, int *codificado);


int main()
{
    int tamaño, semilla, metodo;
    cout<<"Ingrese la semilla n: "; cin>>semilla;
    cout<<"Ingrese el metodo de codificacion (1-2): "; cin>>metodo;

    tamaño=tamtex();                                                                     //Calcular el tamaño del texto.

    char catexto[tamaño];
    int texbinario[8*tamaño];
    binario(tamaño, &catexto[0], &texbinario[0]);                                       //Genera 2 cadenas, caracteres y binario.
    int codificado[8*tamaño];

    if(metodo==1){
        metodo1(tamaño, semilla, &texbinario[0], &codificado[0]);
        escribir(tamaño, &codificado[0]);
    }
    else{
        metodo2(tamaño, semilla, &texbinario[0], &codificado[0]);
        escribir(tamaño, &codificado[0]);
    }
}

int tamtex(){
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
    archivo.seekg(0,ios::beg);                                        //Volver al inicio del archivo
    archivo.close();

    return tamaño;
}

void binario(int tamaño, char *catexto, int *texbinario){
    char cadena[tamaño];
    vector<int> vect;

    ifstream archivo;

    archivo.open("C:\\Users\\luis\\Desktop\\Universidad\\NIVEL 9\\Informatica 2\\Laboratorio\\Practica #3\\Practica_3\\texto.txt");

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto no ce pudo abrir."<<endl;
        exit(1);
    }

    archivo.read(cadena, tamaño);                                    //Se agrega el texto al arreglo caracter por caracter
    archivo.close();

    for(int i=0; i<tamaño; i++)                                   //Se llena la cadena de caracteres
        catexto[i] = cadena[i];

    for(char c : cadena){                                           //Se pasa los caracteres a binario y se llena vector
        bitset<8> binary_char(c);
        for (int i = 7; i >= 0; i--)
            vect.push_back(binary_char[i]);
    }

    for(int i=0; i<8*(tamaño); i++)                             //Se llena el arreglo de binarios con el vector
        texbinario[i]=vect[i];
}

void metodo1(int tamaño, int semilla, int *texbinario, int *codificado){
    int cont0=0, cont1=0, aux=0;

    for(int i=0; i<8*(tamaño);i++)
        cout<<texbinario[i];
    cout<<endl;


    for(int i=0; i<8*(tamaño); i=i+semilla){

        if(cont0 == cont1){                                            //el # de 1nos es igaul al # de 0ros.
            for(int j=i; j<i+semilla; j++){
                if(texbinario[j]==1) codificado[j]=0;
                else
                    codificado[j]=1;
            }
        }

        else if(cont0>cont1){                                             //ceros > unos (invierte cada 2 bits)
            aux=0;
            for(int j=i; j<i+semilla; j++){
                if(aux==1){                                              //Invierte el 2 bit
                    if(texbinario[j]==1) codificado[j]=0;
                    else codificado[j]=1;
                    aux=0;
                }
                else{
                    codificado[j]=texbinario[j];
                    aux++;
                }
            }
        }

        else {                                                       //unos > ceros (invierte cada 3 bits)
            aux=0;
            for(int j=i; j<i+semilla; j++){
                if(aux==2){
                    if(texbinario[j]==1) codificado[j]=0;
                    else codificado[j]=1;
                    aux=0;
                }
                else{
                    codificado[j]=texbinario[j];
                    aux++;
                }
            }
        }

        cont0=0;
        cont1=0;
        for(int j=i; j<i+semilla; j++){                             //Calcula contadores de la suma actual para analizar el
            if(texbinario[j]==1) cont1++;                         // siguiente ciclo
            else cont0++;
        }
    }

    for(int i=0; i<8*(tamaño);i++)
        cout<<codificado[i];
}

void metodo2(int tamaño, int semilla, int *texbinario, int *codificado){
    int grupos;

    for(int i=0; i<8*(tamaño); i++)
        cout<<texbinario[i];
    cout<<endl;

    for(int i=0; i<8*(tamaño); i=i+semilla){                                //Se recorre el arreglo binario por grupos de n

        for(int j=i; j<i+semilla; j++){                                     //Se recorre cada grupo de n escogido

            if(j==(i+semilla-1))                                           //La ultima posicion se pone de primera
                codificado[i]=texbinario[j];

            else
                codificado[j+1]=texbinario[j];                             //Se corre una posicion a la derecha.
        }
    }

    if((8*tamaño)%semilla != 0){
        grupos=(8*tamaño)/semilla;

        for(int i=grupos*semilla; i<8*(tamaño); i++)
            codificado[i]=texbinario[i];
    }

    for(int i=0; i<8*(tamaño); i++)
        cout<<codificado[i];
    cout<<endl;
}

void escribir(int tamaño, int *codificado){
    ofstream archivo;

    archivo.open("C:\\Users\\luis\\Desktop\\Universidad\\NIVEL 9\\Informatica 2\\Laboratorio\\Practica #3\\Practica_3\\Codificado.txt");

    if(archivo.fail()){
        cout<<"El archivo Codificado no ce pudo crear."<<endl;
        exit(1);
    }

    for(int i=0; i<8*(tamaño); i++)
        archivo<<codificado[i];

    archivo.close();
}



