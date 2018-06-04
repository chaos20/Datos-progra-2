#ifndef ARISTA_H
#define ARISTA_H
#include "Node.h"

template <typename E>


class arista{
    public:
        E tag;
        Node<E> *nextNode;
        arista(E element, Node<E> *node) {
            this->tag = element;
            this->nextNode = node;
        }
        arista(E element) {
            this->tag = element;
            this->nextNode = NULL;
        }
        arista(Node<E> *node) {
            this->nextNode = node;
        }

    protected:

    private:
};
#endif // ARISTA_H
