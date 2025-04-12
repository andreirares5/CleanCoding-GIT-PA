/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE; 
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    


typedef struct graph
{
    int vertices;
    int *visited;
    struct Node **adjlist;
}GPH;

typedef struct stack
{
    int top;
    int stack_cap;
    int *array;
}STK;

NODE *create_node(int value)
{
    NODE *new = (NODE*)malloc(sizeof(NODE));
    new->data = value;
    new->next = NULL;
    return new;
}

void add_edge(GPH *graph,int source,int destination)
{
    NODE *new = create_node(destination);

    new->next = graph->adjlist[source];
    graph->adjlist[source] = new;

    new = create_node(source);

    new->next = graph->adjlist[destination];
    graph->adjlist[destination] = new;
}

GPH *create_graph(int number_of_vertices)
{
    int i;

    GPH *graph = (GPH*)malloc(sizeof(GPH));
    graph->vertices = number_of_vertices;

    graph->adjlist = (NODE**)malloc(sizeof(NODE *)* number_of_vertices);
    graph->visited = (int*)malloc(sizeof(int) * number_of_vertices);

    for (i = 0 ; i<number_of_vertices ; i++)
    {
        graph->adjlist[i] = NULL;
        graph->visited[i] = 0;
    }    
    return graph;
}

STK *create_stack(int stack_cap)
{
    STK *stack = (STK*)malloc(sizeof(STK));
    stack->array = (int*)malloc(stack_cap * sizeof(int));
    stack->top = -1;
    stack->stack_cap = stack_cap;

    return stack;
}

void push(int value,STK *stack)
{
    stack->top = stack->top+1;
    stack->array[stack->top] = value;
}

void DFS(GPH *graph,STK *stack,int vertex_index)
{
    NODE *adjlist = graph->adjlist[vertex_index];
    NODE *aux = adjlist;
    graph->visited[vertex_index] = 1;

    printf("%d ",vertex_index);
    push(vertex_index , stack);

    while (aux != NULL)
    {
        int connected_vertex = aux->data;
            if (graph->visited[connected_vertex] == 0)
            DFS(graph , stack , connected_vertex);

        aux=aux->next;
    }
}

void insert_edges(GPH *graph , int number_of_edges , int number_of_vertices)
{
    int source,destination,i;

    printf("Adauga %d munchii (de la 1 la %d)\n",number_of_edges,number_of_vertices);
    for (i = 0 ; i<number_of_edges ; i++)
    {
        scanf("%d%d", &source ,&destination);
        add_edge(graph, source-1 , destination-1);  //daca numerotarea incepe de la 1,dar vectorii sunt indexati de la 0
    }
}

void wipe(GPH *graph, int number_of_vertices)
{
    for (int i = 0 ; i<number_of_vertices ; i++)
    {
        graph->visited[i] = 0;
    }
}

int next_DFS(GPH* graph, STK* stack, int start, int target) 
{
    stack->top = -1;
    wipe(graph, graph->vertices);
    
    DFS(graph, stack, start);

    for (int i = 0; i <= stack->top; i++)
    {
        if (stack->array[i] == target)
            return 1; 
    }
    return 0;
}

int has_direct_edge(GPH *graph, int source, int destination) 
{
    NODE *current = graph->adjlist[source];
    while (current != NULL)
     {
        if (current->data == destination)
     {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}
int main()
{

    int number_of_vertices, number_of_edges, source, destination;

    printf("Cate noduri are graful? "); 
    scanf("%d", &number_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &number_of_edges);

    GPH *graph = create_graph(number_of_vertices);

    STK *stack1 = create_stack(2 * number_of_vertices);

    insert_edges(graph, number_of_edges, number_of_vertices);


    printf("Introdu doua restaurante pentru a verifica daca exista drum direct intre ele:\n");
    scanf("%d%d", &source, &destination);

    
    if (has_direct_edge(graph, source - 1, destination - 1)) 
    {
        printf("Exista drum direct intre restaurantul %d si restaurantul %d\n", source, destination);
    } 
    else if (next_DFS(graph, stack1, source - 1, destination - 1))
    {
        printf("Nu exista drum direct intre restaurantul %d si restaurantul %d\n ,dar exista un drum ce se compune", source, destination);
    }
    else
    {
        printf("Nu exista drum direct intre restaurantul %d si restaurantul %d\n", source, destination);
    }

    return 0;
}
