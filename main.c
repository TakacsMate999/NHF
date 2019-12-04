#include <stdio.h>
#include "debugmalloc.h"
#include "fajlkezeles.h"
#include "adatkezeles.h"
#include "menu.h"
#include <ctype.h>

int main() {



    menut_kiir();
    bool run = true;
    char parancs;
    int valasz;
    Telefon *eleje = NULL;

    while (run) {

        scanf("%c", &parancs);
        switch (parancs) {
            case '0':
                menut_kiir();
                break;
            case '1':
                printf("-o-o-o Telefonkonyv beolvasasa -o-o-o\n");
                printf("Adja meg a fajl nevet! (Maximum 64 karakter)\n");
                char fajlnev[65];

                scanf("%s", fajlnev);
                struktura_felszabadit(&eleje);
                eleje = fajl_bemasol(fajlnev);

                if (eleje == NULL)
                    printf("Sikertelen beolvasas!\n");
                else
                    printf("Sikeres beolvasas!\n");
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '2':
                printf("-o-o-o Telefonkonyv kiirasa -o-o-o\n");
                struktura_kiir(eleje);
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '3':
                printf("-o-o-o Rekord beszurasa -o-o-o\n");
                char nev[51];
                char foglalkozas[128];
                char lakcim[128];
                char szam[12];

                rekordot_beolvas_3(nev, foglalkozas, lakcim, szam);
                rekordot_beszur(&eleje, nev, foglalkozas, lakcim, szam);
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '4':
                printf("-o-o-o Rekord modositasa -o-o-o\n(Egy rekord modositasahoz szukseges megadni a"
                       " rekord egyik adattipusat, es az ahhoz tartozo regi, kicserelesre varo adatot, illetve az uj kivant adatot.)\n");

                char regiadat[128];
                char ujadat[128];

                printf("Valasszon adattipust!");
                printf("\n(nev = 0, foglalkozas = 1, lakcim = 2, telefonszam = 3)\n");
                scanf("%d", &valasz);
                if (valasz >= 0 && valasz <= 3) {
                    printf("Regi adat:");
                    fgets(regiadat, 128, stdin);
                    fgets(regiadat, 128, stdin);
                    printf("Uj adat:");
                    fgets(ujadat, 128, stdin);

                    sorvege_torol(regiadat);
                    sorvege_torol(ujadat);

                    if (rekordot_modosit(eleje, valasz, regiadat, ujadat) == NULL)
                    printf("A rekord nem talalhato.\n");
                    else
                        printf("Sikeres modositas.\n");
                }
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '5':
                printf("-o-o-o Rekord torlese -o-o-o\n(Egy rekord torlesehez meg kell adni egy tipusat, valamint az ahhoz a tipushoz tartozo adatat.)\n");
                char adat[128];

                printf("Valasszon adattipust!");
                printf("\n(nev = 0, foglalkozas = 1, lakcim = 2, telefonszam = 3)\n");

                scanf("%d", &valasz);
                if (valasz >= 0 && valasz <= 3) {
                    printf("Hozza tartozo adat:");
                    fgets(adat, 128, stdin);
                    fgets(adat, 128, stdin);

                    sorvege_torol(adat);
                    if(rekordot_torol(&eleje, valasz, adat) == NULL)
                        printf("Sikertelen torles.\n");
                    else
                        printf("Sikeres torles.\n");
                }
                else
                    printf("Nem letezo tipus.\n");
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '6':
                printf("-o-o-o Osszes rekord torlese -o-o-o\n");
                printf("Biztosan torolni kivanja a telefonkonyvet?(Igen = 0, Nem = 1)\n");
                scanf("%d", &valasz);
                if(valasz == 0){
                    struktura_felszabadit(&eleje);
                    if(eleje == NULL)
                        printf("Sikeres torles.\n");
                }
                else
                    printf("Torles meghiusult.\n");
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '7':
                printf("-o-o-o Fajlba iras -o-o-o\nMi legyen a fajl neve? (.txt, .vcf kiterjesztesek lehetsegesek.)\n");
                char ujfajl[65];
                char kiterjesztes[5];
                char fadat[128];

                scanf("%s", ujfajl);
                kiterjesztes_keres(ujfajl, kiterjesztes);
                if(strcmp(kiterjesztes, "txt") == 0) {
                    if(eleje == NULL)
                        printf("Ures telefonkonyv, sikertelen fajlbairas.\n");
                    else {
                        printf("Sikeres fajlba iras.\n");
                        fajlba_iras(ujfajl, eleje);
                    }
                }
                else if(strcmp(kiterjesztes, "vcf") == 0) {
                    printf("Rekord vCard formatumba mentesehez szukseges az egyik tipusa, es a hozza tartozo adata\n");
                    printf("Valasszon adattipust!");
                    printf("\n(nev = 0, foglalkozas = 1, lakcim = 2, telefonszam = 3)\n");

                    scanf("%d", &valasz);
                    if (valasz >= 0 && valasz <= 3) {
                        printf("Hozza tartozo adat:");
                        fgets(fadat, 128, stdin);
                        fgets(fadat, 128, stdin);

                        sorvege_torol(fadat);
                        if(rekordot_keres(eleje, valasz, fadat) == NULL)
                            printf("Nem talalhato rekord, sikertelen fajlbairas.\n");
                        else {
                            fajlba_iras_vcf(eleje, ujfajl, valasz, fadat);
                            printf("Sikeres fajlba iras.\n");
                        }

                    }
                    else
                        printf("Nem letezo tipus.\n");
                }

                else
                    printf("Hibas kiterjesztes lett megadva.\n");
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");

                break;

            case '8':
                printf("-o-o-o Wildcard kereses (?,*) -o-o-o\nA kereseshez szukseges megadni az adat tipusat!\n");
                char wildcard_adat[128];
                printf("Valasszon adattipust!");
                printf("\n(nev = 0, foglalkozas = 1, lakcim = 2, telefonszam = 3)\n");

                scanf("%d", &valasz);
                if (valasz >= 0 && valasz <= 3) {
                    printf("Hozza tartozo adat:");
                    fgets(wildcard_adat, 128, stdin);
                    fgets(wildcard_adat, 128, stdin);

                    sorvege_torol(wildcard_adat);

                    wildcard_kiir(eleje, valasz, wildcard_adat);

                    }
                else
                    printf("Nem letezo tipus.\n");
                printf("\nMenu meghivasahoz nyomja meg a '0' gombot.\n");
                break;

            case '9':
                run = false;
                printf("A fajl bezarasa.\n");
                break;
            default:
                if (isdigit(parancs))
                    printf("Ismeretlen parancs\n");
                break;


        }
    }

    struktura_felszabadit(&eleje);

    return 0;
}
