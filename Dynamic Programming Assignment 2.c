#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;

        if(g.list[i]==NULL){
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else{
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g,i,j);
	
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    printGraphList(g);
    return 0;
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}
int BFS (Graph g, int v, int w) {
    
    Queue q;        //initialise a queue for BFS
    int i, u;       

    int *visited = malloc(g.V * sizeof(int));       //initialise an array to keep track of visited vertices
    int *distance = malloc(g.V * sizeof(int));      //initialise an array to keep track of the distance from root

    ListNode *temp;                                   //temp pointer to iterate through the graph
    
    for(i=0;i<g.V;i++) {                              //initialise the two arrays to default
        visited[i] = 0;
        distance[i] = -1;
    }

    visited[v-1] = 1;                               //let the value of the start vertex be = 1 to indicate visited
    distance[v-1] = 0;                              //let the distance of that vertex be = 0
    enqueue(&q, v);                      //enqueue the vertex to conduct bfs

    while(!isEmptyQueue(q)) {                       //keep going until the queue is empty or the destination node w is found
        u = getFront(q);                          //let the head of the queue q be = u
        dequeue(&q);                        //dequeue q

        temp = g.list[u-1];                       //let temp be = to the head of the linked list of vertices adjacent to u
        while(temp!=NULL) {                       //to process until temp == NULL meaning all the vertices adjacent to u is processed
            if(!visited[temp->vertex-1]) {         //keep processing the linked list of vertices until visited = 0
                visited[temp->vertex-1] = 1;      //if visited == 0, then make visited = 1, and increase distance by 1 because it is 1 away from the parent u
                distance[temp->vertex-1] = distance[u-1]+1;
                enqueue(&q, temp->vertex);   //enqueue that vertex
            }
            if(temp->vertex == w)                //if it is equal to w, then return the data for distance stored in the distance array
                return distance[w-1];

            temp = temp->next;                 //keep iterating through the adjacent vertices
        }
    }
    return -1;
}
