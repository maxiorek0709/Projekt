#include<iostream>
#include<windows.h>
#include"conio.h"

using namespace std;

const int Esc = 27, gora = 72, dol = 80, lewo = 75, prawo = 77; //deklaracja Esc i kursorów

void rysowanie(short os_x, short os_y,short rozmiar_figury, int znak_ascii);
void put(short os_x, short os_y, int znak_ascii);

/*************************************************************************************/
int main()
{

	_CONSOLE_SCREEN_BUFFER_INFO konsola;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &konsola);
	short os_x = konsola.dwMaximumWindowSize.X / 2;					//punkt początkowy (szerokość)
	short os_y = konsola.dwMaximumWindowSize.Y / 10;				//punkt początkowy (wysokość)


/***************************************************************************************/


	cout << "\tAutor: Katarzyna Zakrzewska Gr. 5 nr indeksu: 14966\n\n\nProgram rysuje ksztalt przypominajacy litere W, za pomoca wprowadzonego \nkodu znaku ASCII.\n\n";
	cout <<	"Figure mozna przesuwac uzywajac strzalek oraz zmieniac jej wielkosc za pomoca \nklawiszy \"+\" i \"-\" \n\n";
	cout << "W celu wybrania znaku z jakiego ma byc stworzona figura, podaj liczbe calkowita od 1 do 255 (oprocz liczb: 7, 8, 9, 10, 13, 32) i zatwierdz wybor enterem. \n\n";
	int znak_ascii;
	cin >> znak_ascii;

		while (cin.fail() || znak_ascii < 0 || znak_ascii > 256 || znak_ascii == 7 || znak_ascii == 8 || znak_ascii == 9 || znak_ascii == 10 || znak_ascii == 13 || znak_ascii == 32)					
		{
		cin.clear();																											//sprawdzenie poprawności, wykluczenie białych znaków
		cin.ignore(1000, '\n');
		cout << "Bledna wartosc.\n Wprowadz liczbe calkowita od 1 do 255 (oprocz liczb: 7, 8, 9, 10, 13 i 32). \n\n";
		cin >> znak_ascii;
		}
	cout << "Wybrany znak ASCII to: " << static_cast<char>(znak_ascii)<< "\n\n";


	short rozmiar_figury;
	cout << "Podaj wysokosc figury i zatwierdz wybor enterem.\n";
	cin >> rozmiar_figury;											// wczytanie rozmiarów figury

		while (cin.fail() || rozmiar_figury < 4 || rozmiar_figury > os_x)					//sprawdzenie poprawności
		{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Bledna wartosc.\n Wprowadz cyfre naturalna wieksza od 3.\n UWAGA: Rozmiar figury nie moze byc wiekszy, niz rozmiar konsoli.\n";
		cin >> rozmiar_figury;
		}
	
	char klawisz;

/************************ZMIANA ROZMIARU I POŁOŻENIA************************/
do {
	system ("cls");
	rysowanie(os_x,os_y, rozmiar_figury, znak_ascii);
	put(os_x, os_y, znak_ascii);
	klawisz = _getch();
           
	switch (klawisz)								
	{			
		case '+': 
					
			{if (os_x > rozmiar_figury)						// zabezpieczenie
			{rozmiar_figury ++;	}							// powiększanie 						 
            break;}
        
		
		case '-': {if (rozmiar_figury > 4)					//zabezpieczenie
				 	  {rozmiar_figury--;}
				  else	{rozmiar_figury = 4;} break;}				// pomniejszanie
		case lewo: 
			{ if (os_x > rozmiar_figury)					// zabezpieczenie	
			{ os_x--; }										// przesunięcie w lewo
			break; } 
        
		case prawo: 
			{ if (os_x < konsola.dwMaximumWindowSize.X-1)		//zabezpieczenie
			{ os_x++; }											// przesunięcie w prawo
			break; } 
		
		
		case gora: 
			{ if (os_y>0)									// zabezpieczenie
			{ os_y--; }										// przesunięcie do góry
			break; }					
        
		case dol: { os_y++; break; }						// przesunięcie w dół
		
		case Esc: { break; }								// wyjście z programu
	}				
	
}	
while( klawisz != Esc );

}
	

/************************RYSOWANIE************************/

void rysowanie(short os_x, short os_y, short rozmiar_figury, int znak_ascii)
{
	if (rozmiar_figury == 0)
	{
		return;
	}
	put(os_x, os_y, znak_ascii);
	

	for (int i = 1; i <= rozmiar_figury; ++i)							//prawa pionowa
	{
		put(os_x, os_y + i, znak_ascii);					
	}	


	for (int i = 1; i <= rozmiar_figury /2; ++i)
	{
		put(os_x - i, os_y + rozmiar_figury -i, znak_ascii);			//prawy skos
	}
	

	for (int i = 1; i <= rozmiar_figury / 2; ++i)
	{
		put(os_x - rozmiar_figury/2 - i, os_y + rozmiar_figury/2+ i, znak_ascii);           //lewy skos
	}


	for (int i = 1; i <= rozmiar_figury + 1 ; ++i)
	{
		put(os_x - rozmiar_figury, os_y + i - 1, znak_ascii);									//lewa pionowa
	}
	 
}

/*********ustalenie współrzędnych i drukowanie***************/
	
	void put(short os_x, short os_y, int znak_ascii)
{
  COORD wpolrzedne = {os_x, os_y };
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), wpolrzedne);
  cout << static_cast<char>(znak_ascii);
}
