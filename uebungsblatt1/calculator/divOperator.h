
#ifndef __DIV_OP_H__
#define __DIV_OP_H__

#include "arithOperator.h"

#include <ostream>

class DivOperator : public ARITH_OP
{
public:
	DivOperator() : ARITH_OP() {}
	
	virtual ~DivOperator() {}

	friend std::ostream & operator<<(std::ostream &, const DivOperator *const);

	virtual OP *cat(NumOperator *);
};

#endif
