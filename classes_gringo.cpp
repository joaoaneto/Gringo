#include "classes_gringo.hpp"

//VarDeclarationsSimple
int VarDeclarationsSimple::getType(){
	return this->type;
}

IdValue *VarDeclarationsSimple::getIdValue(){
	return this->idValue;
}

//VarDeclarationsInit

int VarDeclarationsInit::getType(){
	return this->type;
}

Assignment *VarDeclarationsInit::getAssigment(){
	return this->assignment;
}

//FunctionDefinition

int FunctionDefinition::getType(){
	return this->type;
}

IdValue *FunctionDefinition::getIdValue(){
	return this->idValue; 
}

Block *FunctionDefinition::getBlock(){
	return this->block; 
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

//Block

Block *VarDeclarationsList::getVarDecList(){
	return this->varDecList;
}

Block *Commands::getCommands(){
	return this->commands;
}

//BinExpPlus
Exp *BinExpPlus::getExp (){
	return this->exp;
}

Factor *BinExpPlus::getFactor(){
	return this->factor;
}

//BinExpMinus
Exp *BinExpMinus::getExp (){
	return this->exp; 
}

Factor *BinExpMinus::getFactor(){ 
	return this->factor; 
}

Exp *BinExpLessThen::getExp(){
	return this->exp;
}

Factor *BinExpLessThen::getFactor(){
	return this->factor;
}

Exp *BinExpLessEqualThen::getExp(){
	return this->exp;
}

Factor *BinExpLessEqualThen::getFactor(){
	return this->factor;
}

Exp *BinExpGreaterThen::getExp(){
	return this->exp;
}

Factor *BinExpGreaterThen::getFactor(){
	return this->factor;
}

Exp *BinExpGreaterEqualThen::getExp(){
	return this->exp;
}

Factor *BinExpGreaterEqualThen::getFactor(){
	return this->factor;
}

Exp *BinExpEqual::getExp(){
	return this->exp;
}

Factor *BinExpEqual::getFactor(){
	return this->factor;
}

Exp *BinExpDiff::getExp(){
	return this->exp;
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

//Context
Context &Context::getContext(){
		if (instance == NULL){ 
			instance = new Context(); 
		}
		return *instance;
}

Context::TypeTable &Context::getTable(){ 
	return this->table; 
}

void Context::setProgram(Program *prog){ 
	program = prog; 
}

Program *Context::getProgram(){
	return this->program;
}

Context *Context::instance = NULL;