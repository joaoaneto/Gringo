#ifndef CLASSES_GRINGO_HPP
#define CLASSES_GRINGO_HPP

#include <map>
#include <string.h>
#include <string>

using namespace std;

class Node {
public:
	virtual void accept(class Visitor *) = 0;
};

class Program : public Node {};

class Type : public Node{};

class StatementList : public Program {};

class VarDeclarationList : public StatementList {};

class FuncDefinitionList : public StatementList {};

class FuncDefinition;

class Block;

class NameList;

class Commands : public Block {};

class Command : public Commands {};

class IfElseIf : public Command{};

class Exp : public Command {};

class LValue : public Exp {};

class BinExpEqualDiff : public LValue {};

class BinExpLessGreater : public LValue {};

class BinExpPlusMinus : public LValue {};

class Factor: public LValue {};

class UnExp: public Factor {};

class ParameterList : public FuncDefinition{};


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

class IdValue: public Value {
private:
	string idValue;
public:
	IdValue(string idvalue):idValue(idvalue){} //construtor
	string getValue();
	virtual Type getType();
	void accept(Visitor *);
};

class Parameter : public ParameterList{
private:
	int type;
	IdValue *idValue;
public:
	Parameter(IdValue *id, int t) : idValue(id), type(t){}
	IdValue *getIdValue();
	int getType();
	void accept(Visitor *);
};

class NameList : public VarDeclaration {};

class VarDeclaration : public VarDeclarationList {
private:
	int type;
	NameList *nameList;
public:
	VarDeclaration(int t, NameList *n) : type(t), nameList(n){}
	int getType();
	NameList *getNameList();	
	void accept();
};

//class Abstrata NameList
class NameList : public VarDeclaration {};

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

class Name : public NameList{
private:
	IdValue *idValue;
	Assignment *assignment;
public:
	Name(IdValue *id, Assignment *a) : idValue(id), assignment(a){}
	IdValue *getValue();
	Assignment getAssignment();
	void accept(Visitor *);
};

/*
class VarDeclarationSimple : public VarDeclaration{
private:	
	int type;
	IdValue *idValue;
public:
	VarDeclarationSimple(int t, IdValue *name) : type(t), idValue(name){}
	int getType();
	IdValue *getIdValue();
	void accept(Visitor *);	
};

class VarDeclarationInit : public VarDeclaration{
private:
	int type;
	Assignment *assignment;
public:
	VarDeclarationInit(int t, Assignment *a) : type(t), assignment(a){}
	int getType();
	Assignment *getAssigment();
	void accept(Visitor *);	
};
*/

class FuncDefinition : public FuncDefinitionList {
private:
	int type;
	IdValue *idValue;
	Block *block;
public:
	FuncDefinition(int t, IdValue *id, Block *b) : type(t), idValue(id), block(b){}
	int getType();
	IdValue *getIdValue();
	Block *getBlock();
	void accept(Visitor *);
};

class Block : public FuncDefinition, public If, public IfElse, public While{
private:
	VarDeclarationList *varDecList;
	Commands *commands;
public:
	Block(VarDeclarationList *varList, Commands *comms) : varDecList(varList), commands(comms){}
	VarDeclarationList *getVarDecList();
	Commands *getCommands();
	void accept(Visitor *);
};  

class If: public IfElseIf{
private:
	Exp *exp;
	Block *block;
public:
	If(Exp *e, Block *b): exp(e), block(b){}
	Exp *getExp();
	Block *getBlock();
	void accept(Visitor *);
};

class IfElse: public IfElseIf{
private:
	Exp *exp;
	Block *block1;
	Block *block2;
public:
	IfElse(Exp *e, Block *b1, Block *b2): exp(e),block1(b1),block2(b2){}
	Exp *getExp();
	Block *getBlock1();
	Block *getBlock2();
	void accept(Visitor *);
};


class While: public Command {
private:
	Exp *exp;
	Block *block;
public:
	While(Exp *e, Block *b) : exp(e), block(b){}
	Exp *getExp();
	Block *getBlock();
	void accept(Visitor *);
};

class BinExpPlus: public BinExpPlusMinus {
private:
	LValue *lValue;
	Factor *factor;

public:
	BinExpPlus(LValue *lv, Factor *f): lValue(lv), factor(f){} //construtor
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *);
};

class BinExpMinus: public BinExpPlusMinus {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpMinus(LValue *lv, Factor *f): lValue(lv), factor(f){} //construtor
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *);
};

class BinExpLessThen : public BinExpLessGreater {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpLessThen(LValue *lv, Factor *f): lValue(lv), factor(f){}
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpLessEqualThen : public BinExpLessGreater {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpLessEqualThen(LValue *lv, Factor *f): lValue(lv) , factor(f){}
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpGreaterThen : public BinExpLessGreater {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpGreaterThen(LValue *lv, Factor *f): lValue(lv), factor(f){}
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpGreaterEqualThen : public BinExpLessGreater {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpGreaterEqualThen(LValue *lv, Factor *f): lValue(lv), factor(f){}
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpEqual : public BinExpEqualDiff {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpEqual(LValue *lv, Factor *f): lValue(lv), factor(f){}
	LValue *getLValue();
	Factor *getFactor();
	void accept(Visitor *v);
};

class BinExpDiff : public BinExpEqualDiff {
private:
	LValue *lValue;
	Factor *factor;
public:
	BinExpDiff(LValue *lv, class Factor *f): lValue(lv), factor(f){}
	Exp *getExp();
	Factor *getFactor();
	void accept(Visitor *v);
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

class LparExpRpar : public UnExp {
private:
	Exp *exp;
public:
	LparExpRpar(Exp *e) : exp(e){} //construtor
	Exp *getExp();
	void accept(Visitor *);
};

class Scope {
private:
	map<string, Value*> Symbol_table_;
	Scope *father_;
public:
	Scope *getFather();
	Value *getSymbol(string);
};

class Context {
private:
	static Context *instance;
	Program *program;
	Context(){} //construtor	
public:
	typedef map<string, Value *> TypeTable;
	static Context &getContext();
	
	TypeTable &getTable();
	void setProgram(Program *prog);
	Program *getProgram();
private:
	TypeTable table;	
};

#endif
