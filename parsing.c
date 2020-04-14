#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char *cpy = malloc(strlen(buffer) + 1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy) - 1] = '\0';
	return cpy;

}

void add_history(char *unused) {
}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

//static char input[2048];

int main(int argc, char **argv) {
	mpc_parser_t *Number = mpc_new("number");
	mpc_parser_t *Decimal = mpc_new("decimal");
	mpc_parser_t *Operator = mpc_new("operator");
	mpc_parser_t *Expr = mpc_new("expr");
	mpc_parser_t *Lispy = mpc_new("lispy");

	/* Define them with the following Language */
	mpca_lang(MPCA_LANG_DEFAULT,
		  "                                                     \
	    number   : /-?[0-9]+/ ;                             \
	    decimal   : /-?[0-9]+\\.[0-9]+/ ;                             \
	    operator : '+' | '-' | '*' | '/' | '%' ;                  \
	    expr     :  <decimal> | <number> | '(' <operator> <expr>+ ')' ;  \
	    lispy    : /^/ <operator> <expr>+ /$/ ;             \
	  ", Number, Decimal, Operator, Expr, Lispy);



	printf("Lispy Version 0.0.0.0.1\n");
	printf
	    ("This version of Lisp Interpreter is implemented by Burak Gunay and Sarp Uner\n");
	printf("Press Ctrl+c to Exit\n");

	while (1) {
		char *input = readline("Lisp interpreter> ");

		add_history(input);
		/* Attempt to Parse the user Input */
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			/* On Success Print the AST */
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			/* Otherwise Print the Error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		free(input);
	}
	printf("Exiting\n");

	/* Undefine and Delete our Parsers */
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	return 0;
}
