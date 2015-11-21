
#ifndef __ADD_OP_H__
#define __ADD_OP_H__

#include "arithOperator.h"

#include <ostream>

class AddOperator : public ARITH_OP
{
public:
	AddOperator() : ARITH_OP() { }
	
	virtual ~AddOperator(){ }

	friend std::ostream & operator<<(std::ostream &os, const AddOperator *const op);

	virtual OP *cat(NumOperator *op);
};

#endif
