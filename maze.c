// Brian Villar
// 3/26/16
// Maze Assignment
/* Strategy: Have a struct to store the (x,y) of the row and column
   Enque starting point, then when playing the game deque and Enque
   all points that are not visited in a clockwise manner. Rinse, Repeat.
*/

#include <stdio.h>
#include <stdlib.h>

//struct to house ordered pair
struct ordPair
{
    int x; //p for row
    int y; //p for col
};

//struct for each node of the queue
//each node will have a struct with the ordered pair. Struct inside of struct
struct node
{
    struct ordPair * point;
    struct node * next;
};

//the queue template
struct queue
{
    struct node * front; //to remove from
    struct node * rear; //to add to
};

//prototypes
void loadGame();
void runGame(struct queue * q, char board[][300], int steps[][300], int row, int col);
struct queue * initialize(); //initialize the queue
struct node * newNode(struct ordPair * point); //make new nodes for the queue
void enqueue(struct queue * q, struct ordPair *point); //add to back
struct node * dequeue(struct queue * q);

int main()
{
    int i, numGames;

    scanf("%d", &numGames);

    for(i=0; i<numGames; i++)
        loadGame();

    return 0;
}

void loadGame()
{
    int i, j, row, col;
    char board[300][300]; //contains the board
    int steps[300][300]; // keeps track of steps taken
    struct queue * q = initialize(); //make and initialize the queue

    scanf("%d %d", &row, &col);

    for (i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            scanf(" %c", &board[i][j]); //space in the front  for correct board format
            if(board[i][j] != 'S') //not starting point
            steps[i][j] = -1; //mark it as unvisited

            else //it's the starting position
            {
                steps[i][j] = 0;  //the distance from the starting point to itself is 0
                struct ordPair * p = malloc(sizeof( struct ordPair));
                p->x = i;
                p->y = j;
                enqueue(q,p); //enqueue the starting position
            }
        }
    }

    runGame(q, board, steps, row, col);

}

void runGame(struct queue * q, char board[][300], int steps[][300], int row, int col)
{
    struct node * runs;
    int x, y;

    while((runs = dequeue(q)) != NULL) //run until queue is empty if necessary
    {
        x = runs->point->x;
        y = runs->point->y;
       // printf("here %d %d\n", x, y); //making sure visiting right points in right order

        //we're at a corner or somewhere in the outer edge
       if(x==0 || x==row-1 || y==0 || y==col-1)
        {
            printf("%d\n", steps[x][y]);
            break;
        }

        //We can move up (no X on the board) and
        //and we havent visited steps = -1
        if(board[x-1][y] != 'X' && steps[x-1][y] == -1)
        {
            struct ordPair * p = malloc(sizeof(struct ordPair)); //node for x,y
            p->x = x-1; // x-coordinate of that spot
            p->y = y; // y -coordinate of that spot
            enqueue(q,p); //add it to the queue
            steps[x-1][y] = steps[x][y] + 1; //distance +1 from neighboring x,y
        }
        //we can move right and same logic
        if(board[x][y+1] != 'X' && steps[x][y+1] == -1)
        {
            struct ordPair *p = malloc(sizeof(struct ordPair));
            p->x = x;
            p->y = y+1;
            enqueue(q,p);
            steps[x][y+1] = steps[x][y] + 1;
        }
        //we can move down and same logic
        if(board[x+1][y] != 'X' && steps[x+1][y] == -1)
        {
            struct ordPair *p = malloc(sizeof(struct ordPair));
            p->x = x+1;
            p->y = y;
            enqueue(q,p);
            steps[x+1][y] = steps[x][y] + 1;
        }
        //we can move left and same distance
        if(board[x][y-1] != 'X' && steps[x][y-1] == -1)
        {
            struct ordPair *p = malloc(sizeof(struct ordPair));
            p->x = x;
            p->y = y-1;
            enqueue(q,p);
            steps[x][y-1] = steps[x][y] + 1;
        }

    }
       if(runs == NULL)
        {
            if(x == 0 || y == 0 || x == row - 1 || y == col - 1)
                printf("%d\n", steps[x][y]);
            else
                printf("-1\n");

        }

}

struct queue * initialize()
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

struct node * dequeue(struct queue * q)
{
    //empty queue starting
    if(q->front == NULL)
        return NULL;

    struct node * temp = q->front; //temp = 1st item
    q->front = q->front->next;

    //empty once last one is gone
    if(q->front == NULL)
        q->rear = NULL;

    return temp; //return first item
}

void enqueue(struct queue * q, struct ordPair * p)
{
    struct node * temp = newNode(p); //makes new node with ordered pair

    //queue is empty
    if(q->rear == NULL)
    {
        q->front = temp;
        q->rear = temp;
        return;
    }

    //not empty
    q->rear->next = temp;
    q->rear = temp;
}

struct node * newNode(struct ordPair * p)
{
    struct node * temp = malloc(sizeof(struct node));
    temp->point = p;
    temp->next = NULL;
    return temp;
}
