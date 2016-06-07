#include "classes_gringo.hpp"

//If
Exp *If::getExp(){
	return this->exp;
}

ExpList *If::getExpList(){
	return this->expList;
}

//IfElse
Exp *IfElse::getExp(){
	return this->exp;
}

ExpList *IfElse::getExpList(){
	return this->expList;
}

ExpList *IfElse::getExpList_2(){
	return this->expList_2;
}

//While
Exp *While::getExp(){
	return this->exp;
}

ExpList *While::getExpList(){
	return this->expList;
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
char *IdValue::getValue(){ 
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