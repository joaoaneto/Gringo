#ifndef CLASSES_GRINGO_HPP
#define CLASSES_GRINGO_HPP

#include <map>
#include <string>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <vector>

using std::vector;
using namespace std;

class Node {
public:
	virtual void accept(class Visitor *) = 0;
};

class Program : public Node {};

class ExpList : public Program {};

class Command : public ExpList {};

class Exp : public Command {};

class Factor: public Exp {};

class UnExp: public Factor {};

class Value : public UnExp {
public:
	enum Type {
		INT,
		DOUBLE,
		ID_VALUE
	};
	
	virtual Type getType() = 0;		 
private:
	Type type;
};

class Commands: public ExpList {
private:
	ExpList *expList;
	Command *command;
public:
	Commands(ExpList *el, Command *c): expList(el), command(c){} //construtor
	ExpList *getExpList(){ return this->expList; }
	Command *getCommand(){ return this->command; }
	//void accept(Visitor *);
};

class BinExpPlus: public Exp {
private:
	Exp *exp;
	Factor *factor;

public:
	BinExpPlus(Exp *e, class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp (){ return this->exp; }
	Factor *getFactor(){ return this->factor; }
	void accept(Visitor *);
};

class BinExpMinus: public Exp {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpMinus(Exp *e,  class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp (){ return this->exp; }
	Factor *getFactor(){ return this->factor; }
	void accept(Visitor *);
};

class FactorMul: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorMul(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor(){ return this->factor; }
	UnExp *getUnExp(){ return this->unExp; }
	void accept(Visitor *);
};

class FactorDiv: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorDiv(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor(){ return this->factor; }
	UnExp *getUnExp(){	return this->unExp; }
	void accept(Visitor *);
};

class UnExpPlus : public UnExp {
private:	
	Value *value;
public:
	UnExpPlus(Value *v): value(v){} //construtor
	Value *getValue(){ return this->value; }
	void accept(Visitor *);
};

class UnExpMinus : public UnExp {
private:
	Value *value;
public:
	UnExpMinus(Value *v): value(v){} //construtor
	Value *getValue(){ return this->value; }
	void accept(Visitor *);
};

class UnExpLog : public UnExp {
private:
	Exp *exp;
public:
	UnExpLog(Exp *e): exp(e){} //construtor
	Exp *getExp(){ return this->exp; }
	void accept(Visitor *);
};

class UnExpExp: public UnExp {
private:
	Exp *exp;
public:
	UnExpExp(Exp *e): exp(e){} //construtor
	Exp *getExp(){ return this->exp; }
	void accept(Visitor *);
};

class IntValue: public Value {
private:
	int value;
public:
	IntValue(int value):value(value){} //construtor
	int getValue(){ return this->value; }
	virtual Type getType(){ return INT; }
	void accept(Visitor *);
};

class DoubleValue: public Value {
private:
	double value;
public:
	DoubleValue(double value):value(value){} //construtor
	double getValue(){ return this->value; }
	virtual Type getType(){ return DOUBLE; }
	void accept(Visitor *v);
};


class IdValue: public Value {
private:
	char *idValue;
public:
	IdValue(char *idvalue){ idValue = strdup(idvalue); } //construtor
	char *getValue(){ return this->idValue; }
	virtual Type getType(){ return ID_VALUE; }
	void accept(Visitor *);
};

class LparExpRpar : public Value {
private:
	Exp *exp;
public:
	LparExpRpar(Exp *e) : exp(e){} //construtor
	Exp *getExp(){ return this->exp; }
	//void accept(Visitor *);
};

class Assignment : public Command {
private:
	Exp *exp;
	IdValue *idValue;
public:
	Assignment(IdValue *id, Exp *e) : idValue(id), exp(e){} //construtor
	Exp *getExp(){ return this->exp; }
	IdValue	*getIdValue(){ return this->idValue; }
	void accept(Visitor *);
}; 


class Context {
private:
	static Context *instance;
	static Program *program;
	Context(){} //construtor	
public:
	typedef map<string, Value *> TypeTable;
	static Context &getContext() {
		if (instance == NULL){ instance = new Context(); }
		return *instance;
	}
	
	TypeTable &getTable(){ return this->table; }
	void setProgram(Program *prog){ program = prog; }
private:
	TypeTable table;	
};

Context *Context::instance = NULL;

#endif
