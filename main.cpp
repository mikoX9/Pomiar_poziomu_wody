#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>

using namespace std;


/*******************
  ZAD 1
*******************/

void oblicz_objetosc(void)
{
  char * nazwa_figury = new char[10];
  float promien;
  float wysokosc;

  cout<<"Wybierz figure: ";
  cin>>nazwa_figury;

  while( strcmp(nazwa_figury, "walec") && strcmp(nazwa_figury, "stozek") )
  {
    cout<<"Wybierz \"walec\" albo \"stozek\": ";
    cin>>nazwa_figury;
  }

  cout<<"Podaj promien podstawy: ";
  cin>>promien;

  if( !strcmp(nazwa_figury, "walec") )
  {
    cout<<"Podaj wysokosc walca ";
    cin>>wysokosc;
    cout<<"Objetosc walca to: "<< M_PI * pow(promien,2)*wysokosc<<endl;

  }
  else if( !strcmp(nazwa_figury, "stozek") )
  {
    cout<<"Podaj wysokosc stozka ";
    cin>>wysokosc;
    cout<<"Objetosc stozka to: "<< M_PI * pow(promien,2)*wysokosc/3<<endl;

  }
  else
    cout<<"Cos sie spier**o!!";

}


float oblicz_objetosc(float promien, float wysokosc)
{
  char * nazwa_figury = new char[10];

  cout<<"Wybierz figure: ";
  cin>>nazwa_figury;

  while( strcmp(nazwa_figury, "walec") && strcmp(nazwa_figury, "stozek") )
  {
    cout<<"Wybierz \"walec\" albo \"stozek\": ";
    cin>>nazwa_figury;
  }

  if( !strcmp(nazwa_figury, "walec") )
  {
    return M_PI * pow(promien,2)*wysokosc;
  }
  else if( !strcmp(nazwa_figury, "stozek") )
  {
    return M_PI * pow(promien,2)*wysokosc/3;
  }
  else
    cout<<"Cos sie spier**o!!";

}


/*******************
  ZAD 2
*******************/

void wyswietl_tablice( int tab[][5] )
{
  cout<<"----------------"<<endl;
  for (int i = 0; i < 5; ++i)
  {
      for (int j = 0; j < 5; ++j)
      {
          cout<<setw(3)<<tab[i][j];
      }
      cout << endl;
  }
  cout<<"----------------"<<endl;
}


void stworz_tablice()
{
  int tab_1[5][5];
  int tab_2[5][5];

  for(int n=1; n<6 ; n++) //wiersze
  {
    for(int m=1; m<6 ; m++) //kolumny
    {
      if( n%2 == 0 )  //wiersz jest parzysty
        tab_1[n-1][m-1] = tab_2[n-1][5-m] = ( n<3 ) ? pow(2,n) + 3*m : pow(n,2) + pow(m,2);
      else
        tab_1[n-1][m-1] = tab_2[n-1][5-m] = ( n*m<10 ) ? m*n : 0;
    }
  }

  wyswietl_tablice(tab_1);
  wyswietl_tablice(tab_2);
}

/*******************
  ZAD 3
*******************/

struct ksiazka {

  int nr_katalogowy;
  string tytul;
  string autor;
  int liczba_stron;
  char rodzaj_okladki;
};

ksiazka lista_bib[10];

ksiazka* wyszukaj_z_miekka( ksiazka * list_k )
{
  cout<<"Ksiazki z "
  for( int i=0; i < sizeof(lista_bib)/sizeof(*lista_bib); i++)  //bo 10 przykladow
  {
    if()
  }
}

void sort_bib( ksiazka *list_k)
{

 cout<< list_k[0].nr_katalogowy;
list_k[0].nr_katalogowy = 20;
}


/*******************
  ZAD 4
*******************/

void suma_cyfr(void)
{
  cout<<"Podaj liczbe: ";
  string liczba_str;
  cin>>liczba_str;

  int sum = 0;
  for(int i = 0; i < liczba_str.size(); i++)
    sum += (int) (liczba_str[i] - '0');

  cout<<"Suma cyfr w liczbie = "<< sum<<endl;
}


/*******************/

int main(void)
{

  //cout << oblicz_objetosc(10,20);
  //stworz_tablice();
  //suma_cyfr();

  lista_bib[0].nr_katalogowy = 11;

  wyszukaj_z_miekka( lista_bib );


}
