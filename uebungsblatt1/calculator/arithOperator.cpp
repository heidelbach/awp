#include "addOperator.h"
#include "subOperator.h"
#include "multOperator.h"
#include "divOperator.h"
#include "numOperator.h"

#include <ostream>
#include <iostream>

ARITH_OP::~ARITH_OP()
{
	if (_num != NULL)
		delete _num;
}

OP *ARITH_OP::cat(OP *op)
{
	NumOperator *numCast = (NumOperator *) op;
	if (numCast->myMagicNum == NumOperator::magicNUM) {
		return cat(numCast);
	}
	return NULL;
}

std::ostream &operator<<(std::ostream os, const AddOperator *const op)
{
		return os << " + ";
}

std::ostream &operator<<(std::ostream os, const MultOperator *const op)
{
		return os << " * ";
}

std::ostream &operator<<(std::ostream os, const SubOperator *const op)
{
		return os << " - ";
}

std::ostream &operator<<(std::ostream os, const DivOperator *const op)
{
		return os << " / ";
}
