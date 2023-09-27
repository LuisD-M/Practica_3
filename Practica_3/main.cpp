#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include <vector>

using namespace std;

int tamtex(string archivoleer);
void binario(int tamaño, char *catexto, int *texbinario, string archivoleer);
void metodo1(int tamaño, int semilla, int *texbinario, int *codificado, string nombre);
void metodo2(int tamaño, int semilla, int *texbinario, int *codificado, string nombre);
void deco1(int tamaño, int semilla, int *texbinario, string nombre, string nombredeco);
void deco2(int tamaño, int semilla, int *texbinario, int *codificado, string nombre, string nombredeco);
int menu();


int main()
{
    int tamaño, semilla, metodo, opcion=10, numerousu;
    string archivoleer, nombre, nombredeco, clave, linea, claveusu, datos;
    cout<<"Ingrese la semilla n: "; cin>>semilla;
    cout<<"Ingrese el metodo de codificacion (1-2): "; cin>>metodo;

    ifstream in;
    ofstream on;


    while(opcion!=0){
        cout<<endl;
        menu();
        cout<<"Ingrese la opcion deseada: "; cin>>opcion;

        if(opcion==1){
            cout<<"Ingrese el nombre del archivo que tiene la clave incriptada: "; cin>>nombre;
            tamaño=tamtex(nombre);
            char catexto[tamaño/8];
            int texbinario[tamaño];
            int codificado[tamaño];

            cout<<"Ingrese el nombre del archivo que va a tener la clave desencriptada: "; cin>>nombredeco;
            if(metodo==1) deco1(tamaño/8, semilla, &texbinario[0], nombre, nombredeco);
            else deco2(tamaño/8, semilla, &texbinario[0], &codificado[0], nombre, nombredeco);

            in.open(nombredeco);

            if(in.fail()){
                cout<<"El archivo texto de la clave decodificada no se pudo abrir."<<endl;
                exit(1); }

            while (getline(in, linea))
                clave += linea;

            in.close();

            cout<<"Ingrese la clave de administrador: "; cin>>claveusu;

            if(claveusu == clave){
                cout<<"Administradro en linea."<<endl;
                cout<<"Ingrese el nombre del archivo de los usuarios: "; cin>>archivoleer;

                on.open(archivoleer,ios::app);
                if(on.fail()){
                    cout<<"El archivo texto de los usuarios no se pudo abrir."<<endl;
                    exit(1); }

                cout<<"Ingrese el numero de usuarios que desea registrar: "; cin>>numerousu;

                while(numerousu!=0){
                    cout<<"Ingrese los datos del usuario nuevo cedula,clave,dinero: "; cin>>datos;
                    on<<datos<<endl;
                    numerousu--;
                }
                on.close();

            }
            else cout<<"Las claves no coinciden, no puede ingresar"<<endl;

        }





    }
}

int menu(){
    cout<<"-------------------- Menu de la aplicacion --------------------"<<endl;
    cout<<" 1. Registrar usuarios. "<<endl;
    cout<<" 2. Consultar saldo."<<endl;
    cout<<" 3. Retirar dinero."<<endl;
    cout<<" 0. Para finalizar."<<endl;
}

int tamtex(string archivoleer){
    int tamaño;

    ifstream archivo;
    archivo.open(archivoleer);

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto no ce pudo abrir para encontrar el tamanio."<<endl;
        exit(1);
    }

    archivo.seekg(0,ios::end);                                        //Se va al final del archivo
    tamaño=archivo.tellg();                                           //Se obtiene la posicion actual.
    archivo.seekg(0,ios::beg);                                        //Volver al inicio del archivo
    archivo.close();

    return tamaño;
}

void binario(int tamaño, char *catexto, int *texbinario, string archivoleer){
    char cadena[tamaño];

    vector<int> vect;

    ifstream archivo;
    archivo.open(archivoleer);

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto no ce pudo abrir en la funcion binario."<<endl;
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

void metodo1(int tamaño, int semilla, int *texbinario, int *codificado, string nombre){
    int cont0=0, cont1=0, aux=0;

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

    ofstream archivo;
    archivo.open(nombre);

    if(archivo.fail()){
        cout<<"El archivo Codificado del metodo 1 no ce pudo crear."<<endl;
        exit(1);
    }

    for(int i=0; i<8*tamaño; i++)
        archivo<<codificado[i];

    archivo.close();
}

void metodo2(int tamaño, int semilla, int *texbinario, int *codificado, string nombre){
    int grupos;

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

    ofstream archivo;
    archivo.open(nombre);

    if(archivo.fail()){
        cout<<"El archivo Codificado con el metodo 2 no ce pudo crear."<<endl;
        exit(1);
    }

    for(int i=0; i<8*(tamaño); i++)
        archivo<<codificado[i];
    archivo.close();
}

void deco1(int tamaño, int semilla, int *texbinario, string nombre, string nombredeco){
    int cont0=0, cont1=0, aux=0, suma=0, pote[8]={128,64,32,16,8,4,2,1};
    char cadena[tamaño*8];

    ifstream archivo;
    archivo.open(nombre);

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto codificado con el metodo 1 no ce pudo abrir."<<endl;
        exit(1);
    }

    archivo.read(cadena, tamaño*8);                                    //Se agrega el texto al arreglo caracter por caracter
    archivo.close();

    for(int i=0; i<8*(tamaño); i++)                                    //Se llena el arreglo con enteros binarios
        texbinario[i] = (int)cadena[i]-48;

    for(int i=0; i<8*(tamaño); i=i+semilla){

        if(cont0 == cont1){                                            //el # de 1nos es igaul al # de 0ros.
            for(int j=i; j<i+semilla; j++){
                if(texbinario[j]==1) texbinario[j]=0;
                else
                    texbinario[j]=1;
            }
        }

        else if(cont0>cont1){                                             //ceros > unos (invierte cada 2 bits)
            aux=0;
            for(int j=i; j<i+semilla; j++){
                if(aux==1){                                              //Invierte el 2 bit
                    if(texbinario[j]==1) texbinario[j]=0;
                    else texbinario[j]=1;
                    aux=0;
                }
                else
                    aux++;
            }
        }

        else {                                                       //unos > ceros (invierte cada 3 bits)
            aux=0;
            for(int j=i; j<i+semilla; j++){
                if(aux==2){
                    if(texbinario[j]==1) texbinario[j]=0;
                    else texbinario[j]=1;
                    aux=0;
                }
                else
                    aux++;
            }
        }

        cont0=0;
        cont1=0;
        for(int j=i; j<i+semilla; j++){                             //Calcula contadores de la suma actual para analizar el
            if(texbinario[j]==1) cont1++;                         // siguiente ciclo
            else cont0++;
        }
    }

    cout<<endl;

    ofstream salida;
    salida.open(nombredeco);

    if(salida.fail()){
        cout<<"El archivo Decodificado por el metodo 1 no ce pudo crear."<<endl;
        exit(1);
    }

    aux=0;
    for(int i=0; i<8*(tamaño); i=i+8){                         //ciclo que recorre el arreglo de bits por grupos de n bits
        for(int j=i; j<i+8; j++){
            suma = suma + texbinario[j]*pote[aux];
            aux++;
        }
        aux=0;
        salida<<(char)suma;
        suma=0;
    }
    archivo.close();
}

void deco2(int tamaño, int semilla, int *texbinario, int *codificado, string nombre, string nombredeco){
    int aux=0, suma=0, grupos=0, pote[8]={128,64,32,16,8,4,2,1};
    char cadena[tamaño*8];

    ifstream archivo;
    archivo.open(nombre);

    cout<<endl;
    if(archivo.fail()){
        cout<<"El archivo texto a decodificar con el metodo 2 no ce pudo abrir."<<endl;
        exit(1);
    }

    archivo.read(cadena, tamaño*8);                                    //Se agrega el texto al arreglo caracter por caracter
    archivo.close();

    for(int i=0; i<8*(tamaño); i++)                                    //Se llena el arreglo con enteros binarios
        codificado[i] = (int)cadena[i]-48;


    for(int i=0; i<8*(tamaño); i=i+semilla){                                //Se recorre el arreglo binario por grupos de n

        for(int j=i; j<i+semilla; j++){                                     //Se recorre cada grupo de n escogido

            if(j==(i+semilla-1))                                           //La ultima posicion se pone de primera
                texbinario[j]=codificado[i];

            else
                texbinario[j]=codificado[j+1];                             //Se corre una posicion a la derecha.
        }
    }

    if((8*tamaño)%semilla != 0){
        grupos=(8*tamaño)/semilla;

        for(int i=grupos*semilla; i<8*(tamaño); i++)
            texbinario[i]=codificado[i];
    }


    ofstream salida;
    salida.open(nombredeco);

    if(salida.fail()){
        cout<<"El archivo Decodificado con el metodo 2 no ce pudo crear."<<endl;
        exit(1);
    }

    aux=0;
    for(int i=0; i<8*(tamaño); i=i+8){                         //ciclo que recorre el arreglo de bits por grupos de n bits
        for(int j=i; j<i+8; j++){
            suma = suma + texbinario[j]*pote[aux];
            aux++;
        }
        aux=0;
        salida<<(char)suma;
        suma=0;
    }
    archivo.close();


}








