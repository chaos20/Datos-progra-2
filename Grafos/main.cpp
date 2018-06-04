#include <iostream>
#include <string>
#include <GraphList.h>
#include <LinkedList.h>

using namespace std;

int main(){
    GraphList<string> grafo;
    grafo.append("A");
    grafo.append("B");
    grafo.append("C");
    grafo.goToStart();
    for(int i = 0; i < grafo.getSize(); i++){
        cout << grafo.getElement() <<endl;
        grafo.next();
    }
    grafo.goToStart();
    grafo.addLinkAndNode("B","caso1");
    grafo.addLinkAndNode("C","Caso_2");
    for(int i = 0; i < grafo.getCurrent()->getNodes()->getSize(); i++){
        cout << grafo.getCurrent()->getNodes()->getElement() << endl;
        cout << grafo.getCurrent()->getNodes()->getTag() << endl;
        grafo.getCurrent()->getNodes()->next();
    }
    return 0;
}
