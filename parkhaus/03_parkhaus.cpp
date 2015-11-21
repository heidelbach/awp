//---------------------------------------------------------------------------
//Parkhausprogramm mit Leitsystem
//---------------------------------------------------------------------------

#include <iostream>
#include <windows.h> //Für farbige Darstellung benötigt


#define NORMAL FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY 
#define ROT FOREGROUND_RED | FOREGROUND_INTENSITY 
#define GRUEN FOREGROUND_GREEN | FOREGROUND_INTENSITY 

using namespace std;

//Prototypen
void zeichneParkhaus(void);
int suchefreieEtage(void);
int suchefreienParkplatz(int);
void einausfahrt(bool);
void schaltePfeile(int, int);
bool EingabepruefenEtage(int iEtagennr);
bool EingabepruefenParkbox(int iParkplatznr);
void farbe(WORD color);

// Globale Datendefinition
bool ab_parkhaus[3][10]
= {{1,1,1,0,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1},
{1,1,0,1,1,1,1,1,1,1}};

bool bfrei;
int ietage, iparkplatz;

bool bpfeillinks0, bpfeilgeradeaus0, bpfeilrechts0;
bool bpfeillinks1, bpfeilgeradeaus1, bpfeilrechts1;
bool bpfeillinks2, bpfeilgeradeaus2, bpfeilrechts2;


//Hauptprogramm
int main(int argc, char* argv[])
{
	farbe(NORMAL);
	do
	{
		bfrei=(suchefreieEtage()+1);
		if (bfrei)
		{
			ietage=suchefreieEtage();
			iparkplatz=suchefreienParkplatz(ietage);
			schaltePfeile(ietage,iparkplatz);
			zeichneParkhaus();
			einausfahrt(1);
			system("cls");
		}
		else
		{
			farbe(ROT);
			cout << "Einfahrt gesperrt - Parkhaus voll"<<endl;
			farbe(NORMAL);
			schaltePfeile(-1,-1);
			zeichneParkhaus();
			einausfahrt(0);
			system("cls");
		}
	}
	while(1);

	return 0;
}



//---------------------------------------------------------------------------
// Funktionsdefinitionen

//Funktion zum Setzen der Ausgabefarben
void farbe(WORD color)
{
	SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void zeichneParkhaus(void)
{

	cout << "-------------------------------------------------"<<endl;
	cout << "Parkbox:-0--1--2--3--4-----------5--6--7--8--9---"<<endl;
	for (int i=2; i>=0; i--)
	{

		// Ausgabe linke Etage
		cout << "Etage " << i << ":";
		for (int j=0; j <=4 ;j++)
		{
			if(ab_parkhaus[i][j]==1)
			{
				farbe(ROT);
				cout << " 1 ";
				farbe(NORMAL);
			}
			else
			{
				farbe(GRUEN); 
				cout << " 0 ";
				farbe(NORMAL);
			}
		}


		//Ausgabe Pfeile
		farbe(GRUEN); 
		switch (i)
		{
		case 0:
			if (bpfeillinks0==1){ cout << "<--";} else  { cout << "   ";}
			if (bpfeilgeradeaus0==1){ cout << " ^ ";} else  { cout << "   ";}
			if (bpfeilrechts0==1){ cout << "-->";} else  { cout << "   ";}
			break;

		case 1:
			if (bpfeillinks1==1){ cout << "<--";} else  { cout << "   ";}
			if (bpfeilgeradeaus1==1){ cout << " ^ ";} else  { cout << "   ";}
			if (bpfeilrechts1==1){ cout << "-->";} else  { cout << "   ";}
			break;

		case 2:
			if (bpfeillinks2==1){ cout << "<--";} else  { cout << "   ";}
			if (bpfeilgeradeaus2==1){ cout << " ^ ";} else  { cout << "   ";}
			if (bpfeilrechts2==1){ cout << "-->";} else  { cout << "   ";}
			break;
		}
		farbe(NORMAL);

		// Ausgabe rechte Etage0
		for (int j=5; j <=9 ;j++)
		{
			if(ab_parkhaus[i][j]==1)
			{
				farbe(ROT);
				cout << " 1 ";
				farbe(NORMAL);
			}
			else
			{
				farbe(GRUEN); 
				cout << " 0 ";
				farbe(NORMAL);
			}
		}
		cout << endl;
	}
	cout << "-------------------------------------------------" <<endl;;
}

int suchefreieEtage(void)
{
	//Hier muss der Funktionscode rein
	//liefert die erste von oben ausgehende Etage mit einem freien Parkplatz zurück
	//falls keiner frei, return -1
}

int suchefreienParkplatz(int iEtagenNr)
{
	//Hier muss der Funktionscode rein
	//liefert den nähesten von der Mitte ausgehenden freien Parkplatz für eine Etage zurück
	//falls keiner frei, return -1
}



void einausfahrt(bool bfrei)
{
	char ceingabe;
	int i, j;

	if (bfrei)
	{
		cout << "Einfahrt oder Ausfahrt (e/a)?" ;
		cin >> ceingabe;
		cout << endl;
		switch (ceingabe)
		{
		case 'e':
			cout<< "In welche Etage fahren Sie (0-2)?";
			cin >> i; cout << endl;
			if(EingabepruefenEtage(i)==0)
				break;
			cout<< "In welche Box fahren Sie (0-9)?";
			cin >> j; cout << endl;
			if (EingabepruefenParkbox(j)==0)
			{break;}

			if (ab_parkhaus[i][j]==0)
			{
				ab_parkhaus[i][j]=1;
			}
			else
			{
				cout << "Parkplatz schon belegt";
				getchar();getchar();
			}
			break;

		case 'a':
			cout<< "Welchen Parkplatz moechten Sie verlassen?" << endl;
			cout<< "Etage (0-2)?";
			cin >> i; cout << endl;
			if(EingabepruefenEtage(i)==0)
				break;
			cout<< "Box (0-9)?";
			cin >> j; cout << endl;
			if(EingabepruefenParkbox(j)==0)
				break;

			if (ab_parkhaus[i][j]==1)
			{
				ab_parkhaus[i][j]=0;
			}
			else
			{
				cout << "Parkplatz ist noch frei";
				getchar();getchar();
			}
			break;
		}
	}
	else
	{
		cout<< "Welchen Parkplatz moechten Sie verlassen?" << endl;
		cout<< "Etage (0-2)?";
		cin >> i; cout << endl;
		if(EingabepruefenEtage(i)==1)
		{
			cout<< "Box (0-9)?";
			cin >> j; cout << endl;
			if(EingabepruefenParkbox(j)==1)
			{	
				if (ab_parkhaus[i][j]==1)
				{
					ab_parkhaus[i][j]=0;
				}
				else
				{
					cout << "Parkplatz ist noch frei";
					getchar();getchar();
				}
			}
		}
	}


}


void schaltePfeile(int iEtagennr, int iParkplatznr)
{
	// Rücksetzen der Pfeile
	bpfeillinks0=false, bpfeilgeradeaus0=false, bpfeilrechts0=false;
	bpfeillinks1=false, bpfeilgeradeaus1=false, bpfeilrechts1=false;
	bpfeillinks2=false, bpfeilgeradeaus2=false, bpfeilrechts2=false;

	if(iEtagennr!=-1 && iParkplatznr!=-1)
	{
		//Schalten der Pfeile
		switch (iEtagennr)
		{
		case 0:
			if (iParkplatznr<=4) { bpfeillinks0=true;} else {bpfeilrechts0=true;}
			break;

		case 1:
			bpfeilgeradeaus0=true;
			if (iParkplatznr<=4) { bpfeillinks1=true;} else {bpfeilrechts1=true;}
			break;

		case 2:
			bpfeilgeradeaus0=true;
			bpfeilgeradeaus1=true;
			if (iParkplatznr<=4) { bpfeillinks2=true;} else {bpfeilrechts2=true;}
		}
	}
}

bool EingabepruefenEtage(int iEtagennr)
{ 
	if((iEtagennr>=0)&&(iEtagennr<=2))
		return 1;
	cout<< "Etage existiert nicht";
	getchar();getchar();
	return 0;
}
bool EingabepruefenParkbox(int iParkplatznr)
{
	if((iParkplatznr>=0)&&(iParkplatznr<=9))
		return 1;
	cout<< "Parkbox existiert nicht";
	getchar();getchar();
	return 0;
}









