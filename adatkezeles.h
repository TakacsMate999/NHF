#ifndef ADATKEZELES_H_INCLUDED
#define ADATKEZELES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum Tipusok{
    nev =0,
    foglalkozas=1,
    lakcim=2,
    szam=3,
    nincs=4
}Tipusok;
//!
typedef struct Telefon{//! név
    char nev[51];
    char foglalkozas[128];
    char lakcim[128];
    char szam[12];
    struct Telefon  *kov;
}Telefon;

void struktura_kiir(Telefon *eleje);
/*!
 * @brief Megvizsgálja, hogy létezik-e ilyen típus
 * @param tipus
 * @return A Tipusok enum-ból adja vissza a talált értéket.
 */
Tipusok tipus_keres(char *tipus);


/*!
 * @brief Beszúr egy rekordot a láncolt listába. Ha eddig üres volt, akkor létrehozza azt.
 * @param [in,out] eleje A lista eleje
 * @param nev
 * @param foglalkozas
 * @param lakcim
 * @param szam
 */
void rekordot_beszur(Telefon **eleje, char* nev, char *foglalkozas, char*lakcim, char *szam);

/*!
 * @brief Felszabadítja a láncolt listát.
 * @param eleje
 */
void struktura_felszabadit(Telefon **eleje);

/*!
 * @brief rekordot_keres segédfüggvénye, 'nev' típus esetén visszaadja a keresett rekordra mutató pointert.
 * @param [in,out] eleje
 * @param adat
 * @return A keresettre mutató pointer
 */
static Telefon *rekordot_keres_nev(Telefon *eleje, char *adat);
/*!
 * @brief rekordot_keres segédfüggvénye, 'foglalkozas' típus esetén visszaadja a keresett rekordra mutató pointert.
 * @param [in,out] eleje
 * @param adat
 * @return A keresettre mutató pointer
 */
static Telefon *rekordot_keres_foglalkozas(Telefon *eleje, char *adat);

/*!
 * @brief rekordot_keres segédfüggvénye, 'lakcim' típus esetén visszaadja a keresett rekordra mutató pointert.
 * @param [in,out] eleje
 * @param adat
 * @return A keresettre mutató pointer
 */
static Telefon *rekordot_keres_lakcim(Telefon *eleje, char *adat);

/*!
 * @brief rekordot_keres segédfüggvénye, 'szam' típus esetén visszaadja a keresett rekordra mutató pointert.
 * @param eleje
 * @param adat
 * @return A keresettre mutató pointer
 */
static Telefon *rekordot_keres_szam(Telefon *eleje, char *adat);

/*!
 * @brief Megkeres egy rekordot a listában.
 * @param [in,out] eleje
 * @param tipus Az adat típusa
 * @param adat
 * @return A keresettre mutató pointer
 */
Telefon *rekordot_keres(Telefon *eleje, Tipusok tipus, char *adat);

/*!
 * @brief rekordot_torol segédfüggvénye, a rekordot_keres függvény visszatérési értéke előtti rekord helyét adja vissza.
 * @param [in,out] eleje
 * @param tipus Az adat típusa
 * @param adat
 * @return A keresett előttire mutató pointer
 */
Telefon *rekord_elotti(Telefon *eleje, Tipusok tipus, char *adat);
/*!
 * @brief Egy rekord egyik adatát módosítja
 * @param [in,out] eleje
 * @param tipus Az adat típusa
 * @param regiadat Megváltoztatandó adat.
 * @param ujadat Új adat.
 * @return A lista eleje
 */
Telefon *rekordot_modosit(Telefon *eleje, Tipusok tipus, char *regiadat, char *ujadat);

/*!
 * @brief Töröl egy rekordot a listából, kezeli azt is, ha az első rekord a törlendő.
 * @param [in,out] eleje
 * @param tipus A törlendő rekord egyik típusa
 * @param adat A hozzá tartozó adata
 * @return A lista eleje
 */
Telefon *rekordot_torol(Telefon **eleje, Tipusok tipus, char *adat);

/*!
 * @brief Wildcard keresőfüggvény, összehasonlítja két string karaktereit, majd rekurzívan lépteti előre azokat. Ha az inputban '?' szerepel, akkor az bármilyen karaktert képes helyettesíteni, tehát lépteti mindkét pointert. Ha az inputban '*' van, akkor vagy az inputot léptetjük eggyel, vagy a másik stringet. Visszatérési értéke akkor lesz igaz, ha mindkét string eljut a '\0'-ra, tehát "egyeznek".
 * @param input Felhasználó által megadott string
 * @param keres A használatban ezek majd a láncolt lista elemei lesznek.
 * @return True / False
 */
bool wildcard_keres(char *input, char *keres);

/*!
 * @brief wildcard_kiir segédfüggvénye 'nev' típus esetén. Ha a wildcard_keres függvény egyezést talál, kiíratja a rekord típushoz tartozó adatát.
 * @param eleje A lista eleje
 * @param input A felhasználó által megadott string
 */
void wildcard_kiir_nev(Telefon *eleje, char *input);

/*!
 * @brief wildcard_kiir segédfüggvénye 'foglalkozas' típus esetén. Ha a wildcard_keres függvény egyezést talál, kiíratja a rekord típushoz tartozó adatát.
 * @param eleje A lista eleje
 * @param input A felhasználó által megadott string
 */
void wildcard_kiir_foglalkozas(Telefon *eleje, char *input);

/*!
 * @brief wildcard_kiir segédfüggvénye 'lakcim' típus esetén. Ha a wildcard_keres függvény egyezést talál, kiíratja a rekord típushoz tartozó adatát.
 * @param eleje A lista eleje
 * @param input A felhasználó által megadott string
 */
void wildcard_kiir_lakcim(Telefon *eleje, char *input);

/*!
 * @brief wildcard_kiir segédfüggvénye 'szam' típus esetén. Ha a wildcard_keres függvény egyezést talál, kiíratja a rekord típushoz tartozó adatát.
 * @param eleje A lista eleje
 * @param input A felhasználó által megadott string
 */
void wildcard_kiir_szam(Telefon *eleje, char *input);

/*!
 * @brief Végigmegy a láncolt listán, és amennyiben a wildcard keresés egyezést talált, kiíratja a rekord adatait.
 * @param eleje A lista eleje
 * @param tipus Az adat típusa
 * @param input A felhasználó által megadott string
 */
void wildcard_kiir(Telefon *eleje, Tipusok tipus, char *input);



#endif // ADATKEZELES_H_INCLUDED
