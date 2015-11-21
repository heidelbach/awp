#include "multOperator.h"
#include "numOperator.h"

OP *MultOperator::cat(NumOperator *op)
{
	if (_num == NULL) {
		_num = op;
		return this;
	} else {
		return new NumOperator(*_num * *op);
	}
	return NULL;
}
