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

    //Método que recibe el nombre del archivo que se quiere leer con su respectiva extensión, lee lo que está escrito en el archivo y crea los atributos de la clase
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
                    cout << segmento << endl;
                    estadosDeRechazo->append(segmento);
                }
            }
        }
        out.close();
    }

    //Método que lee la lista de estados y los inserta en el grafo
    void insertarEstados(){
        DNode<string> *temp = estados->head->next;
        while(temp != estados->tail){
            grafo->append(temp->element);
            temp = temp->next;
        }
    }

    //Método que verifica si los símbolos que tiene el tag son válidos
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

    //Método que verifica si un símbolo de entrada es válido
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

    //Método que lee la lista de transiciones y las inserta en el grafo
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

    //Método que verifica si un estado dado por parámetro es un estado de rechazo
    bool esEstadoDeRechazo(string estado){
        DNode<string> *temp = estadosDeRechazo->head->next;
        while(temp != estadosDeRechazo->tail){
            if(temp->element == estado)
                return true;
            temp = temp->next;
        }
        return false;
    }

    //Método que verifica si un estado dado por parámetro es un estado de aceptación
    bool esEstadoDeAceptacion(string estado){
        DNode<string> *temp = estadosDeAceptacion->head->next;
        while(temp != estadosDeAceptacion->tail){
            if(temp->element == estado)
                return true;
            temp = temp->next;
        }
        return false;
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

    //Método que llama a varias funciones necesarias para crear el grafo
    void crearGrafo(string fileName){
        lector(fileName);
        insertarEstados();
        insertarConexiones();
        grafo->imprimirGrafo();
    }

    //Método que recibe una serie de caracteres por el usuario y crea la cinta a partir de ellos
    void crearCinta(string userInput) throw(runtime_error){
        int stringLength = userInput.length();
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        for(int i = 0; i < stringLength; i++){
            string symbol(1, userInput[i]);
            if(!isSymbolValid(symbol))
                throw runtime_error("An input symbol is not valid.");
            cabeza->append(symbol);
        }
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
        cabeza->append(caracterBlanco);
    }

    //Método que imprime la cinta
    string imprimirCinta(){
        return cabeza->printList();
    }
    void dibujarGrafo(){
        grafo->goToStart();
        GraficadorTuring g(850, 800, grafo->getSize());
        for(int n = 0; n < grafo->getSize(); n++){
            g.asignarNombreEstado(n,grafo->getElement());
            grafo->next();
        }
        grafo->goToStart();
        while(!grafo->atEnd()){
            DLinkedList<string> *conexiones = grafo->getCurrent()->getNodes();
            if(conexiones->getSize() == 0){
                grafo->next();
            }
            else{
                conexiones->goToStart();
                while(!conexiones->atEnd()){
                    string actual = grafo->getElement();
                    string valorBus = conexiones->getElement();
                    string  tag = conexiones->getTag();
                    int finishPos = grafo->buscar(valorBus);
                    int inipos = grafo->buscar(actual);
                    g.asignarTransicion(inipos,finishPos,tag);
                    conexiones->next();
                }
                grafo->next();
            }

        }
        g.dibujarEstados();
    }

    //Método que lee la cinta caracter por caracter y en base a ellos, realiza distintas transiciones en el grafo (es el método que hace que la máquina de Turing funcione)
    int startTuring(bool cont){
        grafo->goToStart();
        grafo->goToPreviousElement(estadoInicial);
        cabeza->goToFirstElement();
        bool keepRunning = true;
        string element;
        string startNode = grafo->getElement();
        string finishNode;
        string tag;
        string read;
        string write;
        string moveTo;
        while(keepRunning && cont){
            element = cabeza->getElement();
            finishNode = grafo->checkConection(startNode, element);
            tag = grafo->getTag(startNode, element);
            grafo->goToStart();
            grafo->goToPreviousElement(startNode);
            cout << "Se leyo un " << element << ", entonces se hace un movimiento del nodo " << grafo->getElement() << " al nodo " << finishNode << " cuya tag es " << tag << endl;
            stringstream stream(tag);
            getline(stream, read, ',');
            getline(stream, write, ',');
            getline(stream, moveTo, ',');
            cabeza->current->next->element = write;
            cout << "Cinta: " << cabeza->printList() << endl << endl;
            if(moveTo == "<")
                cabeza->previous();
            else if(moveTo == ">")
                cabeza->next();
            grafo->goToPreviousElement(finishNode);
            startNode = grafo->getElement();
            if(esEstadoDeAceptacion(startNode)){
                cout << "Se llego a un estado de aceptacion" << endl;
                keepRunning = false;
                return 0;
            }else if(esEstadoDeRechazo(startNode)){
                cout << "Se llego a un estado de rechazo" << endl;
                keepRunning = false;
                return -1;
            }else{
                return 1;
            }
        }
    }

};

#endif // TURING_H
