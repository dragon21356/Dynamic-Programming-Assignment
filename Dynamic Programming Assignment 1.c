#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}
typedef struct _listnode{
        int vertex;
	    struct _listnode *next;
    } ListNode;

typedef ListNode QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

int isEmptyQueue(Queue q);

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

int BFS ();

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);


int* city_population(int N, int* population, int** road, int Q, int** cities) {

    int **adj_list = (int **)malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {                                  //create adjacency list
        adj_list[i] = (int *)malloc(N * sizeof(int));
        int num_roads = 0;
        for (int j = 0; j < N-1; j++) {
            if (road[j][0] == i+1) {
                adj_list[i][num_roads++] = road[j][1];
            } else if (road[j][1] == i+1) {
                adj_list[i][num_roads++] = road[j][0];
            }
        }
        // set the end of the array to -1 to indicate the end of the list
        adj_list[i][num_roads] = -1;
    }
    
    int *total_list = malloc(N*sizeof(int));                      //create array

    for(int k = 0; k<Q; k++){
       total_list[k] = BFS(adj_list, N, cities[k][0], cities[k][1], cities [k][2], population);            //manage multiple queries
    }

    return total_list;
}

int BFS(int **adj_list, int N, int v, int w, int limit, int *population) {
    Queue q;
    int i, u;
    int *visited = malloc(N * sizeof(int));
    int *parent = malloc(N * sizeof(int));
    ListNode *temp;
    int count = 0;

    for(i=0;i<N;i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[v-1] = 1;
    enqueue(&q, v);

    while(!isEmptyQueue(q)) {
        u = getFront(q);
        dequeue(&q);

        for (i = 0; adj_list[u-1][i] != -1; i++) {
            int vertex = adj_list[u-1][i];
            if (!visited[vertex-1]) {
                visited[vertex-1] = 1;
                parent[vertex-1] = u;
                
                if (vertex == w) {
                    // build path and return
                    int *path = calloc(N, sizeof(int));
                    int j = 0;
                    while (vertex != -1) {
                        path[j++] = vertex;
                        vertex = parent[vertex-1];
                    }       

                    for(int j = 0; j<N; j++){
                        if (path[j] == 0){
                            break;
                        }

                        if (population[path[j]-1] <= limit){
                            count++;
                        }
                    }

                return count;
                }
            enqueue(&q, vertex);
            }
        }
    }

     return 0; // if no path exists, return NULL
}