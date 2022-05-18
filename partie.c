#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partie.h"
#include "piece.h"

cr_t coor(int x, int y)  /* fonction pour creer des coordonnees */
{
    cr_t a;
    a.x=x;
    a.y=y;
    return a;
}

int comp_coor(cr_t cr1, cr_t cr2)  /* fonction de comparaison de coordonnees */
{
    if (cr1.x == cr2.x && cr2.y == cr2.y)
    {
        return 1;
    }
    else return 0;

}
void init_tablier(partie_t* partie) /* initialisation du tablier */
{
    int i,j;
    for (j=0;j<=10;j++)
    {
        for (i=0;i<=10;i++)
        {
            partie->tablier[j][i]='.';
            if (j==1)
            {
                if((i==1) || (i==9))
                    partie->tablier[j][i]='L';
                if((i==2) || (i==8))
                    partie->tablier[j][i]='N';
                if ((i==3) || (i==7))
                    partie->tablier[j][i]='S';
                if ((i==4) || (i==6))
                    partie->tablier[j][i]='G';
                if ((i==5))
                    partie->tablier[j][i]='K';
            }
            if (j==2)
            {
                if ((i==2))
                    partie->tablier[j][i]='R';
                if ((i==8))
                    partie->tablier[j][i]='B';
            }
            if ((j==3) &&  (i != 10) && (i != 0))
            {
                partie->tablier[j][i]='P';
            }

            /********************JOUEUR1***********************/

            if (j==9)
            {
                if((i==1) || (i==9))
                    partie->tablier[j][i]='l';
                if((i==2) || (i==8))
                    partie->tablier[j][i]='n';
                if ((i==3) || (i==7))
                    partie->tablier[j][i]='s';
                if ((i==4) || (i==6))
                    partie->tablier[j][i]='g';
                if ((i==5))
                    partie->tablier[j][i]='k';
            }
            if (j==8)
            {
                if ((i==2))
                    partie->tablier[j][i]='b';
                if ((i==8))
                    partie->tablier[j][i]='r';
            }
            if ((j==7) &&  (i != 10) && (i != 0))
            {
                partie->tablier[j][i]='p';
            }
            if (((j==0) && (i==10)) || ((j==10) && (i==0)))
            {
                partie->tablier[j][i]='§';
            }

        }
    }
}

void ajouter_coup(ldc_t *ldc, coup_t *coup)
{
    coup->coup_suiv=NULL;

    if (ldc->nb == 0)           /* On vérifie si notre liste a été allouée */
    {                           /* On mets à jour les donnés du coup*/
        ldc->coup_debut=coup;
        ldc->coup_fin=coup;
        coup->coup_prec=NULL;


    }
    else if(ldc->nb > 0 )
    {
        coup->coup_prec=ldc->coup_fin;
        ldc->coup_fin=coup;

    }

    ldc->nb++;
}

int case_vide(partie_t p, cr_t c)  /* On verifie si la case est vide */
{
	if (p.tablier[c.x][c.y]== '.' )
        return OUI;                     /* Si elle est vide retourne 1 */
	else
            return NON;
}

void modifier_case(partie_t *partie, piece_t piece, cr_t c) /* modifie la case du tablier */
{
	partie->tablier[c.x][c.y] = piece.type;
}

void changer_joueur(partie_t *partie)   /* Changer le tour du joueur suivant */
{
    if(partie->joueur==joueur1)
    {
        partie->joueur=joueur2;
        system("color f0");             /* fonction de couleur pour le joueur 2 */
    }
    else
    {
        partie->joueur=joueur1;
        system("color 4f");             /* fonction de couleur pour le joueur 1 */
    }

}

void afficher_plateau(partie_t *partie)  /* Affiche le tablier */
{
	int i,j,k;

        printf("                ");

	for(k=0; k<11; k++)
	{
        printf(" %2d",k);
	}
        printf("  Y\n");

	for(i=0; i<11; i++)
	{
		for(j=0; j<11; j++)
		{
		    if (j==0)
                printf("               %2d ",i);
                printf("%c  ", partie->tablier[i][j]);

            if ((i-3)<1 && (i!=0)  && (j==10))
                printf(" <~~ PLAYER 2 ");           /* Zone du joueur 2 */

            if ((i!=10) && (i>6)  && (j==10))
                printf(" <~~ PLAYER 1 ");              /* Zone du joueur 1 */
		}
		printf("\n");
	}
	printf("                X\n\n");
}


void deplacement(partie_t *partie, cr_t depart, cr_t arrive)  /*Fonction de deplacment */
{
    char tmp, chat;                                             /* Coordonnees des reserves */
    cr_t reserve;                                               /* Piece capturer va dans la reserve */
    int capture;                                                   /* Capture une piece */
    int promotion = NORMAL;
    coup_t *coup = malloc(sizeof(coup_t));
    piece_t pmt;
    piece_t promo;


    if (!case_vide(*partie, arrive))
    {
        capture = OUI;
        tmp = partie->tablier[arrive.x][arrive.y];
        partie->tablier[arrive.x][arrive.y] = partie->tablier[depart.x][depart.y];
        partie->tablier[depart.x][depart.y] = '.';
        if(arrive.x <= 3 && partie->joueur == joueur1 && piece_identifier(partie->tablier[arrive.x][arrive.y]).statut != PROMU)
        {
            printf("Voulez-vous etre promu ? (o/n) \n");
            scanf("  %c", &chat);
            if (chat == 'o')
            {
              promotion = PROMU;
              promo = piece_identifier(partie->tablier[arrive.x][arrive.y]);
              promo.statut = PROMU;
              partie->tablier[arrive.x][arrive.y] = piece_caractere(promo);

            }


            else if (chat == 'n') promotion = NORMAL;
        }
        else if (arrive.x >= 7 && partie->joueur == joueur2 && piece_identifier(partie->tablier[arrive.x][arrive.y]).statut != PROMU)
        {
            printf("Voulez-vous etre promu ? (o/n) \n");
            scanf("  %c", &chat);
            if (chat == 'o')
            {
              promotion = PROMU;
              promo = piece_identifier(partie->tablier[arrive.x][arrive.y]);
              promo.statut = PROMU;
              partie->tablier[arrive.x][arrive.y] = piece_caractere(promo);
            }
            else if (chat == 'n') promotion = NORMAL;

        }

        pmt = piece_identifier(tmp);
         if (pmt.joueur==joueur1)
        {
            reserve.x = 0;
            reserve.y = 9;
        } else if (pmt.joueur==joueur2)
        {
            reserve.x = 10;
            reserve.y = 1;
        }


        if(pmt.joueur==joueur1)
        {

            while ((case_vide(*partie,reserve) == NON) && (reserve.y != 0))
            {
                reserve.y--;
            }
            while ((case_vide(*partie,reserve) == NON) && (reserve.x != 9) && (reserve.y != 9))
            {
                reserve.x++;
            }

            partie->tablier[reserve.x][reserve.y] = tmp;
            reserve.x = 0;
            reserve.y = 9;

        } else if(pmt.joueur==joueur2)
            {
            while ((case_vide(*partie,reserve) == NON) && (reserve.y != 10))
            {
                reserve.y++;
            }
            while ((case_vide(*partie,reserve) == NON) && (reserve.x != 1) && (reserve.y == 10))
            {
                reserve.x--;
            }
            partie->tablier[reserve.x][reserve.y] = tmp;
                reserve.x = 10;
                reserve.y = 1;
            }


    }
    else
    {
        capture = NON;
        partie->tablier[arrive.x][arrive.y] = partie->tablier[depart.x][depart.y];
        partie->tablier[depart.x][depart.y] = '.';
        if(arrive.x <= 3 && partie->joueur == joueur1 && piece_identifier(partie->tablier[arrive.x][arrive.y]).statut != PROMU)
        {
            printf("Voulez-vous etre promu ? (o/n) \n");
            scanf("  %c", &chat);
            if (chat == 'o')
            {
              promotion = PROMU;
              promo = piece_identifier(partie->tablier[arrive.x][arrive.y]);
              promo.statut = PROMU;
              partie->tablier[arrive.x][arrive.y] = piece_caractere(promo);

            }
            else if (chat == 'n') promotion = NORMAL;
        }
        else if (arrive.x >= 7 && partie->joueur == joueur2 && piece_identifier(partie->tablier[arrive.x][arrive.y]).statut != PROMU)
        {
            printf("Voulez-vous etre promu ? (o/n) \n");
            scanf("  %c", &chat);
            if (chat == 'o')
            {
              promotion = PROMU;
              promo = piece_identifier(partie->tablier[arrive.x][arrive.y]);
              promo.statut = PROMU;
              partie->tablier[arrive.x][arrive.y] = piece_caractere(promo);
            }
            else if (chat == 'n') promotion = NORMAL;

        }

    }
    coup->depart=depart;
    coup->arrive=arrive;
    coup->capture=capture;
    coup->promotion = promotion;
    ajouter_coup(&partie->ldc,coup);
}

void annuler_deplacement(partie_t *partie)
{
    coup_t *cop = partie->ldc.coup_fin;

    piece_t promo;

    cr_t avant;

    avant.x = cop->depart.x;
    avant.y = cop->depart.y;

    cr_t maintenant;
    maintenant.x = cop->arrive.x;
    maintenant.y = cop->arrive.y;

    cr_t reserve;

    if (partie->joueur ==joueur1)
    {
        reserve.x = 0;
        reserve.y = 9;
    } else if (partie->joueur==joueur2)
    {
        reserve.x = 10;
        reserve.y = 1;
    }

    if (cop->capture == OUI)
    {
        if(cop->promotion == PROMU)
        {
             promo = piece_identifier(partie->tablier[maintenant.x][maintenant.y]);
             promo.statut = NORMAL;
             partie->tablier[maintenant.x][maintenant.y] = piece_caractere(promo);
        }

        partie->tablier[avant.x][avant.y] = partie->tablier[maintenant.x][maintenant.y];

        if(partie->joueur ==joueur1)
        {

            while ((case_vide(*partie,reserve) == OUI) && (reserve.y != 0))
            {
                reserve.y--;
            }
            while ((case_vide(*partie,reserve) == OUI) && (reserve.x != 9) && (reserve.y != 9))
            {
                reserve.x++;
            }

        }
        else if(partie->joueur==joueur2)
        {
            while ((case_vide(*partie,reserve) == OUI) && (reserve.y != 10))
            {
                reserve.y++;
            }
            while ((case_vide(*partie,reserve) == OUI) && (reserve.x != 1) && (reserve.y == 10))
            {
                reserve.x--;
            }
        }

        partie->tablier[maintenant.x][maintenant.y] = partie->tablier[reserve.x][reserve.y];

    }
    else
    {
        if(cop->promotion == PROMU)
        {
             promo = piece_identifier(partie->tablier[maintenant.x][maintenant.y]);
             promo.statut = NORMAL;
             partie->tablier[maintenant.x][maintenant.y] = piece_caractere(promo);
        }
         partie->tablier[avant.x][avant.y] = partie->tablier[maintenant.x][maintenant.y];
         partie->tablier[maintenant.x][maintenant.y] = '.';
    }

    cop->coup_prec=NULL;
    free(cop);
    partie->ldc.nb--;
    changer_joueur(partie);
}

cr_t saisie_case()
{
    int x,y;
    cr_t ca;

    printf("Entrez les coordonnes sous la forme x-y : ");
    scanf("%d-%d",&x,&y);
    ca.x = x;
    ca.y = y;

    return ca;

}

partie_t *partie_creer()
{
    partie_t *partie=malloc(sizeof(partie_t));
    partie->ldc.coup_debut=NULL;
    partie->ldc.coup_fin=NULL;
    partie->ldc.nb=0;
    partie->joueur = joueur1;
    return partie;

}

void partie_detruire(partie_t *partie)
{
    while(partie->ldc.nb)
    {
        partie->ldc.coup_fin->coup_prec->coup_suiv=NULL;
        free(partie->ldc.coup_fin);
    }
    free(partie);
}


void partie_sauvegarder(partie_t *partie,char *chaine)
{
    char *fichier=malloc((strlen(chaine)+10)*sizeof(char));
    FILE*f;
    int i = 0, j = 0;
    sprintf(fichier,"%s.plt",chaine);
    if((f=fopen(fichier,"w")) != NULL)
    {
        fprintf(f,"PL\n");
        for(i=0;i<11;i++)
        {
            for(j=0;j<11;j++)
            {
                 fprintf(f,"%c ", partie->tablier[i][j]);

            } fprintf(f,"\n");
        }   fprintf(f,"\n");
    } fclose(f);
}

partie_t *partie_charger(char *chaine)
{
    FILE *f;
    partie_t *p;
    int i=0;
    char lettre='0';
    char chemin[]="./PLT/";
    p = partie_creer(p);
    strcat(chemin,chaine);
    /*
    FILE *f = fopen(chemin, "r");
    if (f!= NULL)
    {
        printf("Je suis rentre !!!! \n ");
    }
    if(fgetc(f)!='P' || fgetc(f)!='L')
        exit(EXIT_FAILURE);
        fgetc(f);
        printf("........333...........\n");
        for(i=0; i<11; i++)
        {
            for(j=0; j<11; j++)
            {
                lettre=fgetc(f);
                if(lettre != '\n')
               {
                    p->tablier[i][j]=lettre;
                    printf("%c ", p->tablier[i][j]);
               /}
                else
                    j--;
            }
        }
        fclose(f);*/

    char tab[11];
    if ( f=fopen(chemin,"r+") == NULL )
    {
        perror("le fichier n'existe pas !");
        return NULL;
    }
    fgets(tab,100,f); //lire les dix premiers caracteres
    if(strcmp(tab,"PL")==0)
    {
        return NULL;
    }

    else
    {
        p = partie_creer(p);
        int i,j;
        for(i=0;i<11;i++)
        {
            for(j=0;j<11;j++)
            {
                lettre=fgetc(f);
                p->tablier[i][j]=lettre;
                printf("%c ", p->tablier[i][j]);




            }
        }fclose(f);
return p;
    }

}

partie_t *partie_nouvelle()
{
    partie_t *partie = partie_creer();
    init_tablier(partie);
    return partie;
}

void partie_jouer(partie_t *p)
{
    int x,k, v, victoire = NON;
    cr_t choixd;
    cr_t choixa;
    char c;
    char fichier[100];

    printf("                   ----------------------------------------\n");
    printf("                   |             Bienvenue !              |\n");
    printf("                   |                                      |\n");
    printf("                   |         Tapez 1 pour Jouer           |\n");
    printf("                   |         Tapez 2 pour Quitter         |\n");
    printf("                   |         Tapez 3 pour Charger         |\n");
    printf("                   |                                      |\n");
    printf("                   |                                      |\n");
    printf("                   ----------------------------------------\n");
    scanf("%d",&x);

    if (x == 1)
    {
        p = partie_nouvelle(p);
        system("color 4f");
        afficher_plateau(p);

        do
        {
            do
            {
                printf("\tTour du joueur %d \n", p->joueur);
                printf(" Tapez 1 pour continuer \n");
                printf(" Tapez 2 pour quitter \n");
                printf(" Tapez 3 pour annuler le dernier coup \n");
                scanf(" %d",&k);

                if (k == 1)
                {
                    printf("Choisissez la piece a bouger : \n");
                    choixd = saisie_case();
                    printf("Choisissez la case d'arrive : \n");
                    choixa = saisie_case();

                    if (deplacement_valide(p, choixd, choixa)== OUI && (piece_identifier(p->tablier[choixd.x][choixd.y]).joueur == p->joueur))
                    {
                        deplacement(p, choixd, choixa);
                        EFFACER_ECRAN();
                        afficher_plateau(p);
                        v = OUI;
                    }
                    else
                    {
                        EFFACER_ECRAN();
                        afficher_plateau(p);
                        printf("Deplacement invalide ! Reessayez ! \n");
                        v = NON;
                    }
                }
                else if ( k ==2)
                {

                    printf("Voulez-vous sauvegardez la partie (O/N) ? \n");
                    scanf(" %c",&c);
                    if (c == 'O')
                    {
                        printf("Entrez le nom du fichier sans extension \n");
                        scanf(" %99s",fichier);
                        partie_sauvegarder(p,fichier);

                        return;
                    }
                    else return;
                }
                else if ( k == 3 )
                {
                    annuler_deplacement(p);
                    EFFACER_ECRAN();
                    afficher_plateau(p);
                    v = NON;
                }
            } while (v == NON);
            changer_joueur(p);
        }
        while (victoire == NON);


        return;
    }
    else if (x == 3)
    {
        system("color 0C");
        printf("\nEntrez le nom de la partie a charger : \n");
        scanf("%s",fichier);
        p = partie_charger(fichier);
        afficher_plateau(p);

        do
        {
            do
            {
                printf("                                            Tour du joueur %d \n", p->joueur);
                printf("                  Tapez 1 pour continuer \n");
                printf("                  Tapez 2 pour quitter \n");
                printf("                  Tapez 3 pour annuler le dernier coup \n");
                scanf(" %d",&k);

                if (k == 1)
                {
                    printf("Choisissez la piece a bouger : \n");
                    choixd = saisie_case();
                    printf("Choisissez la case d'arrive : \n");
                    choixa = saisie_case();

                    if (deplacement_valide(p, choixd, choixa)== OUI && (piece_identifier(p->tablier[choixd.x][choixd.y]).joueur == p->joueur))
                    {
                        deplacement(p, choixd, choixa);
                        EFFACER_ECRAN();
                        afficher_plateau(p);
                        v = OUI;
                    }
                    else
                    {
                        EFFACER_ECRAN();
                        afficher_plateau(p);
                        printf("Deplacement invalide ! Reessayez ! \n");
                        v = NON;
                    }
                }
                else if ( k ==2)
                {

                    printf("Voulez-vous sauvegardez la partie (O/N) ? \n");
                    scanf(" %c",&c);
                    if (c == 'O')
                    {
                        printf("Entrez le nom du fichier sans extension \n");
                        scanf(" %99s",fichier);
                        partie_sauvegarder(p,fichier);

                        return;
                    }
                    else return;
                }
                else if ( k == 3 )
                {
                    annuler_deplacement(p);
                    afficher_plateau(p);
                    v = NON;
                }
            } while (v == NON);
            changer_joueur(p);
        }
        while (victoire == NON);


        return;
    }
}

/*

partie_t *replay_charger(char *chaine);

void replay_jouer(partie_t partie);  INUTILES */
