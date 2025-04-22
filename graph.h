#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef int NumID;

typedef struct Num {
    int value;
    NumID* edges;
    int edgeCount;
    int edgeCapacity;
} Num;

typedef struct Graph {
    Num* nums;
    int numCount;
    int numCapacity;
    NumID nextID;
} Graph;


Graph* createEmptyGraph(void);
bool isGraphEmpty(Graph* graph);
int addNum(Graph* graph, int value);
void addDirectedEdge(Graph* graph, NumID startNumID, NumID endNumID);
void addEdge(Graph* graph, NumID numID1, NumID numID2);
void printGraphByID(Graph* graph);
void printGraphDFS(Graph* graph, NumID startNumID);
void printGraphBFS(Graph* graph, NumID startNumID);
void clearGraph(Graph* graph);

#endif 
