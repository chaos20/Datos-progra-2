#ifndef TURING_H
#define TURING_H
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Turing{
private:
    DLinkedList<string> *estados;
    DLinkedList<string> *simbolosDeEntrada;
    DLinkedList<string> *simbolosDeMaquina;
    DLinkedList<string> *transiciones;
    string estadoInicial;
    string caracterBlanco;
    DLinkedList<string> *estadosDeAceptacion;
    DLinkedList<string> *estadosDeRechazo;
    DLinkedList<string> *cabeza;
public:
    Turing(){
        estados = new DLinkedList<string>();
        simbolosDeEntrada = new DLinkedList<string>();
        simbolosDeMaquina = new DLinkedList<string>();
        transiciones = new DLinkedList<string>();
        string estadoInicial;
        string caracterBlanco;
        estadosDeAceptacion = new DLinkedList<string>();
        estadosDeRechazo = new DLinkedList<string>();
        cabeza = new DLinkedList<string>();
    }

    ~Turing(){
        delete estados;
        delete simbolosDeEntrada;
        delete simbolosDeMaquina;
        delete transiciones;
        delete estadosDeAceptacion;
        delete estadosDeRechazo;
        delete cabeza;
    }

    void lector(){
        string line;
        ifstream out("hola.txt");
        while(getline(out, line)) {
            if(line[0] == 'Q'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    estados->append(segmento);
                }
            }else if(line[0] == 'S'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    simbolosDeEntrada->append(segmento);
                }
            }else if(line[0] == 'T'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    transiciones->append(segmento);
                }
            }else if(line[0] == 'I'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    estadoInicial = segmento;
                }
            }else if(line[0] == 'B'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    caracterBlanco = segmento;
                }
            }else if(line[0] == 'F'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    estadosDeAceptacion->append(segmento);
                }
            }else{
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    estadosDeRechazo->append(segmento);
                }
            }
        }
        out.close();
    }
};

#endif // TURING_H
