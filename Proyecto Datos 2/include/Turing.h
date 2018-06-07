#ifndef TURING_H
#define TURING_H
#include<iostream>
#include<string>
#include<fstream>
#include "Grafo.h"

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
    Grafo<string> *grafo;

    void lector(string fileName){
        string line;
        ifstream out(fileName.c_str());
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
            }else if(line[0] == 'G'){
                line.erase(0,2);
                string segmento;
                stringstream stream(line);
                while (getline(stream, segmento, ',')){
                    simbolosDeMaquina->append(segmento);
                }
            }else if(line[0] == 'T'){
                line.erase(0,2);
                transiciones->append(line);
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

    void insertarEstados(){
        DNode<string> *temp = estados->head->next;
        while(temp != estados->tail){
            grafo->append(temp->element);
            temp = temp->next;
        }
    }

    bool isTagValid(string pTag){
        string read;
        string write;
        string moveTo;
        bool isReadValid = false;
        bool isWriteValid = false;
        stringstream stream(pTag);
        getline(stream, read, ',');
        getline(stream, write, ',');
        getline(stream, moveTo, ',');
        if(moveTo == "<" || moveTo == ">" || moveTo == "-" || moveTo == "_"){
            DNode<string> *temp = simbolosDeMaquina->head->next;
            while(temp != simbolosDeMaquina->tail){
                if(read == temp->element){
                    isReadValid = true;
                }
                if(write == temp->element){
                    isWriteValid = true;
                }
                temp = temp->next;
            }
        }else{
            return false;
        }
        if(isReadValid && isWriteValid)
            return true;
        else
            return false;
    }

    bool isSymbolValid(string symbol){
        DNode<string> *temp = simbolosDeEntrada->head->next;
        bool isValid = false;
        while(temp != simbolosDeEntrada->tail){
            if(symbol == temp->element){
                    isValid = true;
            }
            temp = temp->next;
        }
        return isValid;
    }

    void insertarConexiones() throw(runtime_error){
        DNode<string> *temp = transiciones->head->next;
        string startNode;
        string finishNode;
        string tag;
        string element;
        while(temp != transiciones->tail){
            string segmento;
            element = temp->element;
            stringstream stream(element);
            getline(stream, segmento, ',');
            startNode = segmento;
            getline(stream, segmento, ',');
            tag = segmento + ",";
            getline(stream, segmento, ',');
            finishNode = segmento;
            getline(stream, segmento, ',');
            tag = tag + segmento + ",";
            getline(stream, segmento, ',');
            tag = tag + segmento;
            if(isTagValid(tag)){
                grafo->addConection(startNode,finishNode,tag);
                temp = temp->next;
            }else{
                throw runtime_error("A tag has invalid symbols.");
            }
        }
    }

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
        grafo = new Grafo<string>();
    }

    ~Turing(){
        delete estados;
        delete simbolosDeEntrada;
        delete simbolosDeMaquina;
        delete transiciones;
        delete estadosDeAceptacion;
        delete estadosDeRechazo;
        delete cabeza;
        delete grafo;
    }

    void crearGrafo(string fileName){
        lector(fileName);
        insertarEstados();
        insertarConexiones();
        grafo->imprimirGrafo();
    }

    void crearCinta(string userInput) throw(runtime_error){
        for(int i = 0; i < userInput.length(); i++){
            string symbol(1, userInput[i]);
            if(!isSymbolValid(symbol))
                throw runtime_error("An input symbol is not valid.");
            cabeza->append(symbol);
        }
    }
};

#endif // TURING_H
