#ifndef ARQ_CLASS_H
#define ARQ_CLASS_H

#include <map>
#include <string>
using namespace std;

class Node {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Program : public Node {	
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ExpList : public Program {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Command : public ExpList {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Exp : public Command {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Factor: public Exp {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class UnExp: public Factor {
	void accept(Visitor *v){
		v->visit(this);
	}
};


class Value : public UnExp {
	void accept(Visitor *v){
		v->visit(this);	
	}
};

class Context {
	private:
		static Context *instance;
		static Program *program;
		Context(){}
	public:
		typedef map<string, Value *> TypeTable;
		static Context &getContext() {
			if (instance == NULL){
				instance = new Context();
			}
			return *instance;
		}
		TypeTable &getTable(){
			return this->table;
		}
		void setProgram(Program *prog){
			program = prog;
		}
	private:
		TypeTable table;
};

Context *Context::instance = NULL;

class Commands: public ExpList {
	private:
		ExpList *expList;
		Command *command;
	public:
		Commands(ExpList *el, Command *c): expList(el), command(c){}
		ExpList *getExpList(){
			return this->expList;
		}
		Command *getCommand(){
			return this->command;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class BinExpPlus: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		BinExpPlus(Exp *e, class Factor *f): exp(e), factor(f){}
		Exp *getExp(){
			return this->exp;
		}
		Factor *getFactor(){
			return this->factor;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class BinExpMinus: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		BinExpMinus(Exp *e, Factor *f): exp(e), factor(f){}
		Exp *getExp(){
			return this->exp;
		}
		Factor *getFactor(){
			return this->factor;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class FactorMul: public Factor {
	private:
		Factor *factor;
		UnExp *unExp;
	public:
		FactorMul(Factor *f, unExp *ue): factor(f), unExp(ue){}
		Factor *getFactor(){
			return this->factor;
		}
		UnExp *getUnExp(){
			return this->unExp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class FactorDiv: public Factor {
	private:
		Factor *factor;
		UnExp *unExp;
	public:
		FactorDiv(Factor *f, UnExp *ue): factor(f), unExp(ue){}
		Factor *getFactor(){
			return this->factor;
		}
		UnExp *getUnExp(){
			return this->unExp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class PlusValue: public UnExp {
	private:	
		Value *value;
	public:
		PlusValue(Valor *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
	}
};

class MinusValue: public UnExp {
	private:
		Value *value;
	public:
		MinusValue(Value *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class LogValue: public UnExp {
	private:
		Exp *exp;
	public:
		LogValue(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class ExpValue: public UnExp {
	private:
		Exp *exp;
	public:
		ExpValue(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class IntValue: public Value {
	public:
		int getValue() const{
			return this->value;
		}
		IntValue(int value):value(value){} //Construtor
		void accept(Visitor *v){
			v->visit(this);
		}
	private:
		int value;
};

class DoubleValue: public Value {
	public:
		double getValue() const{
			return this->value;
		}

		DoubleValue(double value):value(value){} //Construtor
		void accept(Visitor *v){
			v->visit(this);
		}
	private:
		double value;
};

class IdValue: public Value {
	public:
		char *getValue() const{
			return this->idValue;
		}
		IdValue(char *idValue):idValue(idValue){}
		void accept(Visitor *v){
			v->visit(this);
		}
	private:
		char *idValue;
};

class LparExpRpar : public Value {
	private:
		Exp *exp;
	public:
		LparExpRpar(Exp *e) : exp(e){}

		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class Atribuition : public Command {
	private:
		Exp *exp;
		IdValue *idValue;
	public:
		Atribuition(Exp *e) : exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		IdValue	*getIdValue(){
			return this->idValue;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
}; 

class Visitor {
	virtual void visit(Commands *) = 0;
	virtual void visit(BinExpPlus *) = 0;
	virtual void visit(BinExpMinus *) = 0;
	virtual void visit(FactorMul *) = 0;
	virtual void visit(FactorDiv *) = 0;
	virtual void visit(UnExpPlus *) = 0;
	virtual void visit(UnExpMinus *) = 0;
	virtual void visit(UnExpLog *) = 0;
	virtual void visit(UnExpExp *) = 0;
	virtual void visit(IntValue *) = 0;
	virtual void visit(DoubleValue *) = 0;
	virtual void visit(IdValue *) = 0;
	virtual void visit(LparExpRpar *) = 0;
	virtual void visit(Atribuition *) = 0;
};

#endif
