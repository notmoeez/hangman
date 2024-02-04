#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int count = 0;

class Player
{
public:
    string word, guess;
    char name, letter;
    bool isGameMaster;
    int id, points;
    Player()
    {
        name = ' ';
        word = ' ';
        guess = ' ';
        letter = ' ';
        isGameMaster = false;
        id = ++count;
        points = 0;
    }

    Player(bool gameMaster)
    {
        isGameMaster = false;
        name = ' ';
        word = ' ';
        guess = ' ';
        letter = ' ';
        id = ++count;
        points = 0;
    }

    void setData()
    {
        char n;
        cout << "\nPlayer Name: ";
        cin >> n;
        // getline(cin, n);
        name = n;
        // cin.ignore();
    }

    void setWord()
    {
        string w;
        cout << "\nEnter word to be guessed:";
        cin.ignore();
        getline(cin, w);
        word = w;
    }

    string getWord()
    {
        return word;
    }

    void setGameMaster()
    {
        isGameMaster = true;
    }

    bool getGameMaster()
    {
        return isGameMaster;
    }

    void displayData()
    {
        cout << "\nPlayer " << id << " Name: " << name << endl;
        cout << "\nPoints: " << points << endl;
    }

    void gameWon()
    {
        points++;
        isGameMaster = true;
    }
};

void gameStartup()
{
    cout << "\n\t\tWelcome to HANGMAN" << endl;
    cout << "Enter number of players: ";
}

void displayDashes(int l, char wd, int index)
{
    for (int i = 0; i < l; i++)
    {
        if (i == index)
        {
            cout << wd;
        }
        else
        {
            cout << " _ ";
        }
    }
}

int main()
{
    int n;
    gameStartup();
    cin >> n;

    Player *players = new Player[n];//dynamic memmory 
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            cout<<"GAME MASTER"<<endl;
            players[i].setGameMaster();
            players[i].setData();
        }
        else
        {
            players[i].setData();
        }
    }

    players[0].setWord();
    string Word = players[0].getWord();

    int length = Word.length();

    char *guessedWord = new char[length];

    for (int i = 0; i < length; i++)
    {
        guessedWord[i] = '_';
    }

    int totalGuessed = 0;

    for (int i = 1; i <= n; i++)
    {
        if (players[i].getGameMaster())
        {
            cout << i << endl;
        }
        else
        {
            bool done=false;
            cout<<"Turn: Player "<<i<<endl;
            cout << "\nEnter a letter: ";
            cin >> players[i].letter;
            for (int j = 0; j < length; j++)
            {
                if (Word[j] == players[i].letter)
                {
                    // displayDashes(length, players[i].letter, j);
                    if(guessedWord[j] = players[i].letter)
                    {
                    totalGuessed++;
                    cout << guessedWord<<endl;
                    if (totalGuessed == length)
                    {
                        players[i].gameWon();
                        done=true;
                        break;
                    }
                    }
                    else{
                        done=false;
                        
                    }
                }
            }
            if(done)
            break;
            else
            continue;
            

        }
    
    }
    

    // cout << "TERMINATED";

    return 0;
}