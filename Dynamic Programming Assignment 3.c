#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

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

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

int CC (Graph g);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

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

    int res = CC(g);
    if(res ==1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

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

void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
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

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}


int CC (Graph g)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i, u;
    int count = 0;

    int *visited = malloc(g.V * sizeof(int));

    ListNode *temp;

    for(i=0;i<g.V;i++){
        visited[i] = 0;
    }

    push(&s,0);

    while(!isEmptyStack(s)){                                //DFS method to iterate through and count number of nodes
        u = peek(s); 
        pop(&s);

        if(!visited[u]){
            visited[u] = 1;
            count++;
            
            temp = g.list[u];
            while(temp!=NULL){
                push(&s,temp->vertex-1);
                temp = temp->next;
            }
        }          
    }

    Graph h;                                                                            //transpose the graph using the adjacency list
    h.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        h.list[i] = NULL;

    ListNode *temp2;

    for(i = 0; i<g.V; i++){
        temp2 = g.list[i];
        while(temp2!=NULL){        
            ListNode *temp3 = (ListNode *)malloc(sizeof(ListNode));
            temp3->vertex = i+1;
            temp3->next = h.list[temp2->vertex-1];
            h.list[temp2->vertex-1] = temp3;

            temp2 = temp2->next;
        }
    }
        
    int count2 = 0;
    removeAllItemsFromStack(&s);

    for(i=0;i<g.V;i++){                                                             //run DFS again on the transposed graph
        visited[i] = 0;
    }

    push(&s,0);

    while(!isEmptyStack(s)){
        u = peek(s); 
        pop(&s);

        if(!visited[u]){
            visited[u] = 1;
            count2++;
            
            temp = h.list[u];
            while(temp!=NULL){
                push(&s,temp->vertex-1);
                temp = temp->next;
            }
        }          
    }

    
    return (count == g.V && count == count2);                                     //return 1 if the two traversals return the same value to each other and the same as the total count else return 0
}
