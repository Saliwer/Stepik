#include <iostream>
using namespace std;

struct Expression;
struct Number;
struct BinaryOperation;
struct Visitor;
struct PrintVisitor;

struct Visitor {
	virtual void visitNumber(Number const * number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
	virtual ~Visitor()
	{}
};

struct Expression {
	virtual double evaluate() const = 0;
	virtual void visit(Visitor * visitor) const = 0;
	virtual ~Expression() {
	}
};

struct Number : Expression {
	Number(double value) : value(value) {
	}
	double evaluate() const	{ return value; }
	double get_value() const { return value; }
	//call PrintVisitor::visit(Number const *);
	void visit(Visitor * visitor) const override { visitor->visitNumber(this); } 
	~Number() {
	}
private:
	double value;
};

struct BinaryOperation : Expression {

	BinaryOperation(Expression const *left, char op, Expression const *right)
		: left(left), op(op), right(right) {
	}
	double evaluate() const;
	Expression const * get_left() const { return left; }
	Expression const * get_right() const { return right; }
	char get_op() const { return op; }
	//call PrintVisitor::visit(BinaryOperation const *);
	void visit(Visitor * visitor) const override { visitor->visitBinaryOperation(this); }

	~BinaryOperation() {
		delete left;
		delete right;
	}
private:
	Expression const *left;
	Expression const *right;
	char op;
};


struct PrintVisitor : Visitor {
	void visitNumber(Number const * number) override
	{ 
		 cout << number->get_value();
	}

	void visitBinaryOperation(BinaryOperation const * bop) override
	{
		cout << "(";
		bop->get_left()->visit(this);
		cout << bop->get_op();
		bop->get_right()->visit(this);
		cout << ")";
	}
};



double BinaryOperation :: evaluate() const {
	switch (op)
	{
	case '*':
		return left->evaluate() * right->evaluate();

	case '+':
		return left->evaluate() + right->evaluate();

	case '-':
		return left->evaluate() - right->evaluate();

	case '/':
		return left->evaluate() / right->evaluate();
	default:
		return 0.0;
		break;
	}
}

int main() {

	Expression *sube = new BinaryOperation(new Number (5),'+', new Number(6));
	Expression *expr = new BinaryOperation(new Number(2), '*', sube);
	PrintVisitor visitor;
	expr->visit(&visitor);			
	cout <<" = " << expr->evaluate() << endl;

	return 0;
}