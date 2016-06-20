#include "visitor.hpp"

//Operations
void Operations::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(DoubleValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(If *i){
	i->If::getExp()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		i->If::getExpList()->accept(this);
	}

}


void Operations::visit(Commands *c){
	c->Commands::getExpList()->accept(this);
	c->Commands::getCommand()->accept(this);	
}

void Operations::visit(IfElse *e){
	e->IfElse::getExp()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		e->IfElse::getExpList()->accept(this);
	}else{
		e->IfElse::getExpList_2()->accept(this);
	}

}

void Operations::visit(While *w){
	w->While::getExp()->accept(this);
	w->While::getExpList()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());
	
	int a = 0;
	while(v1->getValue()){
		
		if(a == 2){
			break;
		}
		++a;
		printf("Aqui é While msm %d\n", a);
		
	}

	printf("Valor aruah auu while eoq: %d\n\n", v1->getValue());
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
	printf("Eh rolaaaa\n\n");
	Context::TypeTable &t = Context::getContext().getTable();
	
	IdValue *valueId = static_cast <IdValue *> (stack_.back());
	stack_.pop_back();
	t[valueId->getValue()] = stack_.back();
	stack_.pop_back();
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
		//printf("%d\n", static_cast <IntValue *> (stack_.back())->getValue());
		
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
	
	printf("Resultado: %d\n", static_cast<IntValue*>(stack_.back())->getValue());

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

void Operations::visit(BinExpLessThen *belt){
	belt->BinExpLessThen::getExp()->accept(this);
	belt->BinExpLessThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() < v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}
			
	delete value1;
	delete value2;

}

void Operations::visit(BinExpLessEqualThen *belet){
	belet->BinExpLessEqualThen::getExp()->accept(this);
	belet->BinExpLessEqualThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() <= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}
			
	delete value1;
	delete value2;

}

void Operations::visit(BinExpGreaterThen *begt){
	begt->BinExpGreaterThen::getExp()->accept(this);
	begt->BinExpGreaterThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() > v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}
			
	delete value1;
	delete value2;

}

void Operations::visit(BinExpGreaterEqualThen *beget){
	beget->BinExpGreaterEqualThen::getExp()->accept(this);
	beget->BinExpGreaterEqualThen::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() >= v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}
			
	delete value1;
	delete value2;

}

void Operations::visit(BinExpEqual *bee){
	bee->BinExpEqual::getExp()->accept(this);
	bee->BinExpEqual::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() == v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}
			
	delete value1;
	delete value2;

}

void Operations::visit(BinExpDiff *bed){
	bed->BinExpDiff::getExp()->accept(this);
	bed->BinExpDiff::getFactor()->accept(this);
	Value *value1 = stack_.back();
	stack_.pop_back();
	Value *value2 = stack_.back();
	stack_.pop_back();

	if(value1->getType() == Value::INT && value2->getType() == Value::INT){
		IntValue *v1 = static_cast <IntValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::INT && value2->getType() == Value::DOUBLE){
		IntValue *v1 = static_cast <IntValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::INT){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		IntValue *v2 = static_cast <IntValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
	}else if(value1->getType() == Value::DOUBLE && value2->getType() == Value::DOUBLE){
		DoubleValue *v1 = static_cast <DoubleValue *> (value1);
		DoubleValue *v2 = static_cast <DoubleValue *> (value2);
		if(v2->getValue() != v1->getValue()){
			stack_.push_back(new IntValue(1));
		}else{
			stack_.push_back(new IntValue(0));
		}
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

void Operations::visit(FunctionDec *fd){
	fd->getExpList()->accept(this);
	printf("Entrou na birosca do visit\n\n");
}

void Operations::visit(FunctionMain *fm){
	fm->getExpList()->accept(this);
	printf("Entrou na birosca do visit da main\n\n");
}

//Accepts

void Commands::accept(Visitor *v){ 
	v->visit(this); 
}

void VarDeclarationSimple::accept(Visitor *v){ 
	v->visit(this); 
}

void Block::accept(Visitor *v){ 
	v->visit(this); 
}

void VarDeclarationInit::accept(Visitor *v){ 
	v->visit(this); 
}

void FunctionDefinition::accept(Visitor *v){ 
	v->visit(this); 
}

void BinExpPlus::accept(Visitor *v){ 
	v->visit(this); 
}

void BinExpMinus::accept(Visitor *v){ 
	v->visit(this); 
}

void BinExpLessThen::accept(Visitor *v){
	v->visit(this);
}

void BinExpLessEqualThen::accept(Visitor *v){
	v->visit(this);
}

void BinExpGreaterThen::accept(Visitor *v){
	v->visit(this);
}

void BinExpGreaterEqualThen::accept(Visitor *v){
	v->visit(this);
}

void BinExpEqual::accept(Visitor *v){
	v->visit(this);
}

void BinExpDiff::accept(Visitor *v){
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

void IfElse::accept(Visitor *v){
	v->visit(this);
}

void FunctionDec::accept(Visitor *v){
	v->visit(this);
}

void FunctionMain::accept(Visitor *v){
	v->visit(this);
}

void While::accept(Visitor *v){
	v->visit(this);
}