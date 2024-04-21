#include <stdio.h>
#include <time.h>

//Fonction pour vérifier si le magasin est ouvert
int isOpen(int jour, int heure, int minute) {
    //Horaires d'ouverture
    if ((jour == 1 || jour == 3 || jour == 5) && (heure >= 8 && heure < 16)) {  //Lundi, Mercredi, Vendredi
        return 1;  //Ouvert
    }
    if ((jour == 2 || jour == 4 || jour == 6) && ((heure >= 8 && heure < 12) || (heure >= 14 && heure < 18))) {  //Mardi, Jeudi, Samedi
        return 1;  //Ouvert
    }
    return 0;  //Fermé
}

int main() {
    struct tm date = {.tm_year=124, .tm_mon=1, .tm_mday=22, .tm_hour=14, .tm_min=45, .tm_wday=2}; //Date

    if (isOpen(date.tm_wday, date.tm_hour, date.tm_min)) {
        printf("Le magasin est ouvert.\n");
    } else {
        printf("Le magasin est fermé.\n");
    }

    return 0;
}