#ifndef LINKNODE_H
#define LINKNODE_H
#include <Gnode.h>

template <typename E>

class LinkNode{
    public:
        E tag;
        Gnode<E> *nextNode;
        LinkNode(E element, Gnode<E> *node) {
            this->tag = element;
            this->nextNode = node;
        }
        LinkNode(Gnode<E> *node){
            this->nextNode = node;
        }
};

#endif // LINKNODE_H
