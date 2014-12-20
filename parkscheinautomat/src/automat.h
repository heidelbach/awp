/**
 * Author: Johannes Heidelbach
 * Class: Automat - A simple interface for an automat
 */

#ifndef __automat_h__
#define __automat_h__

class Automat
{
private:
	// the currently selected parking duration in minutes
	unsigned int duration;
	double const costPerTick;
	unsigned int const tickInMinutes;
public:
	/*
	 * default constructor
	 * @param costPerTick
	 *		determins how much a user has to pay for each tick
	 * @param tickInMinutes
	 *		determines how long a tick is
	 */
	Automat(double costPerTick, unsigned int tickInMinutes);

	// deconstructor
	virtual ~Automat();
	
	/*
	 * increases the parking duration by one tick
	 */
	void prolongParkingDuration();

	/*
	 * returns currently selected parking duration in minutes
	 */
	unsigned int getParkingDuration() const;
};

#endif // __automat_h__
