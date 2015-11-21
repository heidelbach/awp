/*
 * Ersteller: Johannes Heidelbach
 *
 * Parkscheinautomat mit Tasten P, O und versteckter Taste A
 * A beendet das Programm 
 * P und O nach Spezifikation
 */
#include <iostream>

using namespace std;

int main(void)
{
	// Konstantendefinition und Initialisierung
	const int iTakt = 15;			// Zeittakt
	const double dEinheit = 0.5;	// Betrag pro Zeittakt

	//Variablendefinition
	int iZeit;						// Parkzeit
	double dBetrag;					// Zahlbetrag
	char cTaste;					// Taste

	// loeschen der Konsole
   	system ("cls");
	
	// Reset
	iZeit = 0;
	dBetrag = 0;
	cTaste = '\0';

	// Haupt-Schleife
	// loopStart
	while (cTaste != 'a') {
		// Start der Schleife
		// Ausgabe der Anleitung
		cout << "                    Bedienungs-Anleitung\n"
				<< "Druecken Sie die P-Taste um die Parkzeit um 15 Minuten zu verlaengern\n"
				<< "Druecken Sie die O-Taste um zu quittieren und den Bezahlvorgang zu starten\n"
				<< "Aktuelle Parkzeit: " << iZeit << " Minuten\n" << endl; 

		// Schleife zum erhöhen der Parkzeit
		while (cTaste != 'o') 
		{ 	// Eingabe
			cout << "Ihre Wahl: ";
			cin >> cTaste;
			if (cTaste >= 'A' && cTaste <= 'Z')
				// wandle grossbuchstaben in kleinbuchstaben um
				cTaste ^= 0x20;
			if (cTaste == 'a') 
			{	// Beende Programm
				// goto end
				break;
			}

			// cTaste P?
			if (cTaste == 'p')
			{    // Verarbeitung, Erhoehung Parkzeit um Zeittakt
				iZeit = iZeit + iTakt;

				// Ausgabe, aktuelle Parkzeit
				cout << "Aktuelle Parkzeit: " << iZeit << " Minuten" << endl;
			}
			else
			{	// cTaste O?
				if (cTaste == 'o')
				{	// wurde P gedrueckt?
					if (iZeit == 0)
					{ 	// Ausgabe, Fehlermeldung P wurde nicht gedrueckt
						cout << "Mindestparkzeit 15 Minuten\n"
								<< "Druecken Sie mindestens 1-mal P" << endl;
					}
					else
					{ 	// Verarbeitung, Berechnung des Preises
						dBetrag = dEinheit * iZeit / iTakt;

						// Ausgabe, Ausgabe des Preises und der Parkzeit
						cout.precision(2); // Betrag auf 2 Nachkommastellen ausgeben
						cout << "Sie haben " << iZeit << " Minuten ausgewaehlt\n"
								<< "Bitte zahlen Sie " << std::fixed << dBetrag << " Euro" << endl;
					}
				}
			}
		}
		// Fange ganz vom Anfang an
		// goto loopStart;
	}
end:
	return 0;
}



