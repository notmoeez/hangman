#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int Count = 0;

class Player
{
public:
    int id;
    int points;
    int gamemaster;
    string name;
    // member functions
    void setdata()
    {
        id = ++Count;
        points = 0;
        cout << "Enter name \n";
        string nam;
        cin.ignore();
        getline(cin, nam);
        name = nam;
        gamemaster = 0;
    }
    void gamemasterdata()
    {
        id = ++Count;
        points = 0;
        cout << "Enter name \n";
        string nam;
        cin.ignore();
        getline(cin, nam);
        name = nam;
        gamemaster = 1;
    }
    void getdata()
    {
        cout << name << " id is: ";
        cout << id << "\n";
        cout << "Points: " << points << endl;
        if (gamemaster == 1)
        {
            cout << "Player is gamemaster \n";
        }
        else
            cout << "Player is not gamemaster\n";
        cout << "\n\n";
    }

    void incrPoints()
    {
        ++points;
    }
    void makeGameMaster()
    {
        gamemaster = 1;
    }

    void updateRecord()
    {
        ofstream my_file;

        my_file.open("playersData.txt", ios::app);
        // my_file.write((char*)&name,sizeof(string));
        // my_file.write((char*)&points, sizeof(string));
        my_file << name;
        my_file << endl;
        my_file << points;
        my_file << endl;

        my_file.close();
    }
};

void displayFile()
{
    ifstream myFile;
    string temp;
    myFile.open("playersData.txt", ios::in);
    while (getline(myFile, temp))
    {
        cout << temp << endl;
    }
    myFile.close();
}

void getHighest()
{
    ifstream myFile;
    string temp, temp2;
    char num;
    int max = 0;
    int i = 1;
    myFile.open("playersData.txt", ios::in);
    while (!myFile.eof())
    {
        if (i % 2 == 0)
        {
            myFile >> num;
            // int n = int(num);
            if (max < num)
            {
                max = num;
                temp2 = temp;
            }
        }
        else
        {
            myFile >> temp;
        }
        i++;
    }
    myFile.close();

    cout << temp2 << " Has Highest Points : " << (max-48) << endl; // subtracting 48 to convert ascii value.
}

int main(void)
{
    cout << "enter number of players: ";
    int players = 0;
    cin >> players;
    if (players == 0)
    {
        exit;
    }
    // allocating dynamic array of players
    Player *ptr = new Player[players];
    for (int i = 0; i < players; i++)
    {
        if (i == 0)
        {
            ptr[i].gamemasterdata();
        }
        else
            ptr[i].setdata();
    }
    int tries;
tab2:
    cout << "\n Press 0 to end game: \n";
    int quit;
    cin >> quit;
    if (quit == 0)
    {
        cout << "GAME HAS ENDED!" << endl;
        return 0;
    }

    for (int i = 0; i < players; i -= -1)
    {
        ptr[i].updateRecord();
    }

    displayFile();

    getHighest();

    tries = 0;
    for (int i = 0; i < players; i -= -1)
    {
        ptr[i].getdata();
    }
    cout << "\n";
    cout << "Order in which players will play is as follow \n";
    // Now randomly shuffling the dynamic array for order of play
    random_device rd;
    mt19937 generator(rd());
    // shuffle the elements in the array
    shuffle(ptr, ptr + players, generator);
    // now the elements in the array are in a random order
    for (int i = 0; i < players; i++)
    {
        ptr[i].getdata();
    }
    // Now players will guess words functionality
    cout << "Enter the word to be guessed \n";
    string word;
    cin >> word;
    int civic = word.length();
    int count = 0;

    char *f;
    f = new char[civic];
    // iterating the character array to place dashes
    for (int i = 0; i < civic; i++)
    {
        f[i] = '_';
    }

    for (int i = 0; i < civic; i++)
    {
        cout << f[i];
    }

    cout << endl;

tab3:
    bool again = true;
    for (int i = 0; i < players; i++)
    {
        if (ptr[i].gamemaster == 1)
        {
            continue;
        }
        else
        {
            char guess;
            cout << "\n"
                 << ptr[i].name << "'s Turn to guess\nGuess:";
        tab1:
            cin >> guess;
            bool found = false;
            for (int j = 0; j < civic; j++)
            {
                if (guess == word[j])
                {
                    found = true;
                    f[j] = guess;

                    ++count;
                }
            }
            for (int x = 0; x < civic; x++)
            {
                cout << f[x];
            }
            if (count == civic)
            {
                found = false;
                again = false;
                ptr[i].incrPoints();
                cout << "\n"
                     << ptr[i].name << " guessed the word and is game master now!\n " << endl;
                for (int y = 0; y < players; y -= -1)
                {
                    if (ptr[y].gamemaster == 1)
                    {
                        ptr[y].gamemaster = 0;
                    }
                }
                ptr[i].makeGameMaster();
                goto tab2;
            }
            if (found)
            {
                cout << "\nCORRECT GUESS !!!!\nGuess Again:";
                goto tab1;
            }
            ++tries;
            cout << "\nINCORRECT GUESS !!" << endl;
            if (tries == 10)
            {
                cout << "Out of guesses, Game Master Wins!!!" << endl;
                for (int m = 0; m < players; m -= -1)
                {
                    if (ptr[m].gamemaster == 1)
                    {
                        ptr[m].incrPoints();
                    }
                }
                goto tab2;
            }
        }
    }

    if (again)
        goto tab3;
}