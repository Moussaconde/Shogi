#include <stdio.h>
#include <stdlib.h>
#include "partie.h"
#include "piece.h"
#include "deplacements.h"

int deplacement_valide_pion(partie_t *partie,cr_t depart, cr_t arrive, int statut)
{
    piece_t pmt;
    pmt = piece_identifier(partie->tablier[depart.x][depart.y]);

    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 || // pour eviter les erreurs de segummentation
            arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;


    else if(pmt.joueur==joueur1)      /* Pour le JOUEUR 1 */
    {
        if(statut== 0)        /*Si le pion n'est pas promu */
            {
                if(arrive.x - depart.x == -1 && arrive.y == depart.y)
                    return 1;               /* Valide */
                else
                    return 0;               /* Non valide */
            }
        else
            {
                return deplacement_valide_go(partie,depart,arrive); /* Si il es promu, il se deplace comme le G_O */
            }
    }
    else                        // Pour le JOUEUR 2
    {
        if(statut == 0)        /*Si le pion n'est pas promu */
            {
                if(arrive.x - depart.x == 1 && arrive.y == depart.y)
                    return 1;               /* Valide */
                else
                    return 0;               /* Non valide */
            }
        else
            return deplacement_valide_go(partie,depart,arrive);
    }
}

int deplacement_valide_tour(partie_t *partie,cr_t depart, cr_t arrive, int statut)
{
        if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 || // pour eviter les erreurs de segummentation
            arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;
        else {
                if(arrive.x<depart.x && arrive.y==depart.y)
            {

                int i;
                for(i=depart.x-1;i>arrive.x;i--)
                {
                    if(!case_vide(*partie,coor(i,depart.y)))
                        return 0;
                }
            }
                else if(arrive.x>depart.x && arrive.y==depart.y)
            {
                int i;
                for(i=depart.x+1;i<arrive.x;i++)
                {
                    if(!case_vide(*partie,coor(i,depart.y)))
                        return 0;
                }
            }
                else if(arrive.y<depart.y && arrive.x==depart.x)
            {
                int i;
                for(i=depart.y-1;i>arrive.y;i--)
                {
                    if(!case_vide(*partie,coor(depart.x,i)))
                        return 0;
                }
            }
                else if(arrive.y>depart.y && arrive.x==depart.x)
            {
                int i;
                for(i=depart.y+1;i<arrive.y;i++)
                {
                    if(!case_vide(*partie,coor(depart.x,i)))
                        return 0;
                }
            }

            if( arrive.x - depart.x == 0 && arrive.y - depart.y != 0)
                return 1; // on se déplace verticalement
            else if ( arrive.x - depart.x != 0 && arrive.y - depart.y == 0)
                return 1; // on se depalce horizentalement
            else if ( ((arrive.y - depart.y == 1 || arrive.y - depart.y == -1 ) && (arrive.x - depart.x == 1 || arrive.x - depart.x == -1))
                      && statut == 1)
                        return 1;
            else
                return 0;
        }
}


int deplacement_valide_cavalier(partie_t *partie, cr_t depart, cr_t arrive, int statut)
{
    piece_t pmt;
    pmt = piece_identifier(partie->tablier[depart.x][depart.y]);

     if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||    // pour eviter les erreurs de segummentation
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
               return 0;

     else if (pmt.joueur==joueur1)
     {
        if((arrive.y - depart.y == 1 && arrive.x - depart.x == -2) ||
           (arrive.y - depart.y == -1 && arrive.x - depart.x == -2)  )
            return 1;

        else if(statut == 1)   //Si il est promu
            return deplacement_valide_go(partie,depart,arrive);
        else
            return 0;
     }
    else if(pmt.joueur==joueur2)
    {
        if((arrive.y - depart.y == 1 && arrive.x - depart.x ==2) ||
                (arrive.y - depart.y == -1 && arrive.x - depart.x ==2)  )
            return 1;
        else
                return 0;
    }
    else return 0;
}

int deplacement_valide_fou(partie_t *partie,cr_t depart, cr_t arrive, int statut)
{
        int i;
    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;
    else
        {
            if (statut == 0)
            {
                    if((arrive.x - depart.x) >= 2 && (arrive.y - depart.y) >= 2)
                    {
                        for(i=1;i<abs(arrive.x - depart.x)+1;i++)
                        {
                            if(case_vide(*partie,coor(depart.x+i,depart.y+i))== NON)
                                {
                                    if (comp_coor(arrive,coor(depart.x+i,depart.y+i)) == OUI)
                                    return 1;
                                    else return 0;
                                } else return 1;
                        }
                    }


                    else if((arrive.x - depart.x) <= -2 && (arrive.y - depart.y) <= -2)
                    {
                        for(i=1;i<abs(arrive.x - depart.x)+1;i++)
                        {
                            if(case_vide(*partie,coor(depart.x-i,depart.y-i))== NON)
                                {
                                    if (comp_coor(arrive,coor(depart.x-i,depart.y-i)) == OUI)
                                    return 1;
                                    else return 0;
                                } else return 1;
                        }
                    } /* if depart.x -1 == arrivee.x && depart.y-1 == arrivee.y */


                    else if((arrive.x - depart.x) + (arrive.y - depart.y) == 0)
                    {

                        for(i=1;i<abs(arrive.x - depart.x)+1;i++)
                        {
                            if((arrive.x - depart.x) < 0)
                            {

                                if(case_vide(*partie,coor(depart.x-i,depart.y+i))== NON)
                                {
                                    if (comp_coor(arrive,coor(depart.x-i,depart.y+i)) == OUI)
                                    return 1;
                                    else return 0;
                                } else return 1;
                            }
                            else
                            {

                                if(case_vide(*partie,coor(depart.x+i,depart.y-i))==NON)
                                {
                                    if (comp_coor(arrive,coor(depart.x+i,depart.y-i)) == OUI)
                                    return 1;
                                    else return 0;
                                } else return 1;
                            }
                        }
                    }
                    else
                    {
                        return 1;
                    }

            }
             else if (statut == 1)
            {
                if((arrive.x - depart.x == arrive.y - depart.y) || (((arrive.x - depart.x) + (arrive.y - depart.y)) == 0 ))
                  return 1;
            }
            else
            {
                    return 1;
            }
        }
    return 0;
}

int deplacement_valide_lance(partie_t *partie,cr_t depart, cr_t arrive, int statut)
{
    piece_t pmt;
    pmt = piece_identifier(partie->tablier[depart.x][depart.y]);

    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;
    else if (statut == 0)
    {
            if(pmt.joueur==joueur1)
        {
            if(arrive.x<depart.x && arrive.y==depart.y)
            {
                int i;
                for(i=depart.x-1;i>arrive.x;i--)
                {
                    if(!case_vide(*partie,coor(i,depart.y)))
                        return 0;
                }
            }

            if(arrive.x - depart.x <0 && deplacement_horizontale(depart,arrive)== 0)
            return 1;
        }
        else if (pmt.joueur==joueur2)
        {
            if(arrive.x>depart.x && arrive.y==depart.y)
            {
                int i;
                for(i=depart.x+1;i<arrive.x;i++)
                {
                    if(!case_vide(*partie,coor(i,depart.y)))
                        return 0;
                }
            }

            if(arrive.x - depart.x >0 && deplacement_horizontale(depart,arrive)== 0)
                return 1;
        }
    }

    else if (statut == 1)
    {
        return deplacement_valide_go(partie,depart,arrive);
    }
    else
    {
        return 0;
    } return 0;
}

int deplacement_valide_ga(partie_t *partie,cr_t depart, cr_t arrive, int statut)
{
    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;

    else
    {
        if ((((arrive.y - depart.y == 1) || (arrive.y - depart.y == -1 )) && ((arrive.x - depart.x == 1) || (arrive.x - depart.x == -1)))
             || (deplacement_valide_pion(partie,depart,arrive,0)== 1))
                return 1;

        else if(statut == 1)
            return deplacement_valide_go(partie,depart,arrive);
    }
    return 0;
}

int deplacement_valide_roi(partie_t *partie,cr_t depart, cr_t arrive)
{
    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;
    else
    {
        if (deplacement_valide_ga(partie,depart,arrive,0) || deplacement_valide_go(partie,depart,arrive))
                return 1;
        else
                return 0;
    }
}

int deplacement_valide_go(partie_t *partie,cr_t depart, cr_t arrive)
{
    if( depart.x > 9 || depart.x < 1 || depart.y < 1 || depart.y > 9 ||
         arrive.x > 9 || arrive.x < 1 || arrive.y < 1 || arrive.y > 9   )
                return 0;
    else
    {
       if (arrive.x - depart.x == 1 || arrive.x - depart.x == -1 || arrive.y - depart.y == 1 || arrive.y - depart.y == -1 ||
        (arrive.x - depart.x == 1 && arrive.y - depart.y == 1) || (arrive.x - depart.x == -1 && arrive.y - depart.y == 1)    )
                return 1;
       else
            return 0;
    }

}

int deplacement_valide( partie_t * partie,cr_t depart, cr_t arrive)
{
    piece_t a = piece_identifier(partie->tablier[depart.x][depart.y]);
    piece_t b = piece_identifier(partie->tablier[arrive.x][arrive.y]);

        if (partie->tablier[depart.x][depart.y] == '.')
        {
            return 0;
        }
        else if (a.joueur == b.joueur)
        {
           return 0;
        }
        else if (a.type == 'p')
        {
           return deplacement_valide_pion(partie,depart, arrive, a.statut);
        }
        else if (a.type == 't')
        {
           return deplacement_valide_tour(partie,depart, arrive, a.statut);
        }
        else if (a.type == 'f')
        {
           return deplacement_valide_fou(partie,depart, arrive, a.statut);
        }
        else if (a.type == 'l')
        {
           return deplacement_valide_lance(partie,depart, arrive, a.statut);
        }
        else if (a.type == 'c')
        {
           return deplacement_valide_cavalier(partie,depart, arrive, a.statut);
        }
        else if (a.type == 'a')
        {
           return deplacement_valide_ga(partie,depart, arrive, a.statut);
        }
        else if (a.type == 'o')
        {
           return deplacement_valide_go(partie,depart, arrive);
        }
        else if (a.type == 'r')
        {
           return deplacement_valide_roi(partie,depart, arrive);
        }
        return 0;
}

int deplacement_horizontale(cr_t depart,cr_t arrive)
{
    if ( arrive.x - depart.x == 0 && arrive.y - depart.y != 0)
                return 1; // on se depalce horizentalement
    else
        return 0;
}
int deplacement_verticale(cr_t depart,cr_t arrive)
{
     if( arrive.x - depart.x != 0 &&  arrive.y - depart.y == 0)
                return 1; // on se déplace verticalement
    else
            return 0;

}
