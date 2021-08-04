#ifndef _TASK_H
#define _TASK_H

typedef struct Task
{
    void(* func) (void * arg);
    void * arg;
}Task;

#endif