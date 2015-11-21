
#ifndef __MULT_OP_H__
#define __MULT_OP_H__

#include "arithOperator.h"

#include <ostream>

class MultOperator : public ARITH_OP
{

public:
	MultOperator() : ARITH_OP() { }
	
	virtual ~MultOperator() { }
	
	friend std::ostream & operator<<(std::ostream &, const MultOperator *const);

	virtual OP *cat(NumOperator *);
};

#endif
