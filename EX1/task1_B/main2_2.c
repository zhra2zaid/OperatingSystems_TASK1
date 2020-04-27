#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10000
#define cycles 1000

char child_stack[STACK_SIZE+1];

void print(const char *text)
{
    int i;
    for (i=0;i<20;i++){
         printf("hello from %s\n",text);
         usleep(1000000);
    }
}

int child(void *params)
{
     print("CHILD_THREAD");
}


int main()
{

      //int result = clone(child,child_stack+STACK_SIZE,0,0);
      int result = clone(child,child_stack+STACK_SIZE,CLONE_PARENT,0);
      printf("clone result = %d\n",result);

      print("PARENT");

      return 0;
}


