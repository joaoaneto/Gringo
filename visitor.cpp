#include "visitor.hpp"

//Operations
void Operations::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(DoubleValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(IdValue *v){
		Context::TypeTable &t = Context::getContext().getTable();

		if(t.find(v->getValue()) == t.end()){
			stack_.push_back(v);
		}else{
			stack_.push_back(t[v->getValue()]);
		}
}

void Operations::visit(Assignment *a){
		a->Assignment::getExp()->accept(this);
		a->Assignment::getIdValue()->accept(this);
		
		Context::TypeTable &t = Context::getContext().getTable();
		
		IdValue *valueId = static_cast <IdValue *> (stack_.back());
		stack_.pop_back();
		t[valueId->getValue()] = stack_.back();
		stack_.pop_back();
}

void Operations::visit(If *i){
	i->If::getExp()->accept(this);
	i->If::getExpList()->accept(this);

	//falta terminar

}

void Operations::visit(BinExpPlus *bep){
		bep->BinExpPlus::getExp()->accept(this);
		bep->BinExpPlus::getFactor()->accept(this);
		Value *value1 = stack_.back();
		stack_.pop_back();
		Value *value2 = stack_.back();
		stack_.pop_back();

		if(value1->getType() == Value::INT && value2->getType() == Value::INT){
			IntValue *v1 = static_cast <IntValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new IntValue(v1->getValue() + v2->getValue()));
			printf("%d\n", static_cast <IntValue *> (stack_.back())->getValue());
			
		}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
			IntValue *v1 = static_cast <IntValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
			
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
				
		}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
			DoubleValue *v1 = static_cast <DoubleValue *> (value1);
			DoubleValue *v2 = static_cast <DoubleValue *> (value2);
			stack_.push_back(new DoubleValue(v1->getValue() + v2->getValue()));
		}
			
		delete value1;
		delete value2;
}

void Operations::visit(BinExpMinus *bem){
		bem->BinExpMinus::getExp()->accept(this);
		bem->BinExpMinus::getFactor()->accept(this);
		Value *value2 = stack_.back();
		stack_.pop_back();
		Value *value1 = stack_.back();
		stack_.pop_back(); 

		if(value1->getType() == Value::INT && value2->getType() == Value::INT){
			IntValue *v1 = static_cast <IntValue *> (value1);
			IntValue *v2 = static_cast <IntValue *> (value2);
			stack_.push_back(new IntValue(v1->getValue() - v2->getValue()));
		
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

void Operations::visit(FactorMul *fm){
		fm->FactorMul::getUnExp()->accept(this);
		fm->FactorMul::getFactor()->accept(this);
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
		
		printf("Resultado: %d\n", static_cast<IntValue*>(stack_.back())->getValue());

		delete value1;
		delete value2;
}

void Operations::visit(FactorDiv *fd){
		fd->FactorDiv::getUnExp()->accept(this);
		fd->FactorDiv::getFactor()->accept(this);
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

void Operations::visit(UnExpPlus *uep){
		uep->UnExpPlus::getValue()->accept(this);
		Value *value = stack_.back();
		stack_.pop_back();

		if(value->getType() == Value::INT){
			IntValue *v = static_cast <IntValue *> (value);
		} else if(value->getType() == Value::DOUBLE){
			DoubleValue *v = static_cast <DoubleValue *> (value);
		}
			
		delete value;
}
void Operations::visit(UnExpMinus *uem){
		uem->UnExpMinus::getValue()->accept(this);
		Value*value = stack_.back();
		stack_.pop_back();

		if(value->getType() == Value::INT){
			IntValue *v = static_cast <IntValue *> (value);
		} else if(value->getType() == Value::DOUBLE){
			DoubleValue *v = static_cast <DoubleValue *> (value);
		}

		delete value;
}

void Operations::visit(UnExpLog *uel){
		uel->UnExpLog::getExp()->accept(this);
		Value *value = stack_.back();
		stack_.pop_back();

		if(value->getType() == Value::INT){
			IntValue *v = static_cast <IntValue*> (value);
			stack_.push_back(new IntValue (log (v->getValue())));
		} else if(value->getType() == Value::DOUBLE){
			DoubleValue *v = static_cast <DoubleValue*> (value);
			stack_.push_back(new DoubleValue (log (v->getValue())));
		}
}

void Operations::visit(UnExpExp *uee){
		uee->UnExpExp::getExp()->accept(this);
		Value *value = stack_.back();
		stack_.pop_back();

		if(value->getType() == Value::INT){
			IntValue *v = static_cast <IntValue*> (value);
			stack_.push_back(new IntValue (exp (v->getValue())));
		} else if(value->getType() == Value::DOUBLE){
			DoubleValue *v = static_cast <DoubleValue*> (value);
			stack_.push_back(new DoubleValue (exp (v->getValue())));
		}
}

void Operations::visit(LparExpRpar *lpr){
		lpr->getExp()->accept(this);
}

//Accepts

/*void Commands::accept(Visitor *v){ 
	v->visit(this); 
}*/

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
	v->visit(this); 
}

void DoubleValue::accept(Visitor *v){ 
	v->visit(this); 
}

void IdValue::accept(Visitor *v){ 
	v->visit(this); 
}

void LparExpRpar::accept(Visitor *v){ 
	v->visit(this); 
}

void Assignment::accept(Visitor *v){ 
	v->visit(this); 
}

void If::accept(Visitor *v){
	v->visit(this);
}