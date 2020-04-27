#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main()
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

    return 0;
}
       
