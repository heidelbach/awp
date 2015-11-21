
#include <cstdlib>
#include <iostream>

#include <stdio.h>

using namespace std;

int main()
{
	int iZeit = 0;
	double dBetrag = 0.0;
	char cTaste;
	const int iTakt = 15;
	const double dEinheit = 0.5;

	cout << "Druecken Sie die Taste p zum Verlaengern der Parkzeit\n"
		<< "Druecken Sie die Taste o zum Drucken des Parkscheins" << endl;

	loop: cTaste = (char) getchar();
	getchar();
	
	if (cTaste >= 'A')
		cTaste ^= 0x20;

	if  (cTaste == 'p') {
		iZeit = iZeit + iTakt;
		cout << "Sie parken fuer " << iZeit << " Minuten" << endl;
		goto loop;
	} else if (cTaste == 'o') {
		// wurde schon mal p gedrueckt?
		if (iZeit == 0) {
			cerr << "Bitte betaetigen Sie erst p" << endl;
		} else {
			dBetrag = dEinheit * iZeit / iTakt;
			cout << "Sie parken fuer " << iZeit << " Minuten\n"
				<< "Zahlen Sie " << dBetrag << endl;
		}
	}

	getchar(); 

	return EXIT_SUCCESS;
}