/**
 * @file queue.h
 * @author zaynap (you@domain.com)
 * @brief 
 * @version 0.2
 * @date 2023-07-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include "config.h"

// Define the POINT structure and required functions
   #define QueueEntry POINT

    typedef struct queueNode {
        QueueEntry entry;
        struct queueNode *next;
    } QueueNode;

    typedef struct queue {
        QueueNode *front;
        QueueNode *rear;
        int size;
    } Queue;

    void CreateQueue(Queue *pq);
    int Append(QueueEntry e, Queue *pq);
    void serve(QueueEntry *pe, Queue *pq);
    int QueueEmpty(Queue *pq);
    int QueueFull(Queue *pq);
    int QueueSize(Queue *pq);
    int ClearQueue(Queue *pq);
    void TraverseQueue(Queue *pq, void (*pf)(QueueEntry));






#endif 

