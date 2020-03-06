#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

//static char input[2048];

int main(int argc, char** argv){
  printf("Lispy Version 0.0.0.0.1\n");
  printf("This version of Lisp Interpreter is implemented by Burak Gunay and Sarp Uner\n");
  printf("Press Ctrl+c to Exit\n");

  while (1){
    char * input = readline("Lisp interpreter> ");

    add_history(input);

    printf("No you %s\n", input);

    free(input);
  }
  printf("Exiting\n");
  return 0;
}
