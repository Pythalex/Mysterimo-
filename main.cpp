#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
// Third Party Library

#include "display.h"
#include "tools.h"
// My Library

using namespace std;

/* ------------ Game Rules Functions -----------*/

int choose_difficulty(){
/***************************************************
* Asks the user the difficulty he wants : returns
* the number of attempts per word for the game.
* @param  : none
*
* @return : int number of attempts per round
****************************************************/

    cout << "Entrez une difficulte (facile / moyen "\
         << "/ difficile) : ";
    string choix;
    // On demande la difficulté à l'utilisateur

    while(choix != "facile" && choix != "moyen"\
          && choix != "difficile"){
        getline(cin, choix);

        if((choix != "facile" && choix != "moyen"\
          && choix != "difficile")){
            cout << "Veuillez choisir une difficulte"\
                 << " permise : ";
        }
    }
    // Tant que l'utilisateur ne choisit pas une
    // difficulté valide, on lui redemande.

    if(choix == "facile") return 7;
    else if(choix == "moyen") return 5;
    else if(choix == "difficile") return 3;
    else {
        return 0;
        cout << "Erreur difficulte";
    }
    // On renvoie le nombre de manches associé à
    // la difficulté choisie
}

string choices_word(std::ifstream& stream){
/****************************************************
* Pseudo-randomly choices a word in the dictionnary
* and returns it.
* @param  : stream - Stream of the dictionnary txt file
*
* @return : Word from the dictionnary
****************************************************/

    int words (dic_size(stream));

    int rand_n (rand()%words + 1);
    // Random number get

    string line;

    for (int i = 0; i < rand_n; i++){
        getline(stream, line);
    }
    stream.clear();
    stream.seekg(0, ios::beg);
    // Dic reading

    return line;
    // Value return
}


string mix_word(string word){
/****************************************************
* Pseudo-randomly mix a word, without loyalty
* verification.
* @param  : word to mix
*
* @return : mixed word
****************************************************/

    string new_word;

    int rand_got[word.size()];
    int counter (0);
    // Counter to fill the table

    for (unsigned int i = 0; i < word.size(); i++){
        rand_got[i] = -1;
    }
    // Random list initiate

    while(new_word.size() < word.size()){
        int rand_n;
        do{
            rand_n = rand()%word.size();
        }while (is_in(rand_n, rand_got, word.size()));
        // Random number get

        rand_got[counter] = rand_n;
        counter ++;
        // We add the random number to the table

        new_word += word[rand_n];
        // We create the new word
    }
    // Mixing

    return new_word;
}

bool round(std::ifstream& stream, int round_number, vector<string>& chosen_words, int difficulty){
/***************************************************
* Rules a game round.
* @param  : stream       - Stream of the dictionnary file
*           round_number - Number of the actual round
*           chosen_words - List of all chosen words during
*                           the game rounds
*           difficulty   - Number of attempts
*
* @return : player won the round ? true/false
****************************************************/

    string word (choices_word(stream));
    // Word selection
    chosen_words.push_back(word);
    // We add the word to the list
    string mixed_word (mix_word(word));
    // Word mixing

    int attempts_left (difficulty);
    // Number of attempts left

    cout << "MOT : " + mixed_word << endl << "Quel est l'original ?" << endl;
    cout << "(Entrez 'quit' pour quitter le jeu ! )" << endl << endl;
    cout << "MOT ORIGINAL : ";
    bool victory (false);
    string entry;

    do{
        getline(cin, entry);

        if (entry == word){
            victory = true;
        }
        else if (entry == "quit"){
            return false;
        }
        else{
            attempts_left--;
            if(attempts_left == 0) return false;

            cout << endl << "Rate ! Reessayez " << endl;
            cout << "Il vous reste " << attempts_left << " essais." << endl;
            cout << "MOT ORIGINAL : ";
        }
    }while(!victory);
    // The game continues while the player doesn't found
    // the mystery word or type quit

    return true;
}

/* ---------------------------------------------*/

/////////////////////////////////////////////////


int main(){
/***************************************************
* Main function
****************************************************/

    /*********************************
    * ------ GAME PREPARATION ------ *
    **********************************/

    title_screen();
    // ECRAN TITRE

    int difficulty (choose_difficulty());
    // Options

    string dictionnary = "dic.txt";
    std::ifstream stream (dictionnary.c_str());
    // input file Stream

    srand(time(0));
    // Random initiate

    if (!stream){
        cout << "FATAL ERROR : Bad stream";
        return 1;
    }
    // Stream checking

    int score (0);
    // Player's score - Number of found words

    /*********************************
    * ------ GAME ROUNDS ------ *
    **********************************/

    int round_number (1);
    bool game_continue (true);

    vector<string> chosen_words(0);
    // List of all words chosen for the game
    bool player_continue = true;

    do{
        game_continue = round(stream, round_number, chosen_words, difficulty);

        if (game_continue){
            score += 1;
            cout << "Bravo ! Vous avez trouve le mot mystere, encore une fois !" << endl << endl;
        }
        else {
            cout << endl << "Le mot etait : " << chosen_words[chosen_words.size() - 1] << "." << endl;
            cout << "Vous finissez avec un score de " << score << " mots trouves ! " << endl << endl;
            // Afficher le mot non trouvé + score

            cout << "Voulez-vous continuer a jouer ? (Y/N) : ";
            string reponse;
            getline(cin, reponse);
            // Récupérer réponse du joueur

            game_continue = true;
            if(reponse != "Y" && reponse != "y"){
                game_continue = false;
            }
            // Si le joueur répond oui, on continue à jouer
        }
    }while(game_continue && player_continue);

    end_game();
}
