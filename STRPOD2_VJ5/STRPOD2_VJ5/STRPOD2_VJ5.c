/*
Napisati program koji iz datoteke èita podatke o studentima i sprema ih u binarno stablo pretraživanja.
struct _student{char ime[20]; char prezime[20]; char indexNo[20];};
Studente se sprema u stablo po sluèajnom uzorku na naèin da se prvo proèita broj zapisa u datoteci (N).
Zatim se sluèajno generira M (M=N/2) brojeva u rasponu od 0 do N te ih se spremi u niz.
Svaki element niza brojeva predstavlja redni broj studenta zapisanog u datoteci, tj. redak zapisa u datoteci.
a.	U stablo upisati samo one studente s odabranim retkom, dakle, samo one studente èiji je broj retka zapisan u nizu s tim da se stablo gradi prema broju indeksa studenta
b.	Ispisati studente zapisane u stablu u INORDER naèinu ispisa s pripadajuæim/generiranim rednim brojem
Napomena: Navedena struktura ne sadrži sve potrebne èlanove, potrebno ju je proširiti.
*/

//prvo iz datoteke u listu i onda iz liste u stablo

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Tstudent *node;
typedef struct Tstudent 
{ 
	char ime[20]; 
	char prezime[20]; 
	int indexNo;
	int rBroj;
	node left;
	node right;
}Tstudent;

typedef struct Lstudent *pos;
typedef struct Lstudent
{
	char ime[20];
	char prezime[20];
	int indexNo;
	int rBroj;
	pos next;
}Lstudent;

int brojRedova();
int randomBrojevi(int, int[]);
node citanjeIzDatotekeUStablo(int, int[], node);
node unosUStablo(node, node);
void inorder(node);
//pos stabloUListu(pos, node);//NIJE NAPRAVLJENO


int main()
{
	srand(time(NULL));//definiranje za random brojeve
	int brRed;//deklaracija varijable koja sadrzi broj redova u fileu
	brRed = brojRedova();//funkcija vraca broj redova
	int* randBrojevi;//ciljamo na niz, ali neznamo koliki je pa idemo preko pokazivaca i dinamicke alokacije, u ovom nizu su sacuvani svi random brojevi
	randBrojevi = (int)malloc((brRed/2)*sizeof(int));//dinamicki alociramo
	int temp;//treba za sortiranje

	Lstudent head;
	head.next = NULL;

	node root=NULL;

	for (int i = 0; i < brRed/2; i++)
	{
		randBrojevi[i] = randomBrojevi(i, randBrojevi);//stvaramo niz random brojeva, nece nikako biti 2 ista
	}

	for (int i = 0; i < brRed/2 - 1; i++)
	{
		for (int j = i + 1; j < brRed / 2; j++)
		{
			if (randBrojevi[j] < randBrojevi[i])//sortiramo niz random brojeva od manjeg prema vecem 
			{
				temp = randBrojevi[i];
				randBrojevi[i] = randBrojevi[j];
				randBrojevi[j] = temp;
			}
		}
	}

	for (int i = 0; i < brRed / 2; i++)
	{
		printf("\n\t%d", randBrojevi[i]);//ispisujemo niz random brojeva za provjeru, zadatak to ne trazi
	}

	root = citanjeIzDatotekeUStablo((brRed / 2), randBrojevi, root);//pozivamo funkciju, funkcija mora biti tipa node i root=funkcija jer se inace samo root u fji promjeni, a ovaj u mainu ostane null, drugo rjesenje bi bili dupli pokazivaci ja mislim,a li ovo je elegantnije
	inorder(root);//samo generic ispis
	printf("\n");
	return 0;
}

int brojRedova()//vraca broj redova, generalno moguce napravi u mainu, ali sve je bolje u funkcijama
{
	int i = 1;//brojac redova, pocinjemo brojat od 1, ne od 0
	char ch;
	FILE *dat;
	dat = fopen("student.txt", "r");
	while (!feof(dat))//fukcionira na nacin da scaki put kada karakter bude enter brojac redova se poveca za 1
	{
		ch = fgetc(dat);
		if ('\n' == ch)
		{
			i++;
		}
	}
	fclose(dat);
	return i;
}

int randomBrojevi(int brojac, int randBrojevi[])//stvara random brojeve i pazi da ne budu dva ista
{
	int R;
	int check = 0;//koristimo 0 i 1 s obzirom da bool ne postoji bez nekih libreria, 1 i 0 dovoljno dobro fukcioniraju
	do
	{
		check = 0;// uvik postavljamo na neistinu, jel nakon sta bi prvi put upalo u 1 nastala bi beskonacna petlja
		R = rand() % 20 + 1;//od 1 do 20 ukljucujuci
		for (int i = 0; i < brojac; i++)//for petlja koja ce provjeriti je li taj broj vec postoji u nizu, ova fja ce se pozivati u petlji i ovaj brojac ce biti "i" iz petlje, odnosno provjeravat ce sve do sada sta je uneseno, nece ic do kraja
		{
			if (randBrojevi[i] == R)//ako je isti kao bilo koji broj u nizu check postaje 1, for petlja se prekida i vraca se na pocetak do while, check se resetira na 0
			{
				check = 1;
				break;//da izadje iz for petlje, nema smisla se vise vrtit nakon sta je jedan pronadjen
			}
		}
	} while (1 == check);
	return R;
}

node citanjeIzDatotekeUStablo(int brojac, int randBrojevi[], node S)
{
	FILE *dat;
	dat = fopen("student.txt", "r");
	node temp;//odi cemo spremat sve iformacije
	int j = 1, i = 0;//brojac redova (pocinje od 1 jel tako ih brojimo) i brojac clanova niza (pocinje od 0 posto se tako broji sa deklariranim nizovima u Cu)
	char ch;//za provjeru entera
	temp = (node)malloc(sizeof(Tstudent));
	while (!feof(dat) && i < brojac)//sta se prvo dogodi, kraj datoteke ili niza, svejedno je
	{
		if (j == randBrojevi[i])//ako je broj retka jednak jednom od brojeva u nizu (niz je sortiran pa ne moramo svaki put prolazit kroz cijeli niz)
		{
			fscanf(dat, "%s %s %d", temp->ime, temp->prezime, &temp->indexNo);
			temp->rBroj = j;
			S = unosUStablo(temp, S);//zapravo unos u stablo
			i++;//kad je uneseno u stablo onda je taj clan u nizu random brojeva iskoristen i ide se na iduci clan za kojeg znamo da je veci posto je niz sortiran
		}
		ch = fgetc(dat);//char prima znak iz datoteke
		if ('\n' == ch)
		{
			j++;//ako je to enter onda idemo u drugi red, odnosno brojac redova se poveca za jedan
		}
	}
	fclose(dat);
	return S;//root= ovo sta smo vratili
}

node unosUStablo(node temp, node S)// standardni unos u stablo samo sta sada ima malo vise od jednog int elementa
{
	if (NULL == S)
	{
		S = (node)malloc(sizeof(Tstudent));
		S->left = NULL;
		S->right = NULL;
		strcpy(S->ime, temp->ime);//PAZLJIVO ODE, mora se koristit strcpy, posto izjednacavanje sa stringovima ne funkcionira u Cu
		strcpy(S->prezime, temp->prezime);
		S->indexNo = temp->indexNo;
		S->rBroj=temp->rBroj;
	}
	//else if (temp->rBroj > S->rBroj)
	else if (temp->indexNo > S->indexNo)//klasika rekurzivno
	{
		S->right = unosUStablo(temp, S->right);
	}
	//else if (temp->rBroj < S->rBroj)
	else if (temp->indexNo < S->indexNo)//klasika rekurzivno
	{
		S->left = unosUStablo(temp, S->left);
	}
	return S;
}

void inorder(node S)//generic ispisivanje inorder
{
	if (NULL != S)
	{
		inorder(S->left);
		printf("\n\t%s %s %d %d", S->ime, S->prezime, S->indexNo, S->rBroj);
		inorder(S->right);
	}
}

/*NE RADI
while (!feof(dat))//pazi na !
{
ch = fgetc(dat);
for (int i = 0; i < brojac; i++)
{
if (j == randBrojevi[i])
{
fscanf(dat, "%s %s %d", temp->ime, temp->prezime, &temp->indexNo);
temp->rBroj = j;
S = unosUStablo(temp, S);
break;//mozda ne treba
}
}
if ('\n' == ch)
{
j++;
}
}
*/