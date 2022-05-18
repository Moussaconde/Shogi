#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED
#define joueur1 1
#define joueur2 2
#define PROMU 1
#define NORMAL 0

struct piece_s
{
    int joueur;
    char type;
    int statut;
};

typedef struct piece_s piece_t;

piece_t piece_creer(int joueur, char type, int statut);
int piece_joueur(piece_t x);
piece_t piece_identifier(char lettre);
char piece_caractere(piece_t x);
void piece_afficher(piece_t x);

#endif // PIECE_H_INCLUDED
