#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define STACK_SIZE 65536

int child_func() {
   int* x = 0;
   printf("\nThis is process (thread) %d.\n", getpid());
   **x = 7;
   return 0;
}
  
		
int main () 
{
   char *stack;
   char *stackTop;
   int x = 0, y = 0;
   pid_t pid;
   
   stack = malloc(STACK_SIZE);
   if (stack == NULL){
      perror("malloc"); exit(1);
   }
   stackTop = stack + STACK_SIZE;   

   pid  = clone(child_func, stackTop, CLONE_VM|CLONE_FILES, NULL);
   if(pid == -1) {perror("clone"); exit(0); }

   if (pid > 0) {
       printf ("\nThis is process (thread) %d.\n", pid);
       y = 1;
   }
   else if (pid == 0){
       sleep(1);
       printf ("\nThis is process(thread) %d. \n", pid);
       x = 7;
   }
   else {
       printf ("fork failed\n");
       return (1);
   }
   printf("x+y=%d\n", x + y);
}
