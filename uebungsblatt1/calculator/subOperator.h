
#ifndef __SUB_OP_H__
#define __SUB_OP_H__

#include "arithOperator.h"

#include <ostream>

class SubOperator : public ARITH_OP
{
public:
	SubOperator() : ARITH_OP() { }
	
	virtual ~SubOperator() { }

	friend std::ostream &operator<<(std::ostream &, const SubOperator *const);

	virtual OP *cat(NumOperator *);
};

#endif
