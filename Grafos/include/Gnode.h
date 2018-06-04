#ifndef GNODE_H
#define GNODE_H
#include<LinkedList.h>

template <typename E>


class Gnode{
    public:
        E element;
        Gnode<E> *next;
        Gnode<E> *previous;
        LinkedList<E> *link = new LinkedList<E>();

        Gnode(E pElement, Gnode<E> *pNext, Gnode *pPrevious) {
            this->element = pElement;
            this->previous = pPrevious;
            this->next = pNext;
        }
        Gnode(Gnode<E> *pNext, Gnode *pPrevious){
            this->next = pNext;
            this->previous = pPrevious;
        }
        LinkedList<E> * getNodes(){
            return link;
        }


};
#endif // GNODE_H
