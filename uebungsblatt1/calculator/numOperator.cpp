#include "numOperator.h"

#include <ostream>


std::ostream & operator<<(std::ostream &os, NumOperator *op)
{	
	if (op->t_value == d) {
		return os << op->u_value.d_value;
	} else {
		return os << op->u_value.l_value;
	}
}

const NumOperator NumOperator::operator+(NumOperator const &o) const
{	
	if (t_value && l && t_value == o.t_value)
		return NumOperator(u_value.l_value + o.u_value.l_value);
	double value_l;
	double value_r;
	if (t_value == d)
		value_l = u_value.d_value;
	else
		value_l = u_value.l_value;
	if (o.t_value == d)
		value_r = o.u_value.d_value;
	else
		value_r = o.u_value.l_value;
	return NumOperator(value_r + value_l);
}

const NumOperator NumOperator::operator-(NumOperator const &o) const
{	
	if (t_value && l && t_value == o.t_value)
		return NumOperator(u_value.l_value - o.u_value.l_value);
	double value_l;
	double value_r;
	if (t_value == d)
		value_l = u_value.d_value;
	else
		value_l = u_value.l_value;
	if (o.t_value == d)
		value_r = o.u_value.d_value;
	else
		value_r = o.u_value.l_value;
	return NumOperator(value_r - value_l);
}

const NumOperator NumOperator::operator/(NumOperator const &o) const
{	
	if (t_value && l && t_value == o.t_value)
		return NumOperator(u_value.l_value / o.u_value.l_value);
	double value_l;
	double value_r;
	if (t_value == d)
		value_l = u_value.d_value;
	else
		value_l = u_value.l_value;
	if (o.t_value == d)
		value_r = o.u_value.d_value;
	else
		value_r = o.u_value.l_value;
	return NumOperator(value_r / value_l);
}

const NumOperator NumOperator::operator*(NumOperator const &o) const
{	
	if (t_value && l && t_value == o.t_value)
		return NumOperator(u_value.l_value * o.u_value.l_value);
	double value_l;
	double value_r;
	if (t_value == d)
		value_l = u_value.d_value;
	else
		value_l = u_value.l_value;
	if (o.t_value == d)
		value_r = o.u_value.d_value;
	else
		value_r = o.u_value.l_value;
	return NumOperator(value_r * value_l);
}
