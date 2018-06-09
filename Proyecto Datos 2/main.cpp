#include<iostream>
#include<string>
#include<fstream>
#include "DLinkedList.h"
#include "Turing.h"
#include "Grafo.h"

using namespace std;

int main(){
    Turing turing;
    turing.crearGrafo("hola.txt");
    turing.crearCinta("00011");
    cout << "Cinta: " << turing.imprimirCinta() << endl << endl;
    turing.startTuring();
}
