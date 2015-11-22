/* ************************************
 * Ersteller: Johannes Heidelbach
 * Version: 2015/02/13 15:20 
 * 
 * Gibt die Zinsertraege nach einer ganzzahligen Jahresanzahl aus. 
 * Ein Menue erlaubt die Ausgabe als Endsumme oder als Summe nach 
 * Abschluss jeden Jahres
 *
 * unsigned int ::= int das vorzeichenlos, immer positiv ist
 * ***********************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

/*
 * Die Rueckgabewerte des Menues
 */
enum modus
{
	UNBEKANNT = -1, SPARPLAN = 1, SPARPLAN_JAEHRLICH = 2
};

static const int MENUE_PUNKTE = 2;
static char *sMenuBeschreibung[2] = {"Sparplan", "Sparplan mit jaehrlicher Anzeige"};

/*
 * Zeigt das Menue an, um das Ausgabeformat zu bestimmen.
 * Gibt die im modus definierten Rueckgabewerte zurueck, im Fehlerfall -1.
 */
static int menue()
{
	signed int auswahl = UNBEKANNT;
	
	while (auswahl == UNBEKANNT)
	{
		int iMenuePunkt = 0;
		
		std::cout << "\rBitte Menuepunkt auswaehlen\n" << std::endl;
		
		while (++iMenuePunkt <= MENUE_PUNKTE)
		{
			std::cout << "(" << iMenuePunkt << ") " 
					<< sMenuBeschreibung[iMenuePunkt - 1]
					<< std::endl;
		}
		std::cout << "\n" << "---------------------------------------"
					<< std::endl;
		
		std::cin >> auswahl;
		if (auswahl < 1 || auswahl > 2)
			auswahl = UNBEKANNT;
	}
	std::cout << "\rAuswahl: (" << auswahl << ")  " 
			<< sMenuBeschreibung[auswahl - 1] << "\n" << std::endl;
	return auswahl;
}

/*
 * Bittet den Benutzer um die Eingabe eines Betrages.
 * Der Abfragetext ist "Bitte geben Sie $sText in $sEinheit ein: "
 */
static float eingabeBetrag(char const *const sText, char const *const sEinheit)
{
	float fWert;
	std::cout << "\rBitte geben Sie " << sText << " in " << sEinheit 
			<< " ein: ";
	std::cout.flush();
	std::cin >> fWert;
	return fWert;
}

/*
 * Einfache Funktion zum Berechnen einer ganzzahligen Potenz
 */
static float powInteger(float fWert, unsigned int iPotenz)
{
	float fErgebnis = 1;
	while (iPotenz--)
		fErgebnis *= fWert;
	return fErgebnis;
}

static float berechneZinsendbetrag(float fZins, float fBetrag,
		unsigned int iJahre)
{
	return fBetrag * powInteger(1.0F + (fZins / 100.0F), iJahre);
}

static void berechneZins_jaehrlich(float fZins, float fBetrag,
		 unsigned int iJahre)
{

	int const iStellenLetztesJahr = (int) log10(berechneZinsendbetrag(fZins,
			 fBetrag, iJahre)) + 1;

	int const iStellenJahre = (int) log10(iJahre) + 1;
	
	unsigned int iJahr = 0;
	
	float fSumme = fBetrag;
	
	while (iJahr < iJahre)
	{
		fSumme *= (1.0F + (fZins / 100.0F));
		std::cout << "\rNach "; 
		std::cout.width(iStellenJahre);
		std::cout << ++iJahr << ". Jahr: ";
		std::cout << std::fixed;
		std::cout.precision(2);
		std::cout.width(iStellenLetztesJahr + 3);
		std::cout << fSumme << std::endl;
	}
}

/*
 * Fraegt den Benutzer, ob das Programm nochmal ausgefuehrt werden soll.
 * Gibt 1 genau dann zurueck, wenn das Programm nochmal ausgefuhert werden 
 * soll.
 */
static int nochmalAbfrage()
{
	char cIn;
	std::cout << "\rNochmal? (j/N): ";
	std::cout.flush();
	std::cin >> cIn;
	return (cIn == 'y' || cIn == 'Y' || cIn == 'j' || cIn == 'J') ? 1 : 0;
}

/* 
 * Die Hauptroutine - Kontrolliert Programmablauf und Variablenwerte
 */
int main()
{
	int nochmal = 1;
	while (nochmal)
	{
		int iModus = menue();
		
		if (iModus != UNBEKANNT)
		{
			float fBetrag; 
			float fZinssatz;
			float fJahre;
			unsigned int iJahre;
			
			fBetrag = eingabeBetrag("das Startkapital", "Euro");

			if (fBetrag < 0)
			{
				fBetrag = -fBetrag;
			}
			
			fZinssatz = eingabeBetrag("den Zinssatz", "%");

			fJahre = eingabeBetrag("die Laufzeit", "Jahren");
			
			if (fJahre < 0) 
			{
				fJahre = -fJahre;
			}
				
			iJahre = (unsigned int) fJahre;
			
			std::cout << "\n";
			switch (iModus)
			{
				case SPARPLAN:
					std::cout << "\rNach " << iJahre 
<< " Jahren: " << berechneZinsendbetrag(fZinssatz, fBetrag, iJahre)
<< std::endl;
					break;
				case SPARPLAN_JAEHRLICH:
					berechneZins_jaehrlich(
							fZinssatz,
							fBetrag,
							iJahre);
					break;
				default:
					// Fehler
					std::cerr << "\rNicht implementierter"
<< " case!" << std::endl;
					abort();
			}
			std::cout << "\n";
		}
		nochmal = nochmalAbfrage();
	}
	getchar(); // leeren Eingabepuffer
	std::cout << "\rDruecken Sie eine Taste zum Beenden" << std::endl;
	getchar();
	return EXIT_SUCCESS;
}
