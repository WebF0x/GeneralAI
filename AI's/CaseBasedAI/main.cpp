#include <iostream>
#include "AI.h"
#include <string>

using namespace std;

#define SAVE_FILE_NAME "ticTacToeSave.txt"

enum CaseEtat
{
    Vide = 0,
    X = 1,
    O = -1
};

/// Global variables (yup that's bad)
int nbTourPratiqueAI(0);
int nbPartieJouee(0);
CaseEtat tableau[9] = {Vide};
CaseEtat tour = X;
bool gameOver = false;

/// Prototypes
string caseEtatToString(CaseEtat);
bool tableauFull();
bool isWinning(CaseEtat);
void viderTableau();
void printTableau();
int askAIInput(AI&);
void saveAIMemory(const AI&);


int main()
{
    cout<<"Tic-Tac-Toe: Ecrivez un chiffre du NumPad pour placer votre coup"<<endl<<endl;

    cout<<"Combien de tour de pratique pour les intelligence artificielle?"<<endl;
    cin>>nbTourPratiqueAI;

    ///Tell possible answers
    vector<int> reponsesPossibles(0,0);
    for(int i(0); i<9; i++)
    {
        reponsesPossibles.push_back(i+1);
    }
    AI ai(reponsesPossibles);

    /// Load Memory
    if(!ai.loadMemory(SAVE_FILE_NAME))
    {
        cout<<"Erreur lors du chargement de la mémoire des IA"<<endl;
    }

    while(1)
    {
        cout<<"\nPartie "<<nbPartieJouee + 1<<":"<<endl;
        cout<<"===================================="<<endl;
        viderTableau();
        CaseEtat tour = X;

        gameOver = false;
        while (!gameOver)
        {
            ///Demander son coup au bon joueur
            cout<<"Tour du joueur "<<caseEtatToString(tour)<<":"<<endl;
            int entree(0);
            if(tour == X)
            {
                if(nbPartieJouee >= nbTourPratiqueAI)
                {
                    do
                    {
                        cin>>entree;
                    }while((tableau[entree-1] != Vide) || !(entree>0) || !(entree<=9));
                }
                else
                {
                    entree = askAIInput(ai);
                }
            }
            else
            {
                entree = askAIInput(ai);
            }

            if(!gameOver)
            {
                ///Changer le symbole de la case choisie
                tableau[entree-1] = tour;

                //if(nbPartieJouee >= nbTourPratiqueAI)
                    printTableau();

                ///Vérifier victoire
                if(isWinning(tour))
                {
                    if(nbPartieJouee >= nbTourPratiqueAI)   //Humain
                    {
                        if(tour == X)
                        {
                        ai.punish();
                        cout<<"Punished"<<endl;
                        }
                        else
                        {
                            ai.reward();
                            cout<<"Rewarded"<<endl;
                        }
                    }
                    else    //Pratique
                    {
                        ai.reward();
                        cout<<"Rewarded"<<endl;
                    }

                    gameOver = true;
                    cout<<"Le joueur des \""<<caseEtatToString(tour)<<"\" gagne!"<<endl;
                }
                ///Vérifier égalité
                else if (tableauFull())
                {
                    cout<<"Il y a egalite!"<<endl;
                    gameOver = true;
                }

                ///Changer de tour de joueur
                if (tour == X)
                {
                    tour = O;
                }
                else
                {
                    tour = X;
                }
            }
            cout<<endl;
        }

        ///Sauvegarder
        saveAIMemory(ai);


        cout<<endl;
        nbPartieJouee++;
    }
    return 0;
}

void saveAIMemory(const AI& ai)
{
    if(ai.saveMemory(SAVE_FILE_NAME))
    {
        cout<<"Saved!"<<endl;
    }
    else
    {
        cout<<"Not saved :("<<endl;
    }
}

string caseEtatToString(CaseEtat c)
{
    if (c == Vide)
        return " ";
    if (c == X)
        return "X";
    if (c == O)
        return "O";
    else
        return "";
}

bool tableauFull()
{
    bool isFull = true;
    for(int i(0); i<9; i++)
    {
        if (tableau[i] == Vide)
            isFull = false;
    }
    return isFull;
}

bool isWinning(CaseEtat tour)
{
    ///Mettre sous forme d'un tableau 3X3
    CaseEtat jeu[3][3];
    for(int i(0); i<3; i++)
    {
        for(int j(0); j<3; j++)
        {
            jeu[i][j] = tableau[i*3+j];
        }
    }

    ///Vérifie horizontalement
    for (int i(0);i<3;i++)
    {
        if ((jeu[i][0]==tour)&&(jeu[i][1]==tour)&&(jeu[i][2]==tour))
            return true;
    }

    ///Vérifie verticalement
    for (int j(0);j<3;j++)
    {
        if ((jeu[0][j]==tour)&&(jeu[1][j]==tour)&&(jeu[2][j]==tour))
            return true;
    }

    ///Check diagonal
    if (((jeu[0][0]==tour)&&(jeu[1][1]==tour)&&(jeu[2][2]==tour)) || ((jeu[2][0]==tour)&&(jeu[1][1]==tour)&&(jeu[0][2]==tour)))
    {
        return true;
    }

    return false;
}

void viderTableau()
{
    for(int i(0); i<9; i++)
    {
        tableau[i] = Vide;
    }
}

void printTableau()
{
    cout<<caseEtatToString(tableau[6])<<"_|_"<<caseEtatToString(tableau[7])<<"_|_"<<caseEtatToString(tableau[8])<<endl;
    cout<<caseEtatToString(tableau[3])<<"_|_"<<caseEtatToString(tableau[4])<<"_|_"<<caseEtatToString(tableau[5])<<endl;
    cout<<caseEtatToString(tableau[0])<<" | "<<caseEtatToString(tableau[1])<<" | "<<caseEtatToString(tableau[2])<<endl;
}

int askAIInput(AI& ai)
{
    std::vector<int> jeu;
    for(int i(0); i<9; i++)
    {
        jeu.push_back(tour * tableau[i]);   ///!!!!!!!!!!!!!!!
    }

    int entree;
    do
    {
        entree = ai.getReaction(jeu);
        if (entree == INVALID_REACTION)
        {
            /**/if(nbPartieJouee >= nbTourPratiqueAI)cout<<"Abandon"<<endl;
            gameOver = true;
            break;
        }

        if(tableau[entree-1] != Vide)
        {
            ai.punish();
        }
    }while(tableau[entree-1] != Vide);

    return entree;
}
