
#include <cstdio>
#include <cmath>

void car2pol(double x, double y, double &r, double &alpha);
void pol2car(double r, double alpha, double &x, double &y);

int main()
{
	bool ende = true;
	char auswahl = 0;
	while (ende)
	{
		
		double x= 0, y = 0, r = 0, alpha = 0;
		if (!auswahl)
		{
			printf("Menue\n");
			printf("1: Kartesisch -> Polar\n");
			printf("2: Polar -> Kartesisch\n");
			printf("0: Programm beenden\n");
		}
		scanf("%c", &auswahl);

		switch(auswahl)
		{
		case '1':
			printf("Bitte x eingeben: ");
			scanf("%Lf", &x);
			printf("Bitte y eingeben: ");
			scanf("%Lf", &y);
			car2pol(x, y, r, alpha);
			printf("r    : %Lf\n", r);
			printf("alpha: %Lf\n", alpha);
			break;

		case '2':
			printf("Bitte r eingeben: ");
			scanf("%Lf", &r);
			printf("Bitte alpha eingeben: ");
			scanf("%Lf", &alpha);
			pol2car(r, alpha, x, y);
			printf("x    : %Lf\n", x);
			printf("y    : %Lf\n", y);
			break;
		
		case '0':
			ende = false;
			break;
		
		default:
			if (auswahl >= 0x60)
			{
				printf("Fehler\n");
				auswahl = 0;
			}
		}
	}
}

void car2pol(double x, double y, double &r, double &alpha)
{
	r = sqrt(x * x + y * y);
	if (y == 0)
		alpha = 0;
	else
		alpha = atan(y / x) * 180 / 3.1415;
}
void pol2car(double r, double alpha, double &x, double &y)
{
	x = r * cos(alpha * 3.1415 / 180.0);
	y = r * sin(alpha * 3.1415 / 180.0);
}