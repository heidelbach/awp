
#ifndef __NUM_OP_H__
#define __NUM_OP_H__

#include "operator.h"

#include <ostream>

enum value_t { d, l};
class OP;

unsigned const int magicNUM = 0xCADED;

class NumOperator : public OP
{
private:
	value_t t_value;
	union value {
		double d_value;
		long l_value;
	} u_value;

public:
	unsigned int const myMagicNum = magicNUM;
	NumOperator(long value) : OP()
	{
		t_value = l;
		u_value.l_value = value;
	}

	NumOperator(double value) : OP()
	{
		t_value = d;
		u_value.d_value = value;
	}
	
	virtual ~NumOperator() { }
	
	friend std::ostream & operator<<(std::ostream &os, NumOperator *op);

	const NumOperator operator+(NumOperator const &) const;
	const NumOperator operator-(NumOperator const &) const;
	const NumOperator operator*(NumOperator const &) const;
	const NumOperator operator/(NumOperator const &) const;

	virtual OP *cat(OP *op)
	{
		return 0;
	}

	virtual OP *cat(NumOperator *op)
	{
		return 0;
	}
};

#endif
