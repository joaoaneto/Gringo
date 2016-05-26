
#ifndef CLASSES_GRINGO_HPP
#define CLASSES_GRINGO_HPP

#include <map>
#include <string>
#include <math.h>
#include <stdio.h>
#include <vector>
using std::vector;
using namespace std;

class Node {
	public:
		virtual void accept(class Visitor *) = 0;
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
		//void accept(Visitor *);
};

class BinExpPlus: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		BinExpPlus(Exp *e, class Factor *f): exp(e), factor(f){}
		Exp *getExp (){
			return this->exp;
		}
		Factor *getFactor(){
			return this->factor;
		}
		void accept(Visitor *);
};

class BinExpMinus: public Exp {
	private:
		Exp *exp;
		Factor *factor;
	public:
		BinExpMinus(Exp *e, Factor *f): exp(e), factor(f){}
		Exp *getExp (){
			return this->exp;
		}
		Factor *getFactor(){
			return this->factor;
		}
		void accept(Visitor *);
};

class FactorMul: public Factor {
	private:
		Factor *factor;
		UnExp *unExp;
	public:
		FactorMul(Factor *f, UnExp *ue): factor(f), unExp(ue){}
		Factor *getFactor(){
			return this->factor;
		}
		UnExp *getUnExp(){
			return this->unExp;
		}
		void accept(Visitor *);
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
		void accept(Visitor *);
};

class UnExpPlus : public UnExp {
	private:	
		Value *value;
	public:
		UnExpPlus(Value *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *);
};

class UnExpMinus : public UnExp {
	private:
		Value *value;
	public:
		UnExpMinus(Value *v): value(v){}
		Value *getValue(){
			return this->value;
		}
		void accept(Visitor *);
};

class UnExpLog : public UnExp {
	private:
		Exp *exp;
	public:
		UnExpLog(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *);
};

class UnExpExp: public UnExp {
	private:
		Exp *exp;
	public:
		UnExpExp(Exp *e): exp(e){}
		Exp *getExp(){
			return this->exp;
		}
		void accept(Visitor *);
};

class IntValue: public Value {
	private:
		int value;
	public:
		int getValue(){
			return this->value;
		}

		IntValue(int value):value(value){}

		virtual Type getType(){
			return INT;
		}
          
		void accept(Visitor *);
};

class DoubleValue: public Value {
	private:
		double value;
	public:
		double getValue(){
			return this->value;
		}
		DoubleValue(double value):value(value){}

		virtual Type getType(){
				return DOUBLE;
		}

		void accept(Visitor *v);
};


class IdValue: public Value {
	private:
		char *idValue;
	public:
		char *getValue(){
			return this->idValue;
		}

		IdValue(char *idValue):idValue(idValue){}

		virtual Type getType(){
			return ID_VALUE;
		}
		//void accept(Visitor *);
};

class LparExpRpar : public Value {
	private:
		Exp *exp;
	public:
		LparExpRpar(Exp *e) : exp(e){}

		Exp *getExp(){
			return this->exp;
		}
		//void accept(Visitor *);
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
		//void accept(Visitor *);
}; 

class Visitor {
public:
	//virtual void visit(Commands *) = 0;
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
	//virtual void visit(IdValue *) = 0;
	//virtual void visit(LparExpRpar *) = 0;
	//virtual void visit(Atribuition *) = 0;
};

class Operations : public Visitor {
	private:
		vector<Value *> stack_;
	public:
		Operations(){};
		void visit(IntValue *v){
			printf("Entrou no visit do IntValue!\n\n");
			stack_.push_back(v);
		}

		void visit(DoubleValue *v){
			stack_.push_back(v);
		}

		void visit(BinExpPlus *bep){
			bep->getExp()->accept(this);
			bep->getFactor()->accept(this);
			Value *value1 = stack_.back();
			stack_.pop_back();
			Value *value2 = stack_.back();
			stack_.pop_back();

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
			Value *value1 = stack_.back();
			stack_.pop_back();
			Value *value2 = stack_.back();
			stack_.pop_back();

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
			Value *value1 = stack_.back();
			stack_.pop_back();
			Value *value2 = stack_.back();
			stack_.pop_back();

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
			Value *value1 = stack_.back();
			stack_.pop_back();
			Value *value2 = stack_.back();
			stack_.pop_back();

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
	        Value *value = stack_.back();
	        stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue *> (value);
			} else {
				DoubleValue *v = static_cast <DoubleValue *> (value);
			}

			delete value;
		}

		void visit(UnExpMinus *uem){
			uem->getValue()->accept(this);
			Value*value = stack_.back();
			stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue *> (value);
			} else {
				DoubleValue *v = static_cast <DoubleValue *> (value);
			}

			delete value;
		}

		void visit(UnExpLog *uel){
			uel->getExp()->accept(this);
			Value *value = stack_.back();
			stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue*> (value);
				stack_.push_back(new IntValue (log (v->getValue())));
			}
			if(value->getType() == Value::DOUBLE){
				DoubleValue *v = static_cast <DoubleValue*> (value);
				stack_.push_back(new DoubleValue (log (v->getValue())));
			}
		}

		void visit(UnExpExp *uee){
			uee->getExp()->accept(this);
			Value *value = stack_.back();
			stack_.pop_back();

			if(value->getType() == Value::INT){
				IntValue *v = static_cast <IntValue*> (value);
				stack_.push_back(new IntValue (exp (v->getValue())));
			}
			if(value->getType() == Value::DOUBLE){
				DoubleValue *v = static_cast <DoubleValue*> (value);
				stack_.push_back(new DoubleValue (exp (v->getValue())));
			}
		}
};
/*
void Commands::accept(Visitor *v){
	v->visit(this);
}
*/
void BinExpPlus::accept(Visitor *v){
	v->visit(this);
}

void BinExpMinus::accept(Visitor *v){
	v->visit(this);
}

void FactorMul::accept(Visitor *v){
	v->visit(this);
}

void FactorDiv::accept(Visitor *v){
	v->visit(this);
}

void UnExpPlus::accept(Visitor *v){
	v->visit(this);
}

void UnExpMinus::accept(Visitor *v){
	v->visit(this);
}

void UnExpLog::accept(Visitor *v){
	v->visit(this);
}

void UnExpExp::accept(Visitor *v){
	v->visit(this);
}

void IntValue::accept(Visitor *v){
	printf("Entrou no accept do IntValue\n\n");
	printf("O valor do IntValue : %d\n\n",this->getValue());
	printf("O tipo do Enum : %d\n\n",this->getType());
	v->visit(this);
}

void DoubleValue::accept(Visitor *v){
	v->visit(this);
}
/*
void IdValue::accept(Visitor *v){
	v->visit(this);
}
*/
/*
void LparExpRpar::accept(Visitor *v){
	v->visit(this);
}

void Atribuition::accept(Visitor *v){
	v->visit(this);
}
*/
#endif
