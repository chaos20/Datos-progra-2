#ifndef GRAFO_H
#define GRAFO_H
#include "GNode.h"
#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;
using std::stringstream;

template <typename E>

class Grafo{
private:
    GNode<E> *head;
    GNode<E> *tail;
    GNode<E> *current;
    int size;

public:
    Grafo(){
        current = head = new GNode<E>(NULL,NULL);
        head->next = tail = new GNode<E>(NULL,head);
        size = 0;
    }

    ~Grafo(){
        clear();
        delete head;
        delete tail;
    }

    void append(E pElement){
        tail->previous = tail->previous->next = new GNode<E>(pElement,tail,tail->previous);
        size++;
    }

    E getElement() throw (runtime_error){
        if(size==0){
            throw runtime_error("Empty List");
        }
        if(current->next == tail){
            throw runtime_error("No current element");
        }
        return current->next->element;
    }

    void goToStart(){
         current = head;
    }

    void goToEnd(){
        current = tail->previous;
    }

    void next(){
        if(current->next != tail){
            current = current->next;
        }
    }

    void previous(){
        if(current != head){
            current = current->previous;
        }
    }

    bool atEnd(){
        return current->next == tail;
    }

    bool atStart(){
        return current == head;
    }

    void clear(){
        current = head->next;
        while(current != tail){
            head->next = head->next->next;
            delete current;
            current = head->next;
        }
        tail->previous = head;
        current = head;
        size = 0;
    }

    int getSize(){
        return size;
    }

    int getPos(){
        int pos = 0;
        GNode<E> *temp = head;
        while(temp != current){
            pos++;
            temp = temp->next;
        }
        return pos;
    }

    //M�todo que verifica si un elemento se encuentra en el grafo
    bool contains(E pElement){
        if(size == 0)
            return false;
        else{
            GNode<E> *temp = head->next;
            while(temp != tail){
                if(temp->element == pElement)
                    return true;
                temp = temp->next;
            }
            return false;
        }
    }

    //M�todo que coloca a current en el nodo dado por par�metro
    void goToElement(E pElement){
        bool keepSearching = true;
        GNode<E> *temp = head->next;
        goToStart();
        while(temp != tail && keepSearching){
            if(temp->element == pElement)
                keepSearching = false;
            else{
                temp = temp->next;
                next();
            }
        }
        next();
    }

    //M�todo que coloca a current un nodo atr�s del dado por par�metro
    void goToPreviousElement(E pElement){
        bool keepSearching = true;
        GNode<E> *temp = head->next;
        goToStart();
        while(temp != tail && keepSearching){
            if(temp->element == pElement)
                keepSearching = false;
            else{
                temp = temp->next;
                next();
            }
        }
    }

    //M�todo que recibe el nodo de donde se va a hacer la transici�n, el nodo a donde va a hacer la transici�n y el tag (condici�n) para que la transici�n suceda
    void addConection(E startNode, E finishNode, string pTag) throw (runtime_error){
        if(contains(startNode)){
            goToElement(startNode);
            if(contains(finishNode)){
                if(!current->conections->checkDuplicatedTags(pTag))
                    current->conections->append(finishNode, pTag);
                else
                    throw runtime_error("Tag is already used.");
            }else
                throw runtime_error("finishNode not found.");
        }else
            throw runtime_error("startNode not found.");
    }

    GNode<E> *getCurrent(){
        return this->current;
    }

    //M�todo que imprime el grafo mostrando cada nodo del grafo y sus conexiones
    void imprimirGrafo(){
        GNode<string> *temp = head->next;
        while(temp != tail){
            cout << "Nodo: " << temp->element << endl << "Conexiones: ";
            cout << temp->conections->printList() << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    //M�todo que recibe el nodo de donde se va a hacer la transici�n y el s�mbolo al que la cabeza apunta en la cinta y retorna el nodo al que se deber�a hacer la transici�n
    string checkConection(string startNode, string symbol){
        goToElement(startNode);
        DNode<string> *temp = current->conections->head->next;
        while(temp != current->conections->tail){
            if(temp->tag[0] == symbol[0]){
                return temp->element;
            }
            temp = temp->next;
        }
    }

    //M�todo que recibe el nodo de donde se va a hacer la transici�n y el s�mbolo al que la cabeza apunta en la cinta y retorna el tag relacionado a dicho s�mbolo
    string getTag(string startNode, string symbol){
        goToElement(startNode);
        DNode<string> *temp = current->conections->head->next;
        while(temp != current->conections->tail){
            if(temp->tag[0] == symbol[0]){
                return temp->tag;
            }
            temp = temp->next;
        }
    }
};

#endif // GRAFO_H
