#include "visitor.hpp"

//Operations
Operations::Operations(){
	countIf = countFunc = countLaces = 	GlobalCountVar.count = GlobalCountVar.countInt = GlobalCountVar.countFloat = GlobalCountVar.countDouble = GlobalCountFunc.count = GlobalCountFunc.countDouble = GlobalCountFunc.countFloat = GlobalCountFunc.countInt = GlobalCountFunc.countVoid = 0;
};

int Operations::getCountL(){
	return this->countLaces;
}

int Operations::getCountIf(){
	return this->countIf;
}

int Operations::getCountIfElse(){
	return this->countIfElse;
}

int Operations::getCountCall(){
	return this->countCall;
}

void Operations::incLaces(){
	++this->countLaces;
}

struct counterVar Operations::getGlobalCount(){
	return this->GlobalCountVar;
};

struct counterFunc Operations::getGlobalCountFunc(){
	return this->GlobalCountFunc;
};

vector<int> &Operations::getStack(){
	return stackCounterVar_;
}

void Operations::visit(IntValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(DoubleValue *v){ 
	stack_.push_back(v); 
}

void Operations::visit(If *i){
	i->getExp()->accept(this);
	IntValue *v1 = static_cast<IntValue *>(stack_.back());
	++Operations::countIf;

	if(v1->getValue()){
		i->If::getBlock()->accept(this);
	}
}

void Operations::visit(IfElse *e){
	e->IfElse::getExp()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());

	++Operations::countIfElse;

	if(v1->getValue()){
		e->IfElse::getBlock1()->accept(this);
	}else{
		e->IfElse::getBlock2()->accept(this);
	}
}

void Operations::visit(While *w){
	w->While::getExp()->accept(this);
	w->While::getBlock()->accept(this);

	IntValue *v1 = static_cast<IntValue *>(stack_.back());
	++Operations::countLaces;

	int a = 0;
	while(v1->getValue()){		
		if(a == 2){
			break;
		}
		++a;
	}
}

void Operations::visit(IdValue *v){
	Scope::TypeTable &t = Context::getContext().getAtualScope()->getTable();

	if(t.find(v->getValue()) == t.end()){
		stack_.push_back(v);
	}else{
		stack_.push_back(t[v->getValue()]);
	}
	
}

void Operations::visit(IdFunction *id){
	Context::getContext().getVector().push_back(id->getIdFunction());	
	//printf("%d\n", Context::getContext().getVector().size());
}

void Operations::visit(FunctionCall *fcall){
	string teste = fcall->getIdFunction()->getIdFunction();
	vector<string> stackTeste_ = Context::getContext().getVector();
	int i;

	for(i = 0; i < stackTeste_.size(); i++){
		if(teste == stackTeste_[i]){
			++countCall;
			break;
		}		
	}
}

void Operations::visit(Assignment *a){
	a->Assignment::getExp()->accept(this);
	a->Assignment::getIdValue()->accept(this);
	Scope::TypeTable &t = Context::getContext().getAtualScope()->getTable();

	IdValue *valueId = static_cast <IdValue *> (stack_.back());
	stack_.pop_back();
	t[valueId->getValue()] = stack_.back();
	stack_.pop_back();

	//printf("Quantidade: %d\n", t.size());

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

void Operations::visit(VarDeclarations *vds){
	vds->getVarDeclarationList()->accept(this);
	vds->getVarDeclaration()->accept(this);
}

void Operations::visit(FunctionPar *fpar){
	int newType = fpar->getType();
	
	fpar->getIdFunction()->accept(this);
	fpar->getBlock()->accept(this);

	if(newType == 1){
		GlobalCountFunc.countInt++;
	} else if(newType == 2){
		GlobalCountFunc.countFloat++;
	} else if(newType == 3){
		GlobalCountFunc.countDouble++;
	} else if(newType == 0){
		GlobalCountFunc.countVoid++;
	}
	
	GlobalCountFunc.count = 0;

	stackCounterVar_.push_back(stackcounter);
	stackcounter = 0;
}

void Operations::visit(FunctionNonPar *fnp){
	int newType = fnp->getType();
	
	fnp->getIdFunction()->accept(this);
	fnp->getBlock()->accept(this);

	if(newType == 1){
		GlobalCountFunc.countInt++;
	} else if(newType == 2){
		GlobalCountFunc.countFloat++;
	} else if(newType == 3){
		GlobalCountFunc.countDouble++;
	} else if(newType == 0){
		GlobalCountFunc.countVoid++;
	}
	
	GlobalCountFunc.count = 0;

	stackCounterVar_.push_back(stackcounter);
	stackcounter = 0;
}

void Operations::visit(FuncDefinitions *fdefs){
	fdefs->getFuncDefinitionList()->accept(this);
	fdefs->getFuncDefinition()->accept(this);
}

void Operations::visit(CommandsList *csl){
	csl->getCommands()->accept(this);
	csl->getCommand()->accept(this);
}

void Operations::visit(Parameter *par){
	par->getIdValue()->accept(this);
}

void Operations::visit(Parameters *pars){
	pars->getParameterList()->accept(this);
	pars->getParameter()->accept(this);
}

void Operations::visit(Names *n){
	n->getNameList()->accept(this);
	n->getName()->accept(this);
}

void Operations::visit(NameID *nID){
	nID->getIdValue()->accept(this);

	GlobalCountVar.count++;
	stackcounter++;
}

void Operations::visit(NameAssignment *n){
	n->getAssignment()->accept(this);

	GlobalCountVar.count++;
	stackcounter++;
}

void Operations::visit(BlockVarCommands *bvc){
	Scope *scopeVarCommands = new Scope();
	Context::getContext().setAtualScope(scopeVarCommands);
	bvc->getVarDecList()->accept(this);
	bvc->getCommands()->accept(this);
	delete scopeVarCommands;
}


void Operations::visit(BlockCommands *bc){
	Scope *scopeCommands = new Scope();
	Context::getContext().setAtualScope(scopeCommands);
	bc->getCommands()->accept(this);
	delete scopeCommands;

}

void Operations::visit(BlockVar *bv){
	Scope *scopeBlockVar = new Scope();
	Context::getContext().setAtualScope(scopeBlockVar);
	bv->getVarDecList()->accept(this);
	delete scopeBlockVar;
}

//Accepts
void VarDeclaration::accept(Visitor *v){ 
	v->visit(this); 
}

void VarDeclarations::accept(Visitor *v){ 
	v->visit(this); 
}

void BlockVarCommands::accept(Visitor *v){ 
	v->visit(this); 
}

void BlockCommands::accept(Visitor *v){ 
	v->visit(this); 
}

void BlockVar::accept(Visitor *v){ 
	v->visit(this); 
}

void FunctionPar::accept(Visitor *v){ 
	v->visit(this); 
}

void FunctionNonPar::accept(Visitor *v){ 
	v->visit(this); 
}

void FunctionCall::accept(Visitor *v){ 
	v->visit(this); 
}

void FuncDefinitions::accept(Visitor *v){ 
	v->visit(this); 
}

void CommandsList::accept(Visitor *v){ 
	v->visit(this);
}

void Parameter::accept(Visitor *v){ 
	v->visit(this); 
}

void Parameters::accept(Visitor *v){ 
	v->visit(this); 
}

void Names::accept(Visitor *v){
	v->visit(this);
}

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

void IdFunction::accept(Visitor *v){ 
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
