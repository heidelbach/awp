#include "subOperator.h"
#include "numOperator.h"

OP *SubOperator::cat(NumOperator *op)
{
	if (_num == NULL) {
		_num = op;
		return this;
	} else {
		return new NumOperator(*_num - *op);
	}
	return NULL;
}
