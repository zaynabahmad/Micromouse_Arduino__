/**
 * @file queue_linkedlist.c
 * @author zaynap (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include <stddef.h>

#include "queue.h"




/**
 * Initializes the queue by setting its front and rear pointers and size to default values.
 *
 * @param pq pointer to the queue
 */
void CreateQueue(Queue *pq){
    pq->front=NULL;
    pq->rear=NULL;
    pq->size=0;

}

/**
 * Appends an element to the rear of the queue.
 *
 * @param e the element to be appended
 * @param pq pointer to the queue
 * @return 1 if the element is successfully appended, 0 otherwise
 */
int Append(QueueEntry e , Queue * pq){
    QueueNode *pn = (QueueNode *)malloc(sizeof( QueueNode));
    if (!pn)
        return 0;
    else {
    pn->next=NULL;
    pn->entry=e;
    if(!pq->rear)
      pq->front=pn;
      else
      {
        pq->rear->next =pn;
      }
      pq->rear=pn;
      pq->size++;
      return 1;
    }

}

/**
 * Removes the front element from the queue and assigns it to the given variable.
 *
 * @param pe pointer to the variable that will hold the removed element
 * @param pq pointer to the queue
 */
void serve (QueueEntry *pe, Queue * pq){
    QueueNode * pn = pq->front;
    *pe =pn->entry ;
    pq->front=pn->next;
    free(pn);
    if(!pq->front)
    pq->rear=NULL;
    pq->size--;


}

/**
 * Determines if the queue is empty.
 *
 * @param pq pointer to the queue
 * @return 1 if the queue is empty, 0 otherwise
 */
int QueueEmpty(Queue* pq){
    return !pq->front;
}

/**
 * Determines the size of the queue.
 *
 * @param pq pointer to the queue
 * @return the size of the queue
 */
int QueueSize(Queue* pq){
    return pq->size;
}

/**
 * Determines if the queue is full. For linked list implementation, the queue can never be full.
 *
 * @param pq pointer to the queue
 * @return always returns 0
 */
int QueueFull (Queue *pq){
    return 0;
}

/**
 * Removes all elements from the queue.
 *
 * @param pq pointer to the queue
 * @return 1 if the queue is successfully cleared, 0 otherwise
 */
int ClearQueue (Queue *pq){    //again
    while (pq->front){
        pq->rear =pq->front->next;
        free(pq->front);
        pq->front=pq->rear;
    }
    pq->size =0;
    // Return 1 to indicate success
    return 1;
}

/**
 * Traverses the queue, applying the given function to each element.
 *
 * @param pq pointer to the queue
 * @param pf pointer to the function that will be applied to each element
 */
void TraverseQueue(Queue *pq ,void (*pf)(QueueEntry)){
    for (QueueNode * pn =pq->front ; pn ; pn=pn->next){
        (*pf)(pn->entry);
    }
}