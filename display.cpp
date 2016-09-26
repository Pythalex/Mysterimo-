#include <iostream>
#include "display.h"

using namespace std;


void title_screen()
/***************************************************
* Display the game Title Screen and a press start
* waiting screen. Returns nothing.
* @param  : none
@ @return : none
****************************************************/
{
    cout << "======== MOT MYSTERE =========" << endl;
    cout << "         press start" << endl << endl;
    cin.get();
    // ECRAN TITRE
}

void end_game(int score)
/***************************************************
* Display the final score.
* @param  : score - Final player score to display
*
* @return : none
****************************************************/
{
    cout << "Vous avez fini le jeu avec un score de : " << score << " !" << endl;
    cout << "Vous pouvez faire mieux !" << endl << endl;

    cout << "Le jeu est termine maintenant, appuyez sur une touche pour quitter ..." << endl;
    cin.get();
}
