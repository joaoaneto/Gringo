#include <stdio.h>
#include "visitor.hpp"

extern int yyparse();
extern FILE *yyin;

int main(int argc, char ** argv){

	yyin = fopen (argv[1],"r"); /*Arquivo de entrada */
	
	if(argc != 2){ printf("Tem que ter o nome do arquivo\n\n"); return 1; }

	if(yyparse()){ printf("Erro no parser\n"); return 1; }

	Operations *op = new Operations();
	Program *prg = Context::getContext().getProgram();

	prg->accept(op);
	
	return 0;
}