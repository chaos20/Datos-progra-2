#ifndef GNODE_H
#define GNODE_H
#include "DLinkedList.h"

template <typename E>


class GNode{
    public:
        E element;
        GNode<E> *next;
        GNode<E> *previous;
        DLinkedList<E> *conections = new DLinkedList<E>();

        GNode(E pElement, GNode<E> *pNext, GNode<E> *pPrevious) {
            this->element = pElement;
            this->previous = pPrevious;
            this->next = pNext;
        }
        GNode(GNode<E> *pNext, GNode<E> *pPrevious){
            this->next = pNext;
            this->previous = pPrevious;
        }
        DLinkedList<E>* getNodes(){
            return conections;
        }


};
#endif // GNODE_H
