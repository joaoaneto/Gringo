#ifndef CLASSES_GRINGO_HPP
#define CLASSES_GRINGO_HPP

#include <map>
#include <string.h>

using namespace std;

class Node {
public:
	virtual void accept(class Visitor *) = 0;
};

class Program : public Node {};

class ExpList : public Program {};

class Command : public ExpList {};

class IfElseIf : public Command{};

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

class If: public IfElseIf{
private:
	Exp *exp;
	ExpList *expList;
public:
	If(Exp *e, ExpList *eList): exp(e), expList(eList){}
	Exp *getExp();
	ExpList *getExpList();
	void accept(Visitor *);
};

class Else: public IfElseIf{
private:
	ExpList *expList;
public:
	Else(ExpList *eList): expList(eList){}
	ExpList *getListExp();
	void accept(Visitor *);
};

class BinExpPlus: public Exp {
private:
	Exp *exp;
	Factor *factor;

public:
	BinExpPlus(Exp *e, class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *);
};

class BinExpMinus: public Exp {
private:
	Exp *exp;
	Factor *factor;
public:
	BinExpMinus(Exp *e,  class Factor *f): exp(e), factor(f){} //construtor
	Exp *getExp ();
	Factor *getFactor();
	void accept(Visitor *);
};

class FactorMul: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorMul(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor();
	UnExp *getUnExp();
	void accept(Visitor *);
};

class FactorDiv: public Factor {
private:
	Factor *factor;
	UnExp *unExp;
public:
	FactorDiv(Factor *f, UnExp *ue): factor(f), unExp(ue){} //construtor
	Factor *getFactor();
	UnExp *getUnExp();
	void accept(Visitor *);
};

class UnExpPlus : public UnExp {
private:	
	Value *value;
public:
	UnExpPlus(Value *v): value(v){} //construtor
	Value *getValue();
	void accept(Visitor *);
};

class UnExpMinus : public UnExp {
private:
	Value *value;
public:
	UnExpMinus(Value *v): value(v){} //construtor
	Value *getValue();
	void accept(Visitor *);
};

class UnExpLog : public UnExp {
private:
	Exp *exp;
public:
	UnExpLog(Exp *e): exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class UnExpExp: public UnExp {
private:
	Exp *exp;
public:
	UnExpExp(Exp *e): exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class IntValue: public Value {
private:
	int value;
public:
	IntValue(int value):value(value){} //construtor
	int getValue();
	virtual Type getType();
	void accept(Visitor *);
};

class DoubleValue: public Value {
private:
	double value;
public:
	DoubleValue(double value):value(value){} //construtor
	double getValue();
	virtual Type getType();
	void accept(Visitor *v);
};


class IdValue: public Value {
private:
	char *idValue;
public:
	IdValue(char *idvalue){ idValue = strdup(idvalue); } //construtor
	char *getValue();
	virtual Type getType();
	void accept(Visitor *);
};

class LparExpRpar : public UnExp {
private:
	Exp *exp;
public:
	LparExpRpar(Exp *e) : exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class Assignment : public Command {
private:
	Exp *exp;
	IdValue *idValue;
public:
	Assignment(IdValue *id, Exp *e) : idValue(id), exp(e){} //construtor
	Exp *getExp();
	IdValue	*getIdValue();
	void accept(Visitor *);
}; 


class Context {
private:
	static Context *instance;
	Program *program;
	Context(){} //construtor	
public:
	typedef map<char *, Value *> TypeTable;
	static Context &getContext();
	
	TypeTable &getTable();
	void setProgram(Program *prog);
	Program *getProgram();
private:
	TypeTable table;	
};

#endif
