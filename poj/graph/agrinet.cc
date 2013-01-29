/*
 * poj 1258
 * memory: 428K
 * time: 16MS
 * complier: G++
 * codelength: 2964B
 * date: 2012-11-03 19:05:15
 * ps: 套用1789的代码 1A
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_N = 105;
const int MAX_EDGE_N = MAX_N * MAX_N;
const int MAX_HEAP_SIZE = MAX_EDGE_N;

int edges[MAX_N][MAX_N];

int prev[MAX_N];
int cost[MAX_N];
int flag[MAX_N];

//小顶堆
int heap[MAX_N];
int xposa[MAX_N];
int heapsize;

void decreasekey(int x);
void insert(int x);
int deletemin();
void makeheap(int n);
int key(int i);
void shiftdown(int x, int i);
void bubbleup(int x, int i);
int minchild(int i);
int& xpos(int x);

int main(int argc, const char *argv[])
{
    int n;
    while (scanf("%d",&n) == 1){

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j){
                scanf("%d", &edges[i][j]);
            }
        }

        for(int i = 0; i < n; ++i){
            cost[i] = 1<<27;
        }
        memset(flag, 0, sizeof(flag));
        cost[0] = 0;

        makeheap(n);

        int sum = 0;
        while( heapsize != 0){
            int x = deletemin();
            flag[x] = 1;
            sum += cost[x];

            for(int j = 0; j < n; ++j){
                if( !flag[j] && cost[j] > edges[x][j] ){
                    cost[j] = edges[x][j];
                    prev[j] = x;
                    decreasekey(j);
                }
            }
        }

        printf("%d\n",sum);
    }

    return 0;
}

int& xpos(int x)
{
    return xposa[x];
}

int key(int i)
{
    return cost[i];
}

//元素不应改为负数
void insert(int x)
{
    heapsize += 1;
    xpos(x) = heapsize - 1;
    bubbleup(x, heapsize - 1);
}

//减小了权值，更新优先级队列
void decreasekey(int x)
{
    bubbleup(x, xpos(x));
}

//元素不应改为负数
int deletemin()
{
    int x = -1;
    if( heapsize != 0){
        x = heap[0];
        heap[0] = heap[heapsize - 1];
        xpos(heap[0]) = 0;
        --heapsize;
        shiftdown(heap[0], 0);
    }
    return x;
}
void makeheap(int n)
{
    heapsize = n;
    for (int i = 0; i < n; ++i){
        heap[i] = i;
        xpos(i) = i;
    }

    for (int i = n -1; i > -1; --i){
        shiftdown(heap[i],i);
    }
}

void bubbleup(int x, int i)
{
    int p = (i - 1)/2;
    while (i != 0 && key(heap[p]) > key(x)){
        heap[i] = heap[p];
        xpos(heap[p]) = i;
        i = p;
        p = (i -1)/2;
    }
    heap[i] = x;
    xpos(x) = i;
}

void shiftdown(int x, int i)
{
    int c = minchild(i);
    while (c != -1 && key(heap[c]) < key(x)) {
        heap[i] = heap[c];
        xpos(heap[c]) = i;
        i = c;
        c = minchild(i);
    }
    heap[i] = x;
    xpos(x) = i;
}

int minchild(int i)
{
    int leftchild = 2 * i + 1;
    int rightchild = 2 * i + 2;

    if ( leftchild > heapsize -1 )
        return -1;
    else if ( rightchild > heapsize -1) {
        return leftchild;
    } else {
        return key(heap[leftchild]) < key(heap[rightchild]) ? leftchild : rightchild;
    }
}
