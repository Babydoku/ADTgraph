#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

static void expandNodeCapacity(Graph* graph);
static void expandEdgeCapacity(Num* num);
static void DFSUtil(Graph* graph, NumID numID, bool* visited);
static void BFSUtil(Graph* graph, NumID startNumID, bool* visited);

Graph* createEmptyGraph(void) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    

    graph->nums = (Num*)malloc(sizeof(Num) * 10);
   

    graph->numCount = 0;
    graph->numCapacity = 10;
    graph->nextID = 0;

    return graph;
}

bool isGraphEmpty(Graph* graph) {
   
    return graph->numCount == 0;
}

int addNum(Graph* graph, int value) {
    assert(graph != NULL);

    if (graph->numCount >= graph->numCapacity) {
        expandNodeCapacity(graph);
    }

    Num* num = &graph->nums[graph->numCount];
    num->value = value;
    num->edges = (NumID*)malloc(sizeof(NumID) * 10);
    num->edgeCount = 0;
    num->edgeCapacity = 10;

    int ID = graph->nextID++;
    graph->numCount++;

    
    assert(graph->numCount > 0);

    return ID;
}

void addDirectedEdge(Graph* graph, NumID startNumID, NumID endNumID) {
  
    Num* num = &graph->nums[startNumID];
    if (num->edgeCount >= num->edgeCapacity) {
        expandEdgeCapacity(num);
    }
    num->edges[num->edgeCount++] = endNumID;
   
}

void addEdge(Graph* graph, NumID numID1, NumID numID2) {
    addDirectedEdge(graph, numID1, numID2);
    addDirectedEdge(graph, numID2, numID1);
}

void printGraphByID(Graph* graph) {
   
    for (int i = 0; i < graph->numCount; i++) {
        Num* num = &graph->nums[i];
        printf("Num ID: %d, Value: %d, Edges: ", i, num->value);
        for (int j = 0; j < num->edgeCount; j++) {
            printf("%d ", num->edges[j]);
        }
        printf("\n");
    }
}

void printGraphDFS(Graph* graph, NumID startNumID) {
    bool* visited = (bool*)malloc(sizeof(bool) * graph->numCount);
    memset(visited, 0, sizeof(bool) * graph->numCount);
    DFSUtil(graph, startNumID, visited);
    free(visited);
}

void DFSUtil(Graph* graph, NumID numID, bool* visited) {
    visited[numID] = true;
    printf("Visited Num ID: %d, Value: %d\n", numID, graph->nums[numID].value);

    for (int i = 0; i < graph->nums[numID].edgeCount; i++) {
        NumID adjacentID = graph->nums[numID].edges[i];
        printf("Num/edge: %d -> %d\n", numID, adjacentID);  
        if (!visited[adjacentID]) {
            DFSUtil(graph, adjacentID, visited);
        }
    }
}

void printGraphBFS(Graph* graph, NumID startNumID) {
    bool* visited = (bool*)malloc(sizeof(bool) * graph->numCount);
    BFSUtil(graph, startNumID, visited);
    free(visited);
}

void BFSUtil(Graph* graph, NumID startNumID, bool* visited) {
    int* queue = (int*)malloc(sizeof(int) * graph->numCount);
    assert(queue != NULL);

    int front = 0, rear = 0;

    visited[startNumID] = true;
    queue[rear++] = startNumID;

    while (front != rear) {
        int numID = queue[front++];
        printf("Visited Num ID: %d, Value: %d\n", numID, graph->nums[numID].value);
        
        

        for (int i = 0; i < graph->nums[numID].edgeCount; i++) {
            NumID adjacentID = graph->nums[numID].edges[i];
            if (!visited[adjacentID]) {
                visited[adjacentID] = true;
                queue[rear++] = adjacentID;
                printf("Num/edge: %d -> %d\n", numID, adjacentID);
            }
        }
    }

    free(queue);
}

void clearGraph(Graph* graph) {
   
    for (int i = 0; i < graph->numCount; i++) {
        free(graph->nums[i].edges);
    }
    free(graph->nums);
    free(graph);
}

static void expandNodeCapacity(Graph* graph) {
   
    graph->numCapacity *= 2;
    graph->nums = (Num*)realloc(graph->nums, sizeof(Num) * graph->numCapacity);
   
}

static void expandEdgeCapacity(Num* num) {
  
    num->edgeCapacity *= 2;
    num->edges = (NumID*)realloc(num->edges, sizeof(NumID) * num->edgeCapacity);
  
}
