#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "classes_gringo.hpp"
#include <math.h>
#include <vector>
#include <stdio.h>

using std::vector;

class Visitor {
public:
	//virtual void visit(Commands *) = 0;
	virtual void visit(BinExpPlus *) = 0;
	virtual void visit(BinExpMinus *) = 0;
	virtual void visit(BinExpLessThen *) = 0;
	virtual void visit(BinExpLessEqualThen *) = 0;
	virtual void visit(BinExpGreaterThen *) = 0;
	virtual void visit(BinExpGreaterEqualThen *) = 0;
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
	virtual void visit(Assignment *) = 0;
	virtual void visit(If *) = 0;
	virtual void visit(IfElse *) = 0;
	virtual void visit(While *) = 0;
};

class Operations : public Visitor {
private:
	vector<Value *> stack_;
public:
	Operations(){};
	
	void visit(IntValue *v);
	
	void visit(DoubleValue *v);
	
	void visit(IdValue *v);
	
	void visit(Assignment *a);

	void visit(If *i);

	void visit(IfElse *e);

	void visit(While *w);
	
	void visit(BinExpPlus *bep);

	void visit(BinExpMinus *bem);

	void visit(BinExpLessThen *belt);

	void visit(BinExpLessEqualThen *belet);

	void visit(BinExpGreaterThen *begt);

	void visit(BinExpGreaterEqualThen *beget);

	void visit(FactorMul *fm);

	void visit(FactorDiv *fd);

	void visit(UnExpPlus *uep);

	void visit(UnExpMinus *uem);

	void visit(UnExpLog *uel);

	void visit(UnExpExp *uee);

	void visit(LparExpRpar *lpr);
};

#endif
