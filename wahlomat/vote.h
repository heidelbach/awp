
#ifndef __VOTE_H__
#define __VOTE_H__

class Vote
{
private:
	unsigned int votes;
	float percent;
	Vote *next;

public:
	Vote();

	~Vote();
	
	Vote *getNext();

	float getPercent();

	unsigned int getCount();

	void setNext(Vote *next);

	void setCount(unsigned int);

	void percentOf(unsigned int sum);

};

#endif