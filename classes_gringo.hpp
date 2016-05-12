#ifndef ARQ_CLASS_H
#define ARQ_CLASS_H

#include <map>
#include <string>
using namespace std;

class Node{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Programa: public Node {	
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ListaExp: public Programa {
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Comando: public ListaExp{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Exp: public Comando{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class Factor: public Exp{
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ExpUn: public Factor{
	void accept(Visitor *v){
		v->visit(this);
	}
};


class Valor : public ExpUn{
	void accept(Visitor *v){
		v->visit(this);	
	}
};

class Contexto {
private:
	static Contexto *instancia;
	static Programa *programa;
	Contexto(){}
public:
	typedef map<string, Valor*> TipoTabela;
	static Contexto &getContexto() {
		if (instancia==NULL){
			instancia = new Contexto();
		}
		return *instancia;
	}
	TipoTabela &getTabela(){
		return this->tabela;
	}
	void setPrograma(Programa *prog){
		programa = prog;
	}
	

private:
	TipoTabela tabela;
};

Contexto *Contexto::instancia = NULL;

class Comandos: public ListaExp{
private:
	ListaExp *listaExp;
	Comando *comando;
public:
	Comandos(ListaExp *l, Comando *c): listaExp(l), comando(c){}
	ListaExp *getListaExp(){
		return this->listaExp;
	}
	Comando *getComando(){
		return this->comando;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
};

class ExpBinPlus: public Exp{
private:
	Exp *exp;
	Factor *factor;
public:
	ExpBinPlus(Exp *e, class Factor *f): exp(e), factor(f){}
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

class ExpBinMinus: public Exp{
private:
	Exp *exp;
	Factor *factor;
public:
	ExpBinMinus(Exp *e, Factor *f): exp(e), factor(f){}
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

class FactorMul: public Factor{
private:
	Factor *factor;
	ExpUn *expUn;
public:
	FactorMul(Factor *f, ExpUn *eUn): factor(f), expUn(eUn){}
	Factor *getFactor(){
		return this->factor;
	}
	ExpUn *getExpUn(){
		return this->expUn;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
};

class FactorDiv: public Factor{
private:
	Factor *factor;
	ExpUn *expUn;
public:
	FactorDiv(Factor *f, ExpUn *eUn): factor(f), expUn(eUn){}
	Factor *getFactor(){
		return this->factor;
	}
	ExpUn *getExpUn(){
		return this->expUn;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
};

class PlusValue: public ExpUn{
private:	
	Valor *valor;
public:
	PlusValue(Valor *value): valor(value){}
	Valor *getValor(){
		return this->valor;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
};

class MinusValue: public ExpUn{
private:
	Valor *valor;
public:
	MinusValue(Valor *value): valor(value){}
	Valor *getValor(){
		return this->valor;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
};

class LogValue: public ExpUn{
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

class ExpValue: public ExpUn{
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

class Atribuicao : public Comando {
private:
	Exp *exp;
	IdValue *idValue;
public:
	Atribuicao(Exp *e) : exp(e){}
	Exp *getExp(){
		return this->exp;
	}
	IdValue *getIdValue(){
		return this->idValue;
	}
}; 


class LparExpRpar : public Valor{
private:
	Exp *exp;
public:
	ValorPAR(Exp *e) : exp(e){}
	Exp *getExp(){
		return this->exp;
	}
};

class IntValue: public Valor{
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

class DoubleValue: public Valor{
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

class IdValue: public Valor{
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

class LparExpRpar : public Valor{
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

class Atribuicao : public Comando {
private:
	Exp *exp;
	IdValue *idValue;
public:
	Atribuicao(Exp *e) : exp(e){}

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
	virtual void visit(Comandos *) = 0;
	virtual void visit(ExpBinPlus *) = 0;
	virtual void visit(ExpBinMinus *) = 0;
	virtual void visit(FactorMul *) = 0;
	virtual void visit(FactorDiv *) = 0;
	virtual void visit(ExpUnPlus *) = 0;
	virtual void visit(ExpUnMinus *) = 0;
	virtual void visit(ExpUnLog *) = 0;
	virtual void visit(ExpUnExp *) = 0;
	virtual void visit(IntValue *) = 0;
	virtual void visit(DoubleValue *) = 0;
	virtual void visit(IdValue *) = 0;
	virtual void visit(LparExpRpar *) = 0;
	virtual void visit(Atribuicao *) = 0;
};

#endif
