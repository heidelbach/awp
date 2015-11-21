#include "vote.h"

#include <cstdlib>

Vote::Vote()
{
	next = NULL;
}

Vote::~Vote()
{
}

void Vote::percentOf(unsigned int sum)
{
	percent = (100.0 * votes) / sum;
}

void Vote::setCount(unsigned int count)
{
	votes = count;
}

void Vote::setNext(Vote *next)
{
	this->next =  next;
}

unsigned int Vote::getCount()
{	
	return votes;
}

float Vote::getPercent()
{
	return percent;
}

Vote *Vote::getNext()
{
	return next;
}
