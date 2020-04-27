#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#define STACK_SIZE 10000
#define cycles 1000

void print(const char *text)
{
    int i;
    for (i=0;i<20;i++){
         printf("hello from %s\n",text);
         usleep(1000000);
    }
}

//fork task

void mainFork()
{
     
      //create child
      pid_t pid =fork();

      if ( pid == 0){
            //we are in child
            
            //create a grand child 
             pid_t pid =fork();
             
            if ( pid == 0){
                    //we are in grand child
                    //print("grand child");
            
                    char * args[2]= {"./friend",NULL};
                    execvp(args[0],args);
            }
            else{
                    print("child");
            }
     }
     else{ 
           print("parent");
     }
     
}


//clone task

char child_stack[STACK_SIZE+1];

int child(void *params)
{
     print("CHILD_THREAD");
}


void mainClone()
{

      //int result = clone(child,child_stack+STACK_SIZE,0,0);
      int result = clone(child,child_stack+STACK_SIZE,CLONE_PARENT,0);
      printf("clone result = %d\n",result);

      print("PARENT");

}


//Daemon task

void mainDaemon()
{
    //create daemon child
    pid_t pid =fork();
    
    if (pid ==0)
    {
       //here is the child
       
       //change the current working directory to root directory 
       chdir("/");
       
       //move the child to another session, so the parent may be closed
       setsid();
     
       printf("DAEMON STARTS\n");
     
       //close output chanels
       close(stdout);
       close(stdin);
       close(stderr);

       //open log
       openlog("my_Daemon", LOG_PID , LOG_DAEMON);
       syslog(LOG_NOTICE, "demon started");
       usleep(3000000);
       syslog(LOG_NOTICE, "doing something ..");
       usleep(3000000);
       syslog(LOG_NOTICE, "demon ended .");
   
    }
    else 
    {
       printf("DAEMON PID %d\n", pid); 
    }

}
       


int main()
{

   mainFork();
   mainClone();
   mainDaemon();
    
    return 0;

}
