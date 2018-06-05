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

    /*void insert(E pElement){
        current->next = current->next->previous = new GNode<E>(pElement,current->next,current);
        size++;
    }*/

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

    /*E remove() throw (runtime_error){
        if(size==0){
            throw runtime_error("Empty List");
        }
        if(current->next == tail){
            throw runtime_error("No current element");
        }
        Gnode<E> *temp = current->next;
        current->next = current->next->next;
        current->next->previous = current;
        E result = temp->element;
        size--;
        return result;
    }*/

    /*void goToPos(int pos){
        if(pos<0 || pos>size){
            throw runtime_error("index out of bounds");
        }
        int i = 0;
        for(goToStart(); i < pos; next()){
            i++;
        }
    }*/

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
    }

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
};

#endif // GRAFO_H
