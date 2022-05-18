#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

piece_t piece_creer(int joueur, char type, int statut)
{
    piece_t x;
    x.joueur = joueur;
    x.type = type;
    x.statut = statut;
    return x;
}

int piece_joueur(piece_t x)
{
    return x.joueur;
}

piece_t piece_identifier(char lettre)
{
    piece_t x;
    switch(lettre){
    case 'p' : x.joueur = joueur1; x.type = 'p'; x.statut=NORMAL;
        break;

        case 'P' : x.joueur = joueur2; x.type = 'p'; x.statut=NORMAL;
        break;

        case 'l' : x.joueur = joueur1; x.type = 'l'; x.statut=NORMAL;
        break;

        case 'L' :x.joueur = joueur2; x.type = 'l'; x.statut=NORMAL;
        break;

        case 'n' : x.joueur = joueur1; x.type = 'c'; x.statut=NORMAL;
        break;

        case 'N' : x.joueur = joueur2; x.type = 'c'; x.statut=NORMAL;
        break;

        case 'b' : x.joueur = joueur1; x.type = 'f'; x.statut=NORMAL;
        break;

        case 'B' : x.joueur = joueur2; x.type = 'f'; x.statut=NORMAL;
        break;

        case 'r' : x.joueur = joueur1; x.type = 't'; x.statut=NORMAL;
        break;

        case 'R' : x.joueur = joueur2; x.type = 't'; x.statut=NORMAL;
        break;

        case 's' : x.joueur = joueur1; x.type = 'a'; x.statut=NORMAL;
        break;

        case 'S' : x.joueur = joueur2; x.type = 'a'; x.statut=NORMAL;
        break;

        case 'g' : x.joueur = joueur1; x.type = 'o'; x.statut=NORMAL;
        break;

        case 'G' : x.joueur = joueur2; x.type = 'o'; x.statut=NORMAL;
        break;

        case 'k' : x.joueur = joueur1; x.type = 'r'; x.statut=NORMAL;
        break;

        case 'K' : x.joueur = joueur2; x.type = 'r'; x.statut=NORMAL;
        break;

        case 'd' : x.joueur = joueur1; x.type = 'p'; x.statut=PROMU;
        break;

        case 'D' : x.joueur = joueur2; x.type = 'p'; x.statut=PROMU;
        break;

        case 'j' : x.joueur = joueur1; x.type = 'l'; x.statut=PROMU;
        break;

        case 'J' : x.joueur = joueur2; x.type = 'l'; x.statut=PROMU;
        break;

        case 'c' : x.joueur = joueur1; x.type = 'c'; x.statut=PROMU;
        break;

        case 'C' : x.joueur = joueur2; x.type = 'c'; x.statut=PROMU;
        break;

        case 'f' : x.joueur = joueur1; x.type = 'f'; x.statut=PROMU;
        break;

        case 'F' : x.joueur = joueur2; x.type = 'f'; x.statut=PROMU;
        break;

        case 't' : x.joueur = joueur1; x.type = 't'; x.statut=PROMU;
        break;

        case 'T' : x.joueur = joueur2; x.type = 't'; x.statut=PROMU;
        break;

        case 'a' : x.joueur = joueur1; x.type = 'a'; x.statut=PROMU;
        break;

        case 'A' : x.joueur = joueur2; x.type = 'a'; x.statut=PROMU;
        break;

        case '.' : x.joueur = 3; x.type = '.'; x.statut=NORMAL;
        break;

    }
    return x;
}

char piece_caractere(piece_t x)
{
    if(x.joueur == joueur1)
    {
        if (x.statut == NORMAL)
        {

            if(x.type == 'p')
            {
                return 'p';
            }
            else if(x.type == 'l')
            {
                return 'l';
            }
            else if(x.type == 'c')
            {
                return 'n';
            }
            else if(x.type == 'f')
            {
                return 'b';
            }
            else if(x.type == 't')
            {
                return 'r';
            }
            else if(x.type == 'a')
            {
                return 's';
            }
            else if(x.type == 'o')
            {
                return 'g';
            }
            else if(x.type == 'r')
            {
                return 'k';
            }
        }
        else
        {
            if(x.type == 'p')
            {
                return 'd';
            }
            else if(x.type == 'l')
            {
                return 'j';
            }
            else if(x.type == 'c')
            {
                return 'v';
            }
            else if(x.type == 'f')
            {
                return 'f';
            }
            else if(x.type == 't')
            {
                return 't';
            }
            else if(x.type == 'a')
            {
                return 'a';
            }
            else if(x.type == 'o')
            {
                return 'g';
            }
            else if(x.type == 'r')
            {
                return 'k';
            }
        }
    }
    if(x.joueur == joueur2)
    {
        if (x.statut == NORMAL)
        {

            if(x.type == 'p')
            {
                return 'P';
            }
            else if(x.type == 'l')
            {
                return 'L';
            }
            else if(x.type == 'c')
            {
                return 'N';
            }
            else if(x.type == 'f')
            {
                return 'B';
            }
            else if(x.type == 't')
            {
                return 'R';
            }
            else if(x.type == 'a')
            {
                return 'S';
            }
            else if(x.type == 'o')
            {
                return 'G';
            }
            else if(x.type == 'r')
            {
                return 'K';
            }
        }
        else
        {
            if(x.type == 'p')
            {
                return 'D';
            }
            else if(x.type == 'l')
            {
                return 'J';
            }
            else if(x.type == 'c')
            {
                return 'C';
            }
            else if(x.type == 'f')
            {
                return 'F';
            }
            else if(x.type == 't')
            {
                return 'T';
            }
            else if(x.type == 'a')
            {
                return 'A';
            }
            else if(x.type == 'o')
            {
                return 'G';
            }
            else if(x.type == 'r')
            {
                return 'K';
            }
        }
    } return '.';
}

void piece_afficher(piece_t x)
{
    if(x.joueur == joueur1)
    {
        if (x.statut == NORMAL)
        {

            if(x.type == 'p')
            {

                printf("p");
            }
            else if(x.type == 'l')
            {
                printf("l");
            }
            else if(x.type == 'c')
            {
                printf("n");
            }
            else if(x.type == 'f')
            {
                printf("b");
            }
            else if(x.type == 't')
            {
                printf("r");
            }
            else if(x.type == 'a')
            {
                printf("s");
            }
            else if(x.type == 'o')
            {
                printf("g");
            }
            else if(x.type == 'r')
            {
                printf("k");
            }
        }
        else
        {
            if(x.type == 'p')
            {
                printf("d");
            }
            else if(x.type == 'l')
            {
                printf("j");
            }
            else if(x.type == 'c')
            {
                printf("v");
            }
            else if(x.type == 'f')
            {
                printf("f");
            }
            else if(x.type == 't')
            {
                printf("t");
            }
            else if(x.type == 'a')
            {
                printf("a");
            }
            else if(x.type == 'o')
            {
                printf("g");
            }
            else if(x.type == 'r')
            {
                printf("k");
            }
        }
    }
    if(x.joueur == joueur2)
    {
        if (x.statut == NORMAL)
        {

            if(x.type == 'p')
            {
                printf("P");
            }
            else if(x.type == 'l')
            {
                printf("L");
            }
            else if(x.type == 'c')
            {
                printf("N");
            }
            else if(x.type == 'f')
            {
                printf("B");
            }
            else if(x.type == 't')
            {
                printf("R");
            }
            else if(x.type == 'a')
            {
                printf("S");
            }
            else if(x.type == 'o')
            {
                printf("G");
            }
            else if(x.type == 'r')
            {
                printf("K");
            }
        }
        else
        {
            if(x.type == 'p')
            {
                printf("D");
            }
            else if(x.type == 'l')
            {
                printf("J");
            }
            else if(x.type == 'c')
            {
                printf("C");
            }
            else if(x.type == 'f')
            {
                printf("F");
            }
            else if(x.type == 't')
            {
                printf("T");
            }
            else if(x.type == 'a')
            {
                printf("A");
            }
            else if(x.type == 'o')
            {
                printf("G");
            }
            else if(x.type == 'r')
            {
                printf("K");
            }
        }
    }
}
