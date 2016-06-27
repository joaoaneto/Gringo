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

	fprintf(relatorio, "Contagem de definições de funçoes\n");
	fprintf(relatorio, "int: %d\n", (op->getGlobalCountFunc()).countInt);
	fprintf(relatorio, "float: %d\n", (op->getGlobalCountFunc()).countFloat);
	fprintf(relatorio, "double: %d\n", (op->getGlobalCountFunc()).countDouble);
	fprintf(relatorio, "void: %d\n", (op->getGlobalCountFunc()).countVoid);

	fprintf(relatorio, "Número de Whiles: %d\n",op->getCountL());	

	fprintf(relatorio, "Número de If's: %d\n",op->getCountIf());	

	fprintf(relatorio, "Número de IfElse's: %d\n",op->getCountIfElse());	

	fprintf(relatorio, "Número de chamadas de funções : %d\n",op->getCountCall());	

	fprintf(relatorio, "Número de declarações de variáveis em cada função\n");
	for(int i =0; i<Context::getContext().getVector().size(); i++){
		string xablau = Context::getContext().getVector()[i];
		int oudre = op->getStack()[i];
		fprintf(relatorio, " %d\n", oudre);
	}

	fclose(relatorio);

	return 0;
}
