#include "addOperator.h"
#include "numOperator.h"

OP *AddOperator::cat(NumOperator *op) {
	if (_num == NULL) {
		_num = op;
		return this;
	} else {
		return new NumOperator(*_num + *op);
	}
	return NULL;
}
