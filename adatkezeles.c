
#include "adatkezeles.h"
#include "debugmalloc.h"

void struktura_kiir(Telefon *eleje){

    Telefon *mozgo = eleje;
    while(mozgo != NULL){
        printf("%s/%s/%s/%s/\n", mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
        mozgo = mozgo->kov;
    }
}

Tipusok tipus_keres(char *tipus) {

    if (strcmp(tipus, "nev") == 0 || strcmp(tipus, "Nev") == 0)
        return nev;

    if (strcmp(tipus, "foglalkozas") == 0 || strcmp(tipus, "Foglalkozas") == 0)
        return foglalkozas;

    if (strcmp(tipus, "lakcim") == 0 || strcmp(tipus, "Lakcim") == 0)
        return lakcim;

    if (strcmp(tipus, "szam") == 0 || strcmp(tipus, "Szam") == 0)
        return szam;

    //Ha a típus nem létezik a struktúrában, 'nincs' értékkel térünk vissza.

    return nincs;
}





//Mivel a rekordot_keres fv bármilyen típusú rekordot kaphat paraméterként ami szerepel a struktúrában,
//az egyszerûbben átlátható kód érdekében a típusokhoz külön függvényt írtam.

Telefon *rekordot_keres_nev(Telefon *eleje, char *adat) {

    if(eleje == NULL)
        return NULL;

    Telefon *mozgo = eleje;
    Telefon *keresett = NULL;

    int db = 0;

        while (mozgo != NULL) {

            if(strcmp(mozgo->nev, adat) == 0){
                db++;
                keresett = mozgo;
            }

            mozgo = mozgo->kov;

            //Ha megtalálom a keresett rekordot, a db számát növelem eggyel, és a keresettet ráállítom
            //megtalált rekordra, majd visszalépek a ciklusba, keresve egy, az adatot tartalmazó rekord
            //következõ felbukkanását.

        }
            //Ha többször szerepel az adat a struktúrában, akkor azt jelezzük a felhasználónak,
            //új adattal történõ keresésre hívjuk fel.

        if(db>1) {

            printf("\nTobb talalat is van, probalja meg masik adattal.\n");
            return NULL;
        }
            //Ha probléma nélkül sikerült megtalálni a rekordot, visszaadjuk a címét
        return keresett;
    }

//A többi segédfüggvény ugyanezen elven mûködik, csupán a típusuk más.

Telefon *rekordot_keres_foglalkozas(Telefon *eleje, char *adat) {

    if(eleje == NULL)
        return NULL;

    Telefon *mozgo = eleje;
    Telefon *keresett = NULL;

    int db = 0;

    while (mozgo != NULL) {

        if(strcmp(mozgo->foglalkozas, adat) == 0){
            db++;
            keresett = mozgo;
        }

        mozgo = mozgo->kov;
    }

    if(db>1) {

        printf("\nTobb talalat is van, probalja meg masik adattal.\n");
        return NULL;
    }

    return keresett;
}

Telefon *rekordot_keres_lakcim(Telefon *eleje, char *adat) {

    if(eleje == NULL)
        return NULL;

    Telefon *mozgo = eleje;
    Telefon *keresett = NULL;

    int db = 0;

    while (mozgo != NULL) {

        if(strcmp(mozgo->lakcim, adat) == 0){
            db++;
            keresett = mozgo;
        }

        mozgo = mozgo->kov;
    }

    if(db>1) {

        printf("\nTobb talalat is van, probalja meg masik adattal.\n");
        return NULL;
    }

    return keresett;
}

Telefon *rekordot_keres_szam(Telefon *eleje, char *adat) {

    if(eleje == NULL)
        return NULL;

    Telefon *mozgo = eleje;
    Telefon *keresett = NULL;


    int db = 0;

    while (mozgo != NULL) {

        if(strcmp(mozgo->szam, adat) == 0){
            db++;
            keresett = mozgo;
        }

        mozgo = mozgo->kov;
    }

    if(db>1) {

        printf("\nTobb talalat is van, probalja meg masik adattal.\n");
        return NULL;
    }

    return keresett;
}


Telefon *rekordot_keres(Telefon *eleje, Tipusok tipus, char *adat) {

    if(tipus == nev){
        return rekordot_keres_nev(eleje, adat);
    }
    else if(tipus == foglalkozas){
        return rekordot_keres_foglalkozas(eleje, adat);
    }
    else if(tipus == lakcim){
        return rekordot_keres_lakcim(eleje, adat);
    }
    else if(tipus == szam){
        return rekordot_keres_szam(eleje, adat);
    }

    return NULL;

}

Telefon *rekord_elotti(Telefon *eleje, Tipusok tipus, char *adat) {
    Telefon *mozgo = eleje;
    Telefon *keresett = rekordot_keres(eleje, tipus, adat);

    while (mozgo->kov != keresett) {
        if(mozgo->kov == NULL){
            return NULL;
        }
        mozgo = mozgo->kov;
    }

    return mozgo;
}


Telefon *rekordot_modosit(Telefon *eleje, Tipusok tipus, char *regiadat, char *ujadat) {

    //Ha a rekord nincs benne a listánkban, NULL pointerrel térünk vissza.

    Telefon *keresett=rekordot_keres(eleje, tipus, regiadat);

    if (keresett == NULL)
        return NULL;

    else {

        if (tipus == nev)
            strcpy(keresett->nev, ujadat);

        if (tipus == foglalkozas)
            strcpy(keresett->foglalkozas, ujadat);

        if (tipus == lakcim)
            strcpy(keresett->lakcim, ujadat);

        if (tipus == szam)
            strcpy(keresett->szam, ujadat);

        return keresett;
    }
}
//Az elejét **-al vesszük át, ugyanis a késöbbiekben lehet meg akarjuk
//változtatni, hogy mire mutat.

//A függvénynek nem kell visszaadnia semmit, ugyanis csak a listába fûz egy elemet.
void rekordot_beszur(Telefon **eleje, char *nev, char *foglalkozas, char *lakcim, char *telefonszam) {

    if(rekordot_keres(*eleje, szam, telefonszam) != NULL && strcmp(telefonszam, "-") != 0) {
        printf("%s: A szam mar letezik az adatbazisban.", telefonszam);
        return;
    }

    Telefon *uj;
    Telefon *mozgo;
    uj = (Telefon *) malloc(sizeof(Telefon));


    //Az új rekord adataiba belemásolom a bekért paramétereket.

    strcpy(uj->nev, nev);
    strcpy(uj->foglalkozas, foglalkozas);
    strcpy(uj->lakcim, lakcim);
    strcpy(uj->szam, telefonszam);

    uj->kov = NULL;


    //Amennyiben nem létezik a lista, amit átvett a függvény, a bekért paraméterekkel feltöltött rekord lesz
    //az új lista elsõ eleme.

    if (*eleje == NULL) {
        *eleje = uj;
    }

        //Ha létezik a megadott lista, akkor végigmegy rajta, és a végére beszúrja az új létrehozott rekordot.

    else {
        for (mozgo = *eleje; mozgo->kov != NULL; mozgo = mozgo->kov) {
        }
        mozgo->kov = uj;
    }

}

Telefon *rekordot_torol(Telefon **eleje, Tipusok tipus, char *adat) {

    Telefon *keresett = rekordot_keres(*eleje, tipus, adat);


    //Ha nincs ilyen elem
    if (keresett == NULL)
        return NULL;


        //Ha az elsõ elemet töröljük. Itt változtatjuk meg a helyet, amire
        //az eleje mutat, ezért kellett **-al jelölni. Ilyenkor a függvény meghívásában is
        //cím szerint kell átadni.

    else if (keresett == *eleje) {
        Telefon *ujeleje = (*eleje)->kov;
        free(*eleje);
        *eleje = ujeleje;

        return *eleje;
    }


        //Ha a közepérõl vagy végérõl törlünk.
    else {
        Telefon *elozo=rekord_elotti(*eleje, tipus, adat);
        elozo->kov = keresett->kov;
        free(keresett);

        return *eleje;
    }

}

void struktura_felszabadit(Telefon **eleje) {

    //Az eleje pointer címét akarjuk megváltoztatni,
    //ezért **-al kell átadni.

    Telefon *mozgo = *eleje;

    while (mozgo != NULL) {
        Telefon *tmp = mozgo->kov;
        free(mozgo);
        mozgo = tmp;
    }
    *eleje = NULL;

}

bool wildcard_keres(char *input, char *keres){

    //Pointerek értékét nézzük, ha megtaláltuk a két string végét, akkor kilépünk igazzal.
    if (*input == '\0' && *keres == '\0')
        return true;

    //Megnézzük, hogy a '*' helye után van-e még karakter a keres-ben.
    if (*input == '*' && *(input+1) != '\0' && *keres == '\0')
        return false;

    //Ha az inputban kérdõjel van, vagy megegyeznek a karakterek, akkor mindkettõt léptetjük.
    if (*input == '?' || *input == *keres)
        return wildcard_keres(input+1, keres+1);

    //Ha '*'-ot találunk, akkor két lehetõség van:
    //1.: Vagy az inputot léptetjük eggyel
    //2.: Vagy a kerest léptetjük eggyel
    if (*input == '*')
        return wildcard_keres(input+1, keres) || wildcard_keres(input, keres+1);
    return false;
}


void wildcard_kiir_nev(Telefon *eleje, char *input) {

    Telefon *mozgo = eleje;
    while (mozgo != NULL) {
        if (wildcard_keres(input, mozgo->nev) == true) {
            printf("%s/%s/%s/%s\n", mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
        }
        mozgo = mozgo->kov;

    }


}
void wildcard_kiir_foglalkozas(Telefon *eleje, char *input){

    Telefon *mozgo = eleje;
        while(mozgo != NULL){
            if(wildcard_keres(input, mozgo->foglalkozas)) {
                printf("%s/%s/%s/%s/\n", mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
            }
            mozgo = mozgo->kov;

        }
    }



void wildcard_kiir_lakcim(Telefon *eleje, char *input){

    Telefon *mozgo = eleje;
        while(mozgo != NULL){
            if(wildcard_keres(input, mozgo->lakcim)) {
                printf("%s/%s/%s/%s/\n", mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
            }
            mozgo = mozgo->kov;

        }
    }



void wildcard_kiir_szam(Telefon *eleje, char *input){

    Telefon *mozgo = eleje;
        while(mozgo != NULL){
            if(wildcard_keres(input, mozgo->szam)) {
                printf("%s/%s/%s/%s/\n", mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
            }
            mozgo = mozgo->kov;

        }
    }



void wildcard_kiir(Telefon *eleje, Tipusok tipus, char *input){

    if(tipus == 0)
        wildcard_kiir_nev(eleje, input);
    else if(tipus == 1)
        wildcard_kiir_foglalkozas(eleje, input);
    else if(tipus == 2)
        wildcard_kiir_lakcim(eleje, input);
    else if(tipus == 3)
        wildcard_kiir_szam(eleje, input);

}

