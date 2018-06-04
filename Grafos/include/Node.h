#ifndef NODE_H
#define NODE_H
#include <stdlib.h>


using namespace std;

template <typename E>

class Node{
    public:
        E element;
        E tag;
        Node<E> *next;

        Node(E element ,E tag, Node<E>*next = NULL) {
            this -> element = element;
            this->tag = tag;
            this -> next = next;
        }
         Node(Node<E>*next = NULL){
             this -> next = next;
         }
};

#endif // NODE_H
