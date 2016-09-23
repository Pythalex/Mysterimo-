#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void title_screen()
/**************************************************
* Display the game Title Screen and a press start
* waiting screen. Returns nothing.
*** ----------------------------------------------*/
{
    cout << "======== MOT MYSTERE =========" << endl;
    cout << "         press start" << endl << endl;
    cin.get();
    // ECRAN TITRE
}

int dic_size(ifstream& stream)
/**************************************************
* Returns the number of words in the dictionnary
* text file of the game folder : '~\dic.txt'
* Each word MUST take one line, no more no less.
* Words can be added everywhere, as long as they
* take one line.
*** ----------------------------------------------*/
{
    int line_num (0);
    string line;

    while (getline(stream, line))
    {
        line_num += 1;
    }
    stream.clear();
    stream.seekg(0, ios::beg);
    // On revient au début du fichier

    return line_num;
}

string choices_word(std::ifstream& stream, int words)
/****************************************************
* Pseudo-randomly choices a word in the dictionnary
* and returns it.
*** ----------------------------------------------*/
{
    int rand_n (rand()%words + 1);
    // Random number get

    string line;

    for (int i = 0; i < rand_n; i++)
    {
        getline(stream, line);
    }
    stream.clear();
    stream.seekg(0, ios::beg);
    // Dic reading

    return line;
    // Value return
}

bool is_in(int value, int table[], int table_size)
/****************************************************
* Finds if an int value exists in an int array,
* returns boolean.
*** ----------------------------------------------*/
{
    bool exist (false);
    for (int i (0); i < table_size; i++)
    {
        exist = exist || (table[i] == value);
    }
    return exist;
}

string mix_word(string word)
/****************************************************
* Pseudo-randomly mix a word, without loyalty
* verification.
*** ----------------------------------------------*/
{
    string new_word;

    int rand_got[word.size()];
    int counter (0);
    // Counter to fill the table

    for (unsigned int i = 0; i < word.size(); i++)
    {
        rand_got[i] = -1;
    }
    // Random list initiate

    while(new_word.size() < word.size())
    {
        int rand_n;
        do
        {
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

bool round(std::ifstream& stream, int round_number, int words, vector<string> chosen_words)
/****************************************************
* Rules a game round.
*
*** ----------------------------------------------*/
{
    string word (choices_word(stream, words));
    // Word selection
    chosen_words.push_back(word);
    // We add the word to the list
    string mixed_word (mix_word(word));
    // Word mixing

    cout << "MOT : " + mixed_word << endl << "Quel est l'original ?" << endl;
    cout << "(Entrez 'quit' pour quitter le jeu ! )" << endl << endl;
    cout << "MOT ORIGINAL : ";
    bool victory (false);
    string entry;

    do
    {
        getline(cin, entry);

        if (entry == word)
        {
            victory = true;
        }
        else if (entry == "quit")
        {
            return false;
        }
        else
        {
            cout << "Rate ! Reessayez " << endl << endl;
            cout << "MOT ORIGINAL : ";
        }
    }while(!victory);
    // The game continues while the player doesn't found
    // the mystery word or type quit

    return true;
}

void end_game(int score)
/****************************************************
* Display the final score.
*
*** ----------------------------------------------*/
{
    cout << "Vous avez fini le jeu avec un score de :  " << score << " !" << endl;
    cout << "Vous pouvez mieux faire !" << endl << endl;

    cout << "Le jeu est termine maintenant, appuyez sur une touche pour quitter ..." << endl;
    cin.get();
}

int main()
/****************************************************
* Main function, calls every others.
*
*** ----------------------------------------------*/
{
    /*
    *   ------ GAME PREPARATION ------
    */

    title_screen();
    // ECRAN TITRE

    string dictionnary = "dic.txt";
    std::ifstream stream (dictionnary.c_str());
    // input file Stream

    srand(time(0));
    // Random initiate

    if (!stream)
    {
        cout << "FATAL ERROR : Bad stream";
        return 1;
    }
    // Stream checking

    int score (0);
    // Player's score - Number of found words

    int words = dic_size(stream);
    // Words counting

    /*
    *   ------ GAME ROUNDS -------
    */

    int round_number (1);
    bool game_continue (true);

    vector<string> chosen_words(0);
    // List of all words chosen for the game

    do
    {
        game_continue = round(stream, round_number, words, chosen_words);

        if (game_continue)
        {
            score += 1;
            cout << "Bravo ! Vous avez trouve le mot mystere, encore une fois !" << endl << endl;
        }
    }while(game_continue);

    end_game(score);
}
