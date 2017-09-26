# VJ5-Strukture-podataka
Vježba 5

Napisati program koji iz datoteke čita podatke o studentima i sprema ih u binarno stablo pretraživanja.
struct _student{char ime[20]; char prezime[20]; char indexNo[20];};
Studente se sprema u stablo po slučajnom uzorku na način da se prvo pročita broj zapisa u datoteci (N).
Zatim se slučajno generira M (M=N/2) brojeva u rasponu od 0 do N te ih se spremi u niz.
Svaki element niza brojeva predstavlja redni broj studenta zapisanog u datoteci, tj. redak zapisa u datoteci.
a.	U stablo upisati samo one studente s odabranim retkom, dakle, samo one studente čiji je broj retka zapisan u nizu s tim da se stablo gradi prema broju indeksa studenta
b.	Ispisati studente zapisane u stablu u INORDER načinu ispisa s pripadajućim/generiranim rednim brojem
Napomena: Navedena struktura ne sadrži sve potrebne članove, potrebno ju je proširiti.
