#ifndef DNODE_H
#define DNODE_H

using namespace std;

template <typename E>

class DNode {
public:
    E element;
    DNode<E> *next;
    DNode<E> *previous;
    string tag;

    DNode(E element, string tag, DNode<E> *next, DNode *previous){
        this->element = element;
        this->tag = tag;
        this->next = next;
        this->previous = previous;
    }

    DNode(DNode<E> *next, DNode<E> *previous){
        this->next = next;
        this->previous = previous;
    }
    string getTag(){
        return tag;
    }
};
#endif // DNODE_H
