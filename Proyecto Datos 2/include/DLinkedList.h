#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include <List.h>
#include <DNode.h>
#include <stdexcept>
#include <string>
#include <sstream>

using std::string;
using std::runtime_error;
using std::stringstream;

template <typename E>

class DLinkedList : public List<E>{
public:
    DNode<E> *head;
    DNode<E> *tail;
    DNode<E> *current;
    int size;
public:
    DLinkedList(){
        current = head = new DNode<E>(NULL,NULL);
        head->next = tail = new DNode<E>(NULL,head);
        size = 0;
    }

    ~DLinkedList(){
        clear();
        delete tail;
        delete head;
    }

    void insert(E pElement, string tag = ""){
        current->next=current->next->previous = new DNode<E>(pElement, tag, current->next, current);
        size++;
    }

    void append(E pElement, string tag = ""){
        tail->previous = tail->previous->next = new DNode<E>(pElement, tag, tail, tail->previous);
        size++;
    }

    E remove() throw (runtime_error){
        if(size==0)
            throw runtime_error("Empty List");
        if(current->next == tail)
            throw runtime_error("No current element");
        DNode<E> *temp = current->next;
        current->next = current->next->next;
        current->next->previous = current;
        E result = temp->element;
        size--;
        return result;
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

    E getElement() throw (runtime_error){
        if(size==0)
            throw runtime_error("Empty List");
        if(current->next == tail)
            throw runtime_error("No current element");
        return current->next->element;
    }

    void goToStart(){
        current = head;
    }

    void goToEnd(){
        current = tail->previous;
    }

    void goToPos(int pos){
        if(pos<0 || pos>size){
            throw runtime_error("index out of bounds");
        }
        int i = 0;
        for(goToStart(); i < pos; next()){
            i++;
        }
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

    int getPos(){
        int pos = 0;
        DNode<E> *temp = head;
        while(temp != current){
            pos++;
            temp = temp->next;
        }
        return pos;
    }

    int getSize(){
        return size;
    }

    string printList(){
        if(size == 0)
            return "Empty List";
        else{
            DNode<E> *temp = head->next;
            string stringList = "";
            while(temp != tail){
                stringstream ss;
                ss << temp->element;
                string s = ss.str();
                stringList = stringList+ s + "->";
                temp = temp->next;
            }
            return stringList;
        }
    }

    DNode<E> getHead(){
        return *head;
    }

    DNode<E> getTail(){
        return *tail;
    }

    bool contains(E pElement){
        if(size == 0)
            return false;
        else{
            DNode<E> *temp = head->next;
            while(temp != tail){
                if(temp->element == pElement)
                    return true;
                temp = temp->next;
            }
            return false;
        }
    }

    bool checkDuplicatedTags(string pTag){
        if(size == 0)
            return false;
        else{
            DNode<E> *temp = head->next;
            while(temp != tail){
                if(temp->tag == pTag)
                    return true;
                temp = temp->next;
            }
            return false;
        }
    }
};

#endif // DLINKEDLIST_H
