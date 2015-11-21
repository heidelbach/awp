
#ifndef __OP_H__
#define __OP_H__

class NumOperator;

class OP
{
protected:
	OP() { }
public:
	virtual ~OP() { }
	virtual OP *cat(NumOperator *) = 0;
	virtual OP *cat(OP *op) = 0;
};
#endif
