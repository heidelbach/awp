
#ifndef __ARITH_OP_H__
#define __ARITH_OP_H__

#include "operator.h"
#include "numOperator.h"
#include <ostream>

class ARITH_OP : public OP
{
protected:
	NumOperator *_num;

	ARITH_OP() : OP()
	{
		_num = NULL;
	}
public:
	virtual ~ARITH_OP();
	virtual OP *cat(OP *);
	virtual OP *cat(NumOperator *) = 0;
};
#endif
