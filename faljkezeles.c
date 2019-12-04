
#include "fajlkezeles.h"
#include "debugmalloc.h"


Telefon* fajl_bemasol(char *string){

    FILE *fp=fopen(string, "r");
    if(fp == NULL){
        fclose(fp);
        return NULL;
    }

    char egy[51], ketto[128], harom[128], negy[12];
    Telefon *eleje = NULL;



    //Ahhoz, hogy a fájl végét megtaláljam, létrehoztam egy buffert, aminek a mérete megegyezik a négy tömböm méretének összegével,
    //így elegendõ az aktuális sorokkal foglalkoznom, melyeket elhelyezek a segédtömbjeimben.

    char buf[323];
    while (fgets(buf,323,fp ) != NULL) {
        sscanf(buf, "%[^/]/%[^/]/%[^/]/%[^/]", egy, ketto, harom, negy);

        rekordot_beszur(&eleje, egy, ketto, harom, negy);

    }

    fclose(fp);
    return eleje;
}

void kiterjesztes_keres(char *fajlnev, char *kiterjesztes) {
    int index=0;
    for(int i=0; fajlnev[i] != '\0'; i++){
        if(fajlnev[i] == '.')
            index = i;
    }
    //Fajlnev pointerhez hozzaadjuk a legutolso megtalált '.'-nak a helyet +1 (a pont ne legyen benne), igy az mar a kiterjesztesre fog mutatni.
    strcpy(kiterjesztes, fajlnev+index+1);
}

Siker fajlba_iras(char *string, Telefon *eleje){

    FILE *fp=fopen(string, "wt");
    if(fp == NULL)
        return sikertelen;

    Telefon *mozgo = eleje;

    while(mozgo != NULL){

        fprintf(fp,"%s/%s/%s/%s/\n",mozgo->nev, mozgo->foglalkozas, mozgo->lakcim, mozgo->szam);
        mozgo = mozgo->kov;
    }
    fclose(fp);
    return sikeres;
}



Siker fajlba_iras_vcf(Telefon *eleje, char *fajlnev, Tipusok tipus, char *adat) {

    FILE *fp=fopen(fajlnev, "w");
    if(fp == NULL)
        return sikertelen;

    Telefon *keresett = rekordot_keres(eleje, tipus, adat);
    if(keresett == NULL)
        return sikertelen;

    char firstname[64];
    char surname[64];
    int idx=0;
    int j=0;


    for(int i=0; keresett->nev[i] != ' '; i++){
        surname[i]=keresett->nev[i];
        idx=i;
    }
    surname[idx+1]='\0';

    //Azért kell az idx-hez 2-t adni, hogy a ' ' ne kerüljön be a firstname elé
    for(int i=idx+2; i<=strlen(keresett->nev); i++){
        firstname[j]=keresett->nev[i];
        j++;
        idx=i;
    }
    firstname[idx+1]='\0';

    fprintf(fp, "BEGIN:VCARD\n");
    fprintf(fp, "VERSION:2.1\n");
    fprintf(fp, "N:%s;%s\n", firstname, surname);
    fprintf(fp, "ORG:%s\n",keresett->foglalkozas);
    fprintf(fp, "TEL;HOME:%s\n", keresett->szam);
    fprintf(fp, "ADR;HOME:;;%s\n", keresett->lakcim);
    fprintf(fp, "END:VCARD\n");

    fclose(fp);
    return sikeres;
}




