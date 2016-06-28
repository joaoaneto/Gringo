#include <stdio.h>
#include <iostream>
#include <fstream>
#include "visitor.hpp"

using namespace std;

extern int yyparse();
extern FILE *yyin;

int main(int argc, char ** argv){

	yyin = fopen (argv[1],"r"); /*Arquivo de entrada */
	
	if(argc != 2){ printf("Tem que ter o nome do arquivo\n\n"); return 1; }

	if(yyparse()){ printf("Erro no parser\n"); return 1; }

	Operations *op = new Operations();
	Program *prg = Context::getContext().getProgram();

	prg->accept(op);
	
	ofstream relatorio;
	relatorio.open("relatório.txt");
	relatorio << "Contagem de declarações de variável global\n";
	relatorio << "int: " << (op->getGlobalCount()).countInt << "\n";
	relatorio << "float: " << (op->getGlobalCount()).countFloat << "\n";
	relatorio << "double: " << (op->getGlobalCount()).countDouble << "\n\n";
	relatorio << "Contagem de definições de funçoes\n";
	relatorio << "int: " << (op->getGlobalCountFunc()).countInt << "\n";
	relatorio << "float: " << (op->getGlobalCountFunc()).countFloat << "\n";
	relatorio << "double: " << (op->getGlobalCountFunc()).countDouble << "\n";
	relatorio << "void: " << (op->getGlobalCountFunc()).countVoid << "\n\n";
	relatorio << "Número de Whiles: " << op->getCountL() << "\n";
	relatorio << "Número de If's: " << op->getCountIf() << "\n";
	relatorio << "Número de IfElse's: " << op->getCountIfElse() << "\n";	
	relatorio << "Número de chamadas de funções: " << op->getCountCall() << "\n\n";
	relatorio << "Número de declarações de variáveis em cada função\n";
	
	int i;
	for(i=0; i<Context::getContext().getVector().size(); i++){
		string xablau = Context::getContext().getVector()[i];
		int oudre = op->getStack()[i];
		relatorio << xablau << ": " << oudre << "\n";
	}

	relatorio.close();
	
	return 0;
}
