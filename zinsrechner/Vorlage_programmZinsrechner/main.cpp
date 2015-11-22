#include <iostream>
#include <math.h>
#include <conio.h>
#include <iomanip>
using namespace std;

// Prototypen
int menue();
float berechneZins(float, float, int);
void berechneZins_jaehrlich(float fanf, float fzins, int ilz);
float eingabeBetrag(); 


void main()
{
 //Variablen definieren
 //------------------------------------------
 float fKapital=0, fEndkapital=0, fZinssatz=0;
 int iLaufzeit, iAuswahl;

 char cEingabe;
 //------------------------------------------
 locale::global(locale("German_germany"));
 cout << setprecision(2) << fixed;
 do //Schleifenbeginn
 {	
	 system("cls"); //Bildschirm leeren
	 iAuswahl=menue();
	 switch (iAuswahl) //Mehrfachauswahl -- 1-2
	  {
	   case 1: //Endkapital berechnen
	   {
		//------------------------------------------
		cout << '\n' << "Sparplan (Zinsen) berechnen" << endl;
		cout << '\n' << "Bitte geben Sie das Startkapital ein: ";
		fKapital=eingabeBetrag();
		cout << "Bitte geben Sie den Zinssatz in % ein: ";
		fZinssatz=eingabeBetrag();;
		cout << "Bitte geben Sie die Laufzeit in Jahren ein:";
		iLaufzeit=eingabeBetrag();
		cout << endl;

		//Funktion zur Berechnung des Endkapitals aufrufen
		


		//Ausgabe des Endkapitals
		cout << "Nach " << iLaufzeit << " Jahren:\t" << fEndkapital << endl << endl;
		break;
		//------------------------------------------
	   }
	   case 2: //Jährliche Endkapitalausgabe
	   {
		//------------------------------------------
		cout << '\n' << "Sparplan (Zinsen) mit jährlicher Ausgabe" << endl;
		cout << '\n' << "Bitte geben Sie das Startkapital ein: ";
		fKapital=eingabeBetrag();
		cout << "Bitte geben Sie den Zinssatz in % ein: ";
		fZinssatz=eingabeBetrag();;
		cout << "Bitte geben Sie die Laufzeit in Jahren ein:";
		iLaufzeit=eingabeBetrag();
		cout << endl;

		//Für jedes Jahr...  Funktion aufrufen


		

		cout << endl;
		break;
		//------------------------------------------
	   }
	   default: //Keine brauchbare Eingabe
	   {
		cout << "Dieser Menuepunkt ist nicht vorhanden." << endl;
		break;
	   }
	  }
  cout << endl << "Wollen Sie nochmal? (J/N) ";
  cin>>cEingabe;
 }while(cEingabe == 'j' || cEingabe == 'J');
}


int menue()
{
int ieingabe=0;





}

float berechneZins(float fanf, float fzins, int ilz)
{
//Berechnung des Endkapitals


}

void berechneZins_jaehrlich(float fanf, float fzins, int ilz)
{
float fend;




}

float eingabeBetrag()
{

float fBetrag;






}