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
	
	FILE *relatorio = fopen("relatório.txt", "w");
	
	fprintf(relatorio, "Contagem de declarações de variável global\n");
	fprintf(relatorio, "int: %d\n", (op->getGlobalCount()).countInt);
	fprintf(relatorio, "float: %d\n", (op->getGlobalCount()).countFloat);
	fprintf(relatorio, "double: %d\n", (op->getGlobalCount()).countDouble);

	fprintf(relatorio, "Contagem de declarações de funçoes\n");
	fprintf(relatorio, "int: %d\n", (op->getGlobalCountFunc()).countInt);
	fprintf(relatorio, "float: %d\n", (op->getGlobalCountFunc()).countFloat);
	fprintf(relatorio, "double: %d\n", (op->getGlobalCountFunc()).countDouble);
	fprintf(relatorio, "void: %d\n", (op->getGlobalCountFunc()).countVoid);

	fprintf(relatorio, "Número de Whiles\n");
	fprintf(relatorio, "While:%d\n", op->getCountL());	

	fclose(relatorio);

	return 0;
}
