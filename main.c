#include <stdio.h>
#include "graph.h"


// BFS - (hittar den korstade vägen till destinationen, medans DFS går till botten av ett underträd och backar sedan)

int main(void) {
    
    Graph* graph = createEmptyGraph();

   
    int n1 = addNum(graph, 10);
    int n2 = addNum(graph, 20);
    int n3 = addNum(graph, 30);

   
    addEdge(graph, n1, n2);
    addDirectedEdge(graph, n1, n3);

 
    printGraphByID(graph);

   
    printf("DFS:\n");
    printGraphDFS(graph, n1);


    printf("BFS:\n");
    printGraphBFS(graph, n1);


    return 0;
}
