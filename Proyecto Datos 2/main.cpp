#include<iostream>
#include<string>
#include<fstream>
#include "DLinkedList.h"
#include "Turing.h"
#include "Grafo.h"

using namespace std;

int main(){
    /*Turing turing;
    turing.lector();*/

    Grafo<string> miGrafo;
    miGrafo.append("A");
    miGrafo.append("B");
    miGrafo.append("C");
    miGrafo.append("D");
    miGrafo.append("E");
    miGrafo.addConection("A","B","caca");
    miGrafo.addConection("A","C","caca");
}
