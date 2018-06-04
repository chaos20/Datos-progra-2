#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#include <List.h>
#include <Gnode.h>
#include <LinkedList.h>
#include <stdexcept>

using std::runtime_error;

template <typename E>


class GraphList : public List<E>{
    public:
        GraphList() {
            current = head = new Gnode<E>(NULL,NULL);
            head->next = tail = new Gnode<E>(NULL,head);
            size = 0;
        }
        ~GraphList() {
            clear();
            delete head;
            delete tail;
        }
        void insert(E element){
            current->next = current->next->previous = new Gnode<E>(element,current->next,current);
            size++;
        }
        void append(E element){
            tail->previous = tail->previous->next = new Gnode<E>(element,tail,tail->previous);
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
        E remove() throw (runtime_error){
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
            Gnode<E> *temp = head;
            while(temp != current){
                pos++;
                temp = temp->next;
            }
            return pos;
        }
        void addLinkAndNode(E element, E tag){
            current->link->append(element,tag);
        }
        Gnode<E> *getCurrent(){
            return this->current;
        }

    private:
        Gnode<E> *head;
        Gnode<E> *tail;
        Gnode<E> *current;
        int size;
};

#endif // GRAPHLIST_H
