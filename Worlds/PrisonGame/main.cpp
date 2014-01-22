#include <iostream>
#include "AI.h"
#include <stdlib.h>
#include <vector>

using namespace std;

int hand[2][2];
bool playerTurn = true;    //Human = true, AI = false3
AI* ai;
AI* robot;

enum GameState
{
    P0Win,
    P1Win,
    Unfinished
};

void afficher()
{
    //system("cls");
    cout << hand[0][0] << " --- " << hand[0][1] << endl;
    cout << hand[1][0] << " --- " << hand[1][1] << endl;
    cout << endl << endl << endl;
}

GameState gameState()
{
    if(hand[0][0] > 4 || hand[0][1] > 4)
    {
        return P1Win;
    }

    if(hand[1][0] > 4 || hand[1][1] > 4)
    {
        return P0Win;
    }

    if(hand[0][0] == 0 && hand[0][1] == 0)
    {
        return P1Win;
    }

    if(hand[1][0] == 0 && hand[1][1] == 0)
    {
        return P0Win;
    }

    return Unfinished;
}

void play(int src, int dest)
{
    cout<<"Hit!"<<endl;
    hand[!playerTurn][dest] += hand[playerTurn][src];

    if(hand[!playerTurn][dest] == 4)
        hand[!playerTurn][dest] = 0;
}

void split()
{
    cout<<"Split!"<<endl;
    int fingerCount = hand[playerTurn][0] + hand[playerTurn][1];
    hand[playerTurn][0] = fingerCount/2;
    hand[playerTurn][1] = fingerCount/2;
}

void abandon()
{
    cout<<"Abandon!"<<endl;
    hand[playerTurn][0] = 0;
    hand[playerTurn][1] = 0;
}

void play(int move)
{
    switch(move)
    {
    case 2:
        split();
        break;
    case 14:
        play(0,0);
        break;
    case 16:
        play(0,1);
        break;
    case 34:
        play(1,0);
        break;
    case 36:
        play(1,1);
        break;
    default:
        break;
    }
}

vector<int> getSituation()
{
    vector<int> vec(0,0);
    vec.push_back(hand[0][0]);
    vec.push_back(hand[0][1]);
    vec.push_back(hand[1][0]);
    vec.push_back(hand[1][1]);

    return vec;
}

bool validMove(int move)
{
    int fingerCount = hand[playerTurn][0] + hand[playerTurn][1];
    int diff = hand[playerTurn][0] - hand[playerTurn][1];

    switch(move)
    {
    case 2:
        return ( fingerCount%2 == 0 && diff!=0); //nb doigts pair et pas mains égales
    case 14:
    case 16:
        return (hand[playerTurn][0] > 0);
    case 34:
    case 36:
        return (hand[playerTurn][1] > 0);
    default:
        return false;
    }
}

void askPlayerMove()
{
    int move;

    if(playerTurn)
    {
        /*
        move = robot->getReaction(getSituation());

        while(!validMove(move))
        {
            if(move == -1)
            {
                abandon();
                return;
            }


            robot->punish();
            move = robot->getReaction(getSituation());
        }
        //*/

        //*  This is for humans
        do
        {
            cout<<"Your move: ";
            cin>>move;
        }
        while(!validMove(move));
        //*/

    }
    else
    {
        move = ai->getReaction(getSituation());

        while(!validMove(move))
        {
            if(move == -1)
            {
                abandon();
                return;
            }


            ai->punish();
            move = ai->getReaction(getSituation());
        }
    }

    play(move);

    playerTurn = !playerTurn;
    afficher();
}

void showInstructions()
{
    cout<<"Bienvenue au jeu de prison"<<endl;
    cout<<"=========================="<<endl;
    cout<<"Les regles sont simples:"<<endl;
    cout<<"Si tes mains sont vides, tu perds."<<endl;
    cout<<"Si ta main est a 4 doigts, referme les."<<endl;
    cout<<"Si tu as un nombre pair de doigts, tu as le droit de les \"split\" entre tes deux mains."<<endl;
    cout<<"Si ta main a des doigts, tu peux ajouter ce nombre de doigts a l'adversaire."<<endl;
    cout<<endl;
    cout<<"Jouez avec le clavier numerique, c'est plus intuitif"<<endl;
    cout<<"SaMainGauche(4)                  SaMainDroite(6)"<<endl;
    cout<<"TaMainGauche(1)     Split(2)     TaMainDroite(3)"<<endl;
    cout<<endl;
    cout<<"Le jeu est facile au debut, mais attention: \nL'INTELLIGENCE ARTIFICIELLE APPREND DE SES ERREURS!"<<endl;
    cout<<endl;
    cout<<endl;
}

void reset()
{
    hand[0][0] = 1;
    hand[0][1] = 1;
    hand[1][0] = 1;
    hand[1][1] = 1;
}

int main()
{
    showInstructions();

    /// Create AI
    vector<int> vecReact(0,0);
    vecReact.push_back(14);
    vecReact.push_back(16);
    vecReact.push_back(34);
    vecReact.push_back(36);
    vecReact.push_back(2);

    ai = new AI(vecReact);
    ai->loadMemory("prisonGameMemory");

    robot = new AI(vecReact);
    robot->loadMemory("robotMemory");

    while(true)
    {
        system("pause");
        cout<<"Game start: "<<endl;
        reset();
        afficher();


        while(gameState() == Unfinished)
        {
            //if(!playerTurn)
            //    cout<<"AI does: ";
            //else
             //   cout<<"Robot does:";

            askPlayerMove();
        }

        if(gameState() == P0Win)
        {
            cout<<"AI wins!"<<endl;
            ai->reward();
            robot->punish();
        }
        else
        {
            cout<<"Robot wins!"<<endl;
            ai->punish();
            robot->reward();
        }

        ai->saveMemory("prisonGameMemory");
        robot->saveMemory("robotMemory");
    }


    return 0;
}
