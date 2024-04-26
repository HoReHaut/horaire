#include <stdio.h>
#include <time.h>

typedef struct {
    int jourDebut;
    int heureOuverture;
    int minuteOuverture;
    int heureFermeture;
    int minuteFermeture;
} Horaire;

//Horaires d'ouverture
Horaire horaires[] = {
    {1, 8, 0, 16, 0},  //Lundi
    {3, 8, 0, 16, 0},  //Mercredi
    {5, 8, 0, 16, 0},  //Vendredi
    {2, 8, 0, 12, 0},  //Mardi matin
    {4, 8, 0, 12, 0},  //Jeudi matin
    {6, 8, 0, 12, 0},  //Samedi matin
    {2, 14, 0, 18, 0}, //Mardi après-midi
    {4, 14, 0, 18, 0}  //Jeudi après-midi
};

//Vérifie si le magasin est ouvert
int IsOpenOn(struct tm date) {
    for (int i = 0; i < sizeof(horaires) / sizeof(Horaire); i++) {
        Horaire h = horaires[i];
        if (date.tm_wday == h.jourDebut) {
            if ((date.tm_hour > h.heureOuverture || (date.tm_hour == h.heureOuverture && date.tm_min >= h.minuteOuverture)) &&
                (date.tm_hour < h.heureFermeture || (date.tm_hour == h.heureFermeture && date.tm_min < h.minuteFermeture))) {
                return 1; //Ouvert
            }
        }
    }
    return 0; //Fermé
}

//Trouve la prochaine date d'ouverture
struct tm NextOpeningDate(struct tm date) {
    date.tm_min++; //Commence à la minute suivante
    while (1) {
        mktime(&date); //Normalise la date après modif
        if (IsOpenOn(date)) {
            return date;
        }
        date.tm_min++;
    }
}

int main() {
    struct tm date = { .tm_year = 124, .tm_mon = 1, .tm_mday = 22, .tm_hour = 14, .tm_min = 45, .tm_wday = 2 };

    if (IsOpenOn(date)) {
        printf("Le magasin est ouvert.\n");
    } else {
        printf("Le magasin est fermé.\n");
    }

    struct tm nextOpenDate = NextOpeningDate(date);
    printf("Le magasin sera ouvert le : %04d-%02d-%02d %02d:%02d\n",
           nextOpenDate.tm_year + 1900,
           nextOpenDate.tm_mon + 1,
           nextOpenDate.tm_mday,
           nextOpenDate.tm_hour,
           nextOpenDate.tm_min);

    return 0;
}