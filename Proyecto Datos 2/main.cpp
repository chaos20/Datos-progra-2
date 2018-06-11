#include<iostream>
#include<string>
#include<fstream>
#include "DLinkedList.h"
#include "Turing.h"
#include "Grafo.h"

using namespace std;

int main(){
    while(true){
        Turing turing;
        string opcion ="";
        cout << "bienvenido, por favor elija entre una se las siguientes opciones: " <<
        "s para detener la maquina, i para cargar un archivo y brindar una cinta, r para reiniciar la maquina" << endl;
        cin >> opcion;
        if(opcion == "i"){
            Turing turing;
            string nombreArchivo = "";
            string cinta = "";
            cout << "por favot ingrese el nombre del archivo con la extension (.txt): " << endl;
            cin >> nombreArchivo;
            cout << "ingrese la cinta a leer: " << endl;
            cin >> cinta;
            turing.crearGrafo(nombreArchivo);
            turing.crearCinta(cinta);
            string desicion = "";
            cout << "Ingrese c para continuar o s para salir" << endl;
            cin >> desicion;
            while(desicion == "c"){
                int result = turing.startTuring(true);
                if(result == 0 || result == -1){
                    turing.dibujarGrafo();
                    getch();
                    break;
                }
                cout << "Ingrese c para continuar o s para salir" << endl;
                cin >> desicion;
            }
        }
        if(opcion == "s"){
            break;
        }
        if(opcion == "r"){

        }
    }
    /*Turing turing;
    turing.crearGrafo("hola.txt");
    turing.crearCinta("00011");
    cout << "Cinta: " << turing.imprimirCinta() << endl << endl;
    turing.startTuring();
    turing.dibujarGrafo();
    getch();*/
}
