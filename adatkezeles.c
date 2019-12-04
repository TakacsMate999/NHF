
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

    //Ha a t�pus nem l�tezik a strukt�r�ban, 'nincs' �rt�kkel t�r�nk vissza.

    return nincs;
}





//Mivel a rekordot_keres fv b�rmilyen t�pus� rekordot kaphat param�terk�nt ami szerepel a strukt�r�ban,
//az egyszer�bben �tl�that� k�d �rdek�ben a t�pusokhoz k�l�n f�ggv�nyt �rtam.

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

            //Ha megtal�lom a keresett rekordot, a db sz�m�t n�velem eggyel, �s a keresettet r��ll�tom
            //megtal�lt rekordra, majd visszal�pek a ciklusba, keresve egy, az adatot tartalmaz� rekord
            //k�vetkez� felbukkan�s�t.

        }
            //Ha t�bbsz�r szerepel az adat a strukt�r�ban, akkor azt jelezz�k a felhaszn�l�nak,
            //�j adattal t�rt�n� keres�sre h�vjuk fel.

        if(db>1) {

            printf("\nTobb talalat is van, probalja meg masik adattal.\n");
            return NULL;
        }
            //Ha probl�ma n�lk�l siker�lt megtal�lni a rekordot, visszaadjuk a c�m�t
        return keresett;
    }

//A t�bbi seg�df�ggv�ny ugyanezen elven m�k�dik, csup�n a t�pusuk m�s.

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

    //Ha a rekord nincs benne a list�nkban, NULL pointerrel t�r�nk vissza.

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
//Az elej�t **-al vessz�k �t, ugyanis a k�s�bbiekben lehet meg akarjuk
//v�ltoztatni, hogy mire mutat.

//A f�ggv�nynek nem kell visszaadnia semmit, ugyanis csak a list�ba f�z egy elemet.
void rekordot_beszur(Telefon **eleje, char *nev, char *foglalkozas, char *lakcim, char *telefonszam) {

    if(rekordot_keres(*eleje, szam, telefonszam) != NULL && strcmp(telefonszam, "-") != 0) {
        printf("%s: A szam mar letezik az adatbazisban.", telefonszam);
        return;
    }

    Telefon *uj;
    Telefon *mozgo;
    uj = (Telefon *) malloc(sizeof(Telefon));


    //Az �j rekord adataiba belem�solom a bek�rt param�tereket.

    strcpy(uj->nev, nev);
    strcpy(uj->foglalkozas, foglalkozas);
    strcpy(uj->lakcim, lakcim);
    strcpy(uj->szam, telefonszam);

    uj->kov = NULL;


    //Amennyiben nem l�tezik a lista, amit �tvett a f�ggv�ny, a bek�rt param�terekkel felt�lt�tt rekord lesz
    //az �j lista els� eleme.

    if (*eleje == NULL) {
        *eleje = uj;
    }

        //Ha l�tezik a megadott lista, akkor v�gigmegy rajta, �s a v�g�re besz�rja az �j l�trehozott rekordot.

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


        //Ha az els� elemet t�r�lj�k. Itt v�ltoztatjuk meg a helyet, amire
        //az eleje mutat, ez�rt kellett **-al jel�lni. Ilyenkor a f�ggv�ny megh�v�s�ban is
        //c�m szerint kell �tadni.

    else if (keresett == *eleje) {
        Telefon *ujeleje = (*eleje)->kov;
        free(*eleje);
        *eleje = ujeleje;

        return *eleje;
    }


        //Ha a k�zep�r�l vagy v�g�r�l t�rl�nk.
    else {
        Telefon *elozo=rekord_elotti(*eleje, tipus, adat);
        elozo->kov = keresett->kov;
        free(keresett);

        return *eleje;
    }

}

void struktura_felszabadit(Telefon **eleje) {

    //Az eleje pointer c�m�t akarjuk megv�ltoztatni,
    //ez�rt **-al kell �tadni.

    Telefon *mozgo = *eleje;

    while (mozgo != NULL) {
        Telefon *tmp = mozgo->kov;
        free(mozgo);
        mozgo = tmp;
    }
    *eleje = NULL;

}

bool wildcard_keres(char *input, char *keres){

    //Pointerek �rt�k�t n�zz�k, ha megtal�ltuk a k�t string v�g�t, akkor kil�p�nk igazzal.
    if (*input == '\0' && *keres == '\0')
        return true;

    //Megn�zz�k, hogy a '*' helye ut�n van-e m�g karakter a keres-ben.
    if (*input == '*' && *(input+1) != '\0' && *keres == '\0')
        return false;

    //Ha az inputban k�rd�jel van, vagy megegyeznek a karakterek, akkor mindkett�t l�ptetj�k.
    if (*input == '?' || *input == *keres)
        return wildcard_keres(input+1, keres+1);

    //Ha '*'-ot tal�lunk, akkor k�t lehet�s�g van:
    //1.: Vagy az inputot l�ptetj�k eggyel
    //2.: Vagy a kerest l�ptetj�k eggyel
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

