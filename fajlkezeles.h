#ifndef FAJLKEZELES_H_INCLUDED
#define FAJLKEZELES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adatkezeles.h"


typedef enum Siker{
    sikeres,
    sikertelen
}Siker;

/*!
 * @brief Bemásolja a fájl tartalmát a struktúrába. A program feltételezi, hogy a telefonkönyv felépítése a nev/fogalkozas/lakcim/szam/ normáknak megfelel.
 * @param string
 * @return A létrehozott láncolt lista elejére mutató pointer
 */
Telefon *fajl_bemasol(char *string);

/*!
 * @brief a fajlba_iras és a fajlba_iras_vcf segédfüggvénye. Megkeresi a felhasználó által megadott fájlnév kívánt kiterjesztését, majd azt beletölti a kiterjesztés tömbbe.
 * @param fajlnev
 * @param kiterjesztes
 */
void kiterjesztes_keres(char* fajlnev, char *kiterjesztes);
/*!
 * @brief txt fájlba írja a láncolt lista adatait.
 * @param string
 * @param eleje
 * @return Sikeresség enum
 */
Siker fajlba_iras(char *string, Telefon *eleje);

/*!
 * @brief Egy rekord vCard formátumú mentése
 * @param eleje Láncolt lista eleje
 * @param fajlnev
 * @param tipus Rekord egyik adatának típusa
 * @param adat Típushoz tartozó adat
 */
Siker fajlba_iras_vcf(Telefon *eleje, char *fajlnev, Tipusok tipus, char *adat);



#endif // FAJLKEZELES_H_INCLUDED
