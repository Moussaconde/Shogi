#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED
#include "piece.h"
#define OUI 1
#define NON 0
#if defined (WIN32)
#   define EFFACER_ECRAN() system("cls")
#elif defined (__linux)
#   define EFFACER_ECRAN() system("clear")
#else
#   error "Impossible d'effacer le terminal sur cette plateforme !"
#endif // defined

struct cr_s
{
    int x;
    int y;
};
typedef struct cr_s cr_t;

struct coup_s
{
    struct coup_s * coup_suiv;
    struct coup_s * coup_prec;
    cr_t depart;
    cr_t arrive;
    int promotion;
    int capture;
};

typedef struct coup_s coup_t;

struct ldc_s
{
    unsigned int nb;
    struct coup_s *coup_fin;
    struct coup_s *coup_debut;
};

typedef struct ldc_s ldc_t;

struct partie_s{

    char tablier[11][11];
    ldc_t ldc;
    int joueur;
};
typedef struct partie_s partie_t;


cr_t coor(int x, int y);
int comp_coor(cr_t cr1, cr_t cr2);
void init_tablier(partie_t* partie);
int case_vide (partie_t p,cr_t c);
void modifier_case (partie_t *x, piece_t y,cr_t c);
void changer_joueur (partie_t *x);
void afficher_plateau (partie_t *x);
void deplacement(partie_t *p,cr_t depart,cr_t arriver);
void annuler_deplacement(partie_t *partie);
cr_t saisie_case();
partie_t *partie_creer();
void partie_detruire(partie_t *partie);
void partie_sauvegarder(partie_t *partie,char *chaine);
partie_t *partie_charger(char *chaine);
partie_t *partie_nouvelle();
void partie_jouer(partie_t *p);
partie_t *replay_charger(char *chaine);
void replay_jouer(partie_t partie);



#endif // PARTIE_H_INCLUDED
