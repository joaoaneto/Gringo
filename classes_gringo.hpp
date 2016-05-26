#ifndef ARQ_CLASS_H
#define ARQ_CLASS_H

#include <map>
#include <string>
#include <math.h>

using namespace std;

class Node {
	
};

class Program : public Node {	
};

class ExpList : public Program {
};

class Command : public ExpList {
};

class Exp : public Command {
};

class Factor: public Exp {
};

class UnExp: public Factor {
};


class Value : public UnExp {
	protected:
		Type type;
	public:
		enum Type {
			INT,
			DOUBLE,
			ID_VALUE
		};
		virtual Type getType() = 0; 

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

class UnExpPlus : public UnExp {
	private:	
		Value *value;
	public:
		UnExpPlus(Value *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
	}
};

class UnExpMinus : public UnExp {
	private:
		Value *value;
	public:
		UnExpMinus(Value *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class UnExpLog : public UnExp {
	private:
		Exp *exp;
	public:
		UnExpLog(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class UnExpExp: public UnExp {
	private:
		Exp *exp;
	public:
		UnExpExp(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class IntValue: public Value {
	private:
		int value;
	public:
		int getValue() const{
			return this->value;
		}
		IntValue(int value):value(value){
			virtual Type get_type(){
				return INT;
			}
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class DoubleValue: public Value {
	private:
		double value;
	public:
		double getValue() const{
			return this->value;
		}
		DoubleValue(double value):value(value){
			virtual get_type(){
				return DOUBLE;
			}
		}
		void accept(Visitor *v){
			v->visit(this);
		}
};

class IdValue: public Value {
	private:
		char *idValue;
	public:
		char *getValue() const{
			return this->idValue;
		}
		IdValue(char *idValue):idValue(idValue){
			virtual get_type(){
				return ID_VALUE;
			}
		}
		void accept(Visitor *v){
			v->visit(this);
		}
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

class Operations : public Visitor {
	private:
		vector <Value *> stack_;
	public:
		void visit(IntValue *v){
			stack_.push_back(v);
		}

		void visit(DoubleValue *v){
			stack_.push_back(v);
		}

		void visit(BinExpPlus *bep){
			bep->getExp()->accept(this);
			bep->getFactor()->accept(this);
			Value *value1 = stack_.pop_back();
			Value *value2 = stack_.pop_back();

			if(value1->getType() == Value::INT && value2->getType() == Value::INT){
				IntValue *v1 = static_cast <IntValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new IntValue(v1->getValue() + v2->getValue()));
			}
			else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
				IntValue *v1 = static_cast <IntValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			}
			
			delete value1;
			delete value2;
		}

		void visit(BinExpMinus *bem){
			bem->getExp()->accept(this);
			bem->getFactor()->accept(this);
			Value *value1 = stack_.pop_back();
			Value *value2 = stack_.pop_back();

			if(value1->getType() == Value::INT && value2->getType() == Value::INT){
				IntValue *v1 = static_cast <IntValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new IntValue(v1->getValue() - v2->getValue()));
			}
			else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
				IntValue *v1 = static_cast <IntValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() - v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() - v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() - v2->getValue()));
			}
			
			delete value1;
			delete value2;
		}

		void visit(FactorMul *fm){
			fm->getUnExp()->accept(this);
			fm->getFactor()->accept(this);
			Value *value1 = stack_.pop_back();
			Value *value2 = stack_.pop_back();

			if(value1->getType() == Value::INT && value2->getType() == Value::INT){
				IntValue *v1 = static_cast <IntValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new IntValue(v1->getValue() * v2->getValue()));
			}
			else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
				IntValue *v1 = static_cast <IntValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() * v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() * v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() * v2->getValue()));
			}
			
			delete value1;
			delete value2;
		}

		void visit(FactorDiv *fd){
			fd->getUnExp()->accept(this);
			fd->getFactor()->accept(this);
			Value *value1 = stack_.pop_back();
			Value *value2 = stack_.pop_back();

			if(value1->getType() == Value::INT && value2->getType() == Value::INT){
				IntValue *v1 = static_cast <IntValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new IntValue(v1->getValue() / v2->getValue()));
			}
			else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
				IntValue *v1 = static_cast <IntValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() / v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				IntValue *v2 = static_cast <IntValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() / v2->getValue()));
			}
			else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
				DoubleValue *v1 = static_cast <DoubleValue *> (value1);
				DoubleValue *v2 = static_cast <DoubleValue *> (value2);
				stack_.push_back(new DoubleValue(v1->getValue() / v2->getValue()));
			}
			
			delete value1;
			delete value2;
		}

		void visit(UnExpPlus *uep){
			uep->getValue()->accept(this);
	        /*Cadê Valor?*/ Valor *value = stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue *> (value);
			} else {
				DoubleValue *v = static_cast <DoubleValue *> (value);
			}

			delete value;
		}

		void visit(UnExpMinus *uep){
			uem->getValue()->accept(this);
			Valor *value = stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue *> (value);
			} else {
				DoubleValue *v = static_cast <DoubleValue *> (value);
			}

			delete value;
		}

		void visit(UnExpLog *uel){
			uel->getExp()->accept(this);
			Value *value = stack_pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue*> (value);
				stack_.push_back(new IntValue (log (v->getValue()));
			}
			if(value->getType() == Value::DOUBLE){
				DoubleValue *v = static_cast <DoubleValue*> (value);
				stack_.push_back(new DoubleValue (log (v->getValue()));
			}
		}

		void visit(UnExpExp *uee){
			uee->getExp()->accept(this);
			Value *value = stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue*> (value);
				stack_.push_back(new IntValue (exp (v->getValue()));
			}
			if(value->getType() == Value::DOUBLE){
				DoubleValue *v = static_cast <DoubleValue*> (value);
				stack_.push_back(new DoubleValue (exp (v->getValue()));
			}
		}
};

#endif
