#include "visitor.hpp"

//Operations

Operations::Operations(){
	countIf = countFunc = countLaces = 	GlobalCountVar.count = GlobalCountVar.countInt = GlobalCountVar.countFloat = GlobalCountVar.countDouble = 0;
};

void Operations::incLaces(){
	++this->countLaces;
}

struct counterVar Operations::getGlobalCount(){
	return this->GlobalCountVar;
};

struct counterFunc Operations::getGlobalCountFunc(){
	return this->GlobalCountFunc;
};

void Operations::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(DoubleValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(If *i){
	i->If::getBlock()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		i->If::getBlock()->accept(this);
	}

}

void Operations::visit(IfElse *e){
	e->IfElse::getExp()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	if(v1->getValue()){
		e->IfElse::getBlock1()->accept(this);
	}else{
		e->IfElse::getBlock2()->accept(this);
	}

}

void Operations::visit(While *w){
	w->While::getExp()->accept(this);
	w->While::getBlock()->accept(this);
	printf("LALALAL\n\n");	

	IntValue *v1 = static_cast<IntValue *>(stack_.back());
	++Operations::countLaces;

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
	bep->BinExpPlus::getLValue()->accept(this);
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
	bem->BinExpMinus::getLValue()->accept(this);
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
	belt->BinExpLessThen::getLValue()->accept(this);
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
	belet->BinExpLessEqualThen::getLValue()->accept(this);
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
	begt->BinExpGreaterThen::getLValue()->accept(this);
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
	beget->BinExpGreaterEqualThen::getLValue()->accept(this);
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
	bee->BinExpEqual::getLValue()->accept(this);
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
	bed->BinExpDiff::getLValue()->accept(this);
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

void Operations::visit(VarDeclaration *vd){
	int newType = vd->getType();
	vd->getNameList()->accept(this);
	
	if(newType == 1){
		GlobalCountVar.countInt += GlobalCountVar.count;
	}else if(newType == 2){
		GlobalCountVar.countFloat += GlobalCountVar.count;
	}
	else if(newType == 3){
		GlobalCountVar.countDouble += GlobalCountVar.count;
	}
	
	GlobalCountVar.count = 0;
	
}

void Operations::visit(FuncDefinition *fdef){
	int newType = fdef->getType();

	if(newType == 1){
		GlobalCountFunc.countInt += GlobalCountFunc.count;
	} else if(newType == 2){
		GlobalCountFunc.countFloat += GlobalCountFunc.count;
	} else if(newType == 3){
		GlobalCountFunc.countDouble += GlobalCountFunc.count;
	} else if(newType == 4){
		GlobalCountFunc.countVoid += GlobalCountFunc.count;
	}
	
	GlobalCountFunc.count = 0;
}

void Operations::visit(Parameter *par){}

/*
void Operations::visit(Name *n){
	printf("ROLAAAA\n\n");
	GlobalCountVar.count++;
}
*/

void Operations::visit(NameID *nID){
	printf("%s\n\n", nID->getIdValue());
	GlobalCountVar.count++;
}

void Operations::visit(NameAssignment *n){
	printf("Assignment : %s\n\n", n->getAssignment()->getIdValue());
	GlobalCountVar.count++;
}


void Operations::visit(Block *b){
	printf("Um print em Block\n");
	b->getVarDecList()->accept(this);
	b->getCommands()->accept(this);

}


//Accepts

void VarDeclaration::accept(Visitor *v){ 
	v->visit(this); 
}

void Block::accept(Visitor *v){ 
	v->visit(this); 
}

void FuncDefinition::accept(Visitor *v){ 
	v->visit(this); 
}

void Parameter::accept(Visitor *v){ 
	v->visit(this); 
}
/*
void Name::accept(Visitor *v){
	v->visit(this);
}
*/

void NameID::accept(Visitor *v){
	v->visit(this);
}

void NameAssignment::accept(Visitor *v){
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

void While::accept(Visitor *v){
	v->visit(this);
}
