#include "classes_gringo.hpp"

//Parameter
IdValue *Parameter::getIdValue(){
	return this->idValue;
}

int Parameter::getType(){
	return this->type;
}

//Parameters
ParameterList *Parameters::getParameterList(){
	return this->paramlist;
}

Parameter *Parameters::getParameter(){
	return this->param;
}

//VarDeclarations
VarDeclarationList *VarDeclarations::getVarDeclarationList(){
	return this->vardeclarationlist;
}

VarDeclaration *VarDeclarations::getVarDeclaration(){
	return this->vardeclaration;
}

//VarDeclaration
int VarDeclaration::getType(){
	return this->type;
}

NameList *VarDeclaration::getNameList(){
	return this->nameList;
}

//Names
NameList *Names::getNameList(){
	return this->namelist;
}

Name *Names::getName(){
	return this->name;
}

//NameID 
IdValue *NameID::getIdValue(){
	return this->idValue;
}

//NameAssignment
Assignment *NameAssignment::getAssignment(){
	return this->assignment;
}

//FunctionPar
int FunctionPar::getType(){
	return this->type;
}

IdFunction *FunctionPar::getIdFunction(){
	return this->idFunction; 
}

Block *FunctionPar::getBlock(){
	return this->block; 
}

//FunctionNonPar 
int FunctionNonPar::getType(){
	return this->type;
}

IdFunction *FunctionNonPar::getIdFunction(){
	return this->idFunction; 
}

Block *FunctionNonPar::getBlock(){
	return this->block; 
}

//IdFunction
string IdFunction::getIdFunction(){ 
	return this->idFunction; 
}

//FunctionCall
IdFunction *FunctionCall::getIdFunction(){
	return this->idFunction;
}

//FuncDefinitions
FuncDefinitionList *FuncDefinitions::getFuncDefinitionList(){
	return this->funcdefinitionlist; 
}

FuncDefinition *FuncDefinitions::getFuncDefinition(){
	return this->funcdefinition; 
}

//CommandsList
Commands *CommandsList::getCommands(){
	return this->commands;
}

Command *CommandsList::getCommand(){
	return this->command;
}

//If
Exp *If::getExp(){
	return this->exp;
}

Block *If::getBlock(){
	return this->block;
}

//IfElse
Exp *IfElse::getExp(){
	return this->exp;
}

Block *IfElse::getBlock1(){
	return this->block1;
}

Block *IfElse::getBlock2(){
	return this->block2;
}

//While
Exp *While::getExp(){
	return this->exp;
}

Block *While::getBlock(){
	return this->block;
}

//BlockVarCommands
VarDeclarationList *BlockVarCommands::getVarDecList(){
	return this->varDecList;
}

Commands *BlockVarCommands::getCommands(){
	return this->commands;
}

//BlockCommands
Commands *BlockCommands::getCommands(){
	return this->commands;
}

//BlockVar
VarDeclarationList *BlockVar::getVarDecList(){
	return this->varDecList;
}

//BinExpPlus
LValue *BinExpPlus::getLValue (){
	return this->lValue;
}

Factor *BinExpPlus::getFactor(){
	return this->factor;
}

//BinExpMinus
LValue *BinExpMinus::getLValue (){
	return this->lValue; 
}

Factor *BinExpMinus::getFactor(){ 
	return this->factor; 
}

//BinExpLessThen
LValue *BinExpLessThen::getLValue(){
	return this->lValue;
}

Factor *BinExpLessThen::getFactor(){
	return this->factor;
}

//BinExpLessEqualThen
LValue *BinExpLessEqualThen::getLValue(){
	return this->lValue;
}

Factor *BinExpLessEqualThen::getFactor(){
	return this->factor;
}

//BinExpGreaterThen
LValue *BinExpGreaterThen::getLValue(){
	return this->lValue;
}

Factor *BinExpGreaterThen::getFactor(){
	return this->factor;
}

//BinExpGreaterEqualThen
LValue *BinExpGreaterEqualThen::getLValue(){
	return this->lValue;
}

Factor *BinExpGreaterEqualThen::getFactor(){
	return this->factor;
}

//BinExpEqual
LValue *BinExpEqual::getLValue(){
	return this->lValue;
}

Factor *BinExpEqual::getFactor(){
	return this->factor;
}

//BinExpDiff
LValue *BinExpDiff::getLValue(){
	return this->lValue;
}

Factor *BinExpDiff::getFactor(){
	return this->factor;
}

//FactorMul
Factor *FactorMul::getFactor(){ 
	return this->factor; 
}

UnExp *FactorMul::getUnExp(){ 
	return this->unExp; 
}

//FactorDiv
Factor *FactorDiv::getFactor(){ 
	return this->factor; 
}

UnExp *FactorDiv::getUnExp(){	
	return this->unExp; 
}

//UnExpPlus
Value *UnExpPlus::getValue(){ 
	return this->value;
}

//UnExpMinus
Value *UnExpMinus::getValue(){ 
	return this->value;
}

//UnExpLog
Exp *UnExpLog::getExp(){
	return this->exp; 
}

//UnExpExp
Exp *UnExpExp::getExp(){ 
	return this->exp; 
}

//IntValue
int IntValue::getValue(){
	return this->value; 
}

Value::Type IntValue::getType(){ 
	return INT; 
}

//DoubleValue
double DoubleValue::getValue(){ 
	return this->value; 
}

Value::Type DoubleValue::getType(){ 
	return DOUBLE; 
}

//IdValue
string IdValue::getValue(){ 
	return this->idValue; 
}

Value::Type IdValue::getType(){ 
	return ID_VALUE; 
}

//LparExpRpar
Exp *LparExpRpar::getExp(){ 
	return this->exp; 
}

//Assignment
Exp *Assignment::getExp(){ 
	return this->exp; 
}

IdValue	*Assignment::getIdValue(){ 
	return this->idValue; 
}

//Scope
Scope::TypeTable &Scope::getTable(){ 
	return this->table; 
}

Scope *Scope::getFather(){
	return this->father_; 
}

Scope::Scope(){
	father_ = Context::getContext().getAtualScope();
}

Scope::~Scope(){
	Context::getContext().setAtualScope(father_);
}

//Context
Context &Context::getContext(){
	if (instance == NULL){ 
		instance = new Context(); 
	}
	return *instance;
}

void Context::setAtualScope(Scope *chupa_sandy){
	atual_ = chupa_sandy;
}

Scope *Context::getAtualScope(){

	return atual_;
}

void Context::setProgram(Program *prog){ 
	program = prog;
}

Program *Context::getProgram(){
	return this->program;
}

vector<string> &Context::getVector(){
	return this->stackFunc_;
}

Context *Context::instance = NULL;