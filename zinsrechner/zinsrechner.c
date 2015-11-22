/* ************************************
 * Ersteller: Johannes Heidelbach
 * Version: 2015/02/13 14:50 
 * Nur Sprachelemente von C
 * 
 * Gibt die Zinsertraege nach einer ganzzahligen Jahresanzahl aus. 
 * Ein Menue erlaubt die Ausgabe als Endsumme oder als Summe nach 
 * Abschluss jeden Jahres
 *
 * unsigned int ::= int das vorzeichenlos, immer positiv ist
 * ***********************************/

#include <stdio.h>
#include <stdlib.h>

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
		
		printf("Bitte Menuepunkt auswaehlen\n");
		printf("\n");
		
		while (++iMenuePunkt <= MENUE_PUNKTE)
		{
			printf("(%d) %s\n", iMenuePunkt, sMenuBeschreibung[iMenuePunkt - 1]);
		}
		printf("\n");
		printf("---------------------------------------\n");
		
		if (scanf("%d", &auswahl) <= 0)
		{
			// Fehler beim Lesen von stdin
			abort();
		}
		if (auswahl < 1 || auswahl > 2)
			auswahl = UNBEKANNT;
	}
	printf("\rAuswahl: (%d) %s\n\n", auswahl, sMenuBeschreibung[auswahl - 1]);
	return auswahl;
}

/*
 * Bittet den Benutzer um die Eingabe eines Betrages.
 * Der Abfragetext ist "Bitte geben Sie $sText in $sEinheit ein: "
 */
static float eingabeBetrag(char const *const sText, char const *const sEinheit)
{
	float fWert;
	printf("Bitte geben Sie %s in %s ein: ", sText, sEinheit);

	if (scanf("%f", &fWert) <= 0)
	{
		// Fehler beim Lesen von stdin
		abort();
	}
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

static float berechneZinsendbetrag(float fZins, float fBetrag, unsigned int iJahre)
{
	return fBetrag * powInteger(1.0F + (fZins / 100.0F), iJahre);
}

static void berechneZins_jaehrlich(float fZins, float fBetrag, unsigned int iJahre)
{
	float fSumme = fBetrag;
	unsigned int iJahr = 0;
	while (iJahr < iJahre)
	{
		fSumme *= (1.0F + (fZins / 100.0F));
		// TODO Formatierung der Ausgabe falls Jahreszahl mehrere Stellen hat
		// TODO Formatierung der Ausgabe falls Summe unterschiedliche Stellenanzahlen hat
		printf("Nach %2d. Jahr: %.2f\n", ++iJahr, fSumme);
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
	printf("Nochmal? (J/N)");
	getchar(); // leeren Eingabepuffer
	if (scanf("%c", &cIn) <= 0)
	{
		// Fehler beim Lesen von stdin
		abort();
	}
	printf("\r");
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
			
			printf("\n");
			switch (iModus)
			{
				case SPARPLAN:
					printf("Nach %d Jahren: %.2f\n", iJahre, berechneZinsendbetrag(fZinssatz, fBetrag, iJahre));
					break;
				case SPARPLAN_JAEHRLICH:
					berechneZins_jaehrlich(fZinssatz, fBetrag, iJahre);
					break;
				default:
					// Fehler
					fprintf(stderr, "\rNicht implementierter case!\n");
					abort();
			}
			printf("\n");
		}
		nochmal = nochmalAbfrage();
	}
	getchar(); // leeren Eingabepuffer
	printf("\rDruecken Sie eine Taste zum Beenden\n");
	getchar();
	return EXIT_SUCCESS;
}
