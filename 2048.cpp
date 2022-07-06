#include <iostream>
#include <cstdlib>

using namespace std;

void newGame ();

struct
{
    int table[4][4];
    string name;
}user;


class Move {
    public:
        void up () {}
        void down () {}
        void left () {}
        void right () {}
};

int main () {

    while (true)
    {
        cout << endl << endl;
        cout << "1_ New Game" << endl;
        cout << "2_ Exit" << endl;


        string s = "";
        cin >> s;

        switch (s[0]) {
        case '1':
            newGame();
            break;
        case '2':
            return 0;
            break;
        }
    }
}

void newGame () 
{
    int a = rand() % 4;
    int b = rand() % 4;
    int c = rand() % 4;
    int d = rand() % 4;

    user.table[a][b] = 2;
    user.table[c][d] = 2;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << user.table[i][j] << " ";
        }
        cout << endl;
    }
}

