#ifndef DEPLACEMENTS_H_INCLUDED
#define DEPLACEMENTS_H_INCLUDED
#include "piece.h"
#include "partie.h"




int deplacement_valide_pion(partie_t *parite,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_tour(partie_t *partie,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_cavalier(partie_t *partie,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_fou(partie_t *partie,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_lance(partie_t *partie,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_ga(partie_t *partie,cr_t depart, cr_t arrive, int statut);
int deplacement_valide_roi(partie_t *partie,cr_t depart, cr_t arrive);
int deplacement_valide_go(partie_t *partie,cr_t depart, cr_t arrive);
int deplacement_valide( partie_t * partie,cr_t depart, cr_t arrive);
int deplacement_horizontale(cr_t depart,cr_t arrive);
int deplacement_verticale(cr_t depart,cr_t arrive);

#endif // DEPLACEMENTS_H_INCLUDED
