#include "menu.h"


void menut_kiir(void){
    printf("-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o Telefonkonyv Vezerlo -o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-\n"
            "0.: Menu ujrahivasa\n"
           "1.: Telefonkonyv beolvasasa\n"
           "2.: Telefonkonyv kiirasa\n"
           "3.: Rekord felvetele\n"
           "4.: Rekord modositasa\n"
           "5.: Rekord torlese\n"
           "6.: Osszes rekord torlese\n"
           "7.: Telefonkonyv fajlba irasa\n"
           "8.: Wildcard kereses\n"
           "9.: Kilepes\n\n");
}

void sorvege_torol(char *adat){
    char *p;
    if((p=strchr(adat, '\n')) != NULL)
        *p= '\0';

}

void rekordot_beolvas_3(char *nev, char *foglalkozas, char *lakcim, char *szam){

    printf("Adja meg az adatokat!\n");
    printf("Nev:");
    fgets(nev, 51, stdin);  //Ez a bait, mert amúgy nem mûködne.
    fgets(nev, 51, stdin);
    printf("Foglalkozas:");
    fgets(foglalkozas, 128, stdin);
    printf("Lakcim:");
    fgets(lakcim, 128, stdin);
    printf("Telefonszam:");
    fgets(szam, 12, stdin);

    sorvege_torol(nev);
    sorvege_torol(foglalkozas);
    sorvege_torol(lakcim);
    sorvege_torol(szam);
}

