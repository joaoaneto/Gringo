#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "classes_gringo.hpp"


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
		stack_.push_back(v); 
		printf("Valor na pilha: %d\n\n", static_cast <IntValue*> (stack_.back())->getValue());
	}
	void visit(DoubleValue *v){
		stack_.push_back(v);
		printf("Valor na pilha: %lf\n\n", static_cast <DoubleValue*> (stack_.back())->getValue());
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
			
			printf("Valor soma: %d\n\n", static_cast <IntValue*> (stack_.back())->getValue());
			
		}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
			IntValue *v1 = static_cast <IntValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			
			printf("Valor soma: %lf\n\n", static_cast <DoubleValue*> (stack_.back())->getValue());
			
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			
			printf("Valor soma: %lf\n\n", static_cast <DoubleValue*> (stack_.back())->getValue());	
				
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			
			printf("Valor soma: %lf\n\n", static_cast <DoubleValue*> (stack_.back())->getValue());
		
		}
			
		delete value1;
		delete value2;
	}

	void visit(BinExpMinus *bem){
		bem->getExp()->accept(this);
		bem->getFactor()->accept(this);
		Value *value2 = stack_.back();
		stack_.pop_back();
		Value *value1 = stack_.back();
		stack_.pop_back(); 

		if(value1->getType() == Value::INT && value2->getType() == Value::INT){
			IntValue *v1 = static_cast <IntValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new IntValue(v1->getValue() - v2->getValue()));

			printf("Valor da subtração: %d\n", static_cast <IntValue*> (stack_.back())->getValue());
		
		}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
			IntValue *v1 = static_cast <IntValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() - v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() - v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
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
		
		}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
			IntValue *v1 = static_cast <IntValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() * v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() * v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
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
		
		}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
			IntValue *v1 = static_cast <IntValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() / v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() / v2->getValue()));
		
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
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
			DoubleValue *v = static_cast <DoubleValue *> (value); }
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

//void Commands::accept(Visitor *v){ v->visit(this); }

void BinExpPlus::accept(Visitor *v){ v->visit(this); }

void BinExpMinus::accept(Visitor *v){ v->visit(this); }

void FactorMul::accept(Visitor *v){ v->visit(this); }

void FactorDiv::accept(Visitor *v){ v->visit(this); }

void UnExpPlus::accept(Visitor *v){ v->visit(this); }

void UnExpMinus::accept(Visitor *v){ v->visit(this); }

void UnExpLog::accept(Visitor *v){ v->visit(this); }

void UnExpExp::accept(Visitor *v){ v->visit(this); }

void IntValue::accept(Visitor *v){ v->visit(this); }

void DoubleValue::accept(Visitor *v){ v->visit(this); }

//void IdValue::accept(Visitor *v){ v->visit(this); }

//void LparExpRpar::accept(Visitor *v){ v->visit(this); }

//void Atribuition::accept(Visitor *v){ v->visit(this); }

#endif
