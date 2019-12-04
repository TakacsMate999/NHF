#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <string.h>
/*!
 * @brief Kiírja a menüt
 */
void menut_kiir(void);

/*!
 * @brief Adatok bekérésénél leszedi a sor vége jelet, és '\0'-t tesz a helyére. Az fgets() függvénnyel történő adatbekérés miatt szükséges.
 * @param adat
 */
void sorvege_torol(char *adat);
/*!
 * @brief Beolvassa az adatokat, a paraméterként megadott karaktertömbökben tárolja azokat.
 */
void rekordot_beolvas_3(char *nev, char *foglalkozas, char *lakcim, char *szam);


#endif // MENU_H_INCLUDED
