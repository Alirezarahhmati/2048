#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <ios>
#include <stdlib.h>

using namespace std;

struct User
{
    int table[4][4];
    int score = 2;
    int best_score;
    string name;
    string moves;
}user;

void play ();
void front ();
void shuffle_array (int arr[], int n);
int isGameEnd ();
void printWin ();
void getBestScore ();
void save_ranking ( string name , int score );
void output_ranking ( string name , int point );
void ranking ();
void endGame ();

class Move 
{
    public:
        void up () {
            for (int j = 0; j < 4; j++) {
                for (int i = 1; i < 4; i++) {
                    int num = user.table[i][j];
                    if (num == 0) {
                        continue;
                    }
                    user.table[i][j] = 0;
                    for (int z = i - 1; z >= 0; z--) {
                        if (user.table[z][j] > 0) {
                            if (user.table[z][j] == num) {
                                user.table[z][j] = 2 * num;
                                break;
                            }else{
                                user.table[z + 1][j] = num;
                                break;
                            }
                        }else if (z == 0) {
                            user.table[z][j] = num;
                            break;
                        }
                    }
                }
            }
        }
        void down () {
            for (int j = 0; j < 4; j++) {
                for (int i = 2; i >= 0; i--) {
                    int num = user.table[i][j];
                    if (num == 0) {
                        continue;
                    }
                    user.table[i][j] = 0;
                    for (int z = i + 1; z < 4; z++) {
                        if (user.table[z][j] > 0) {
                            if (user.table[z][j] == num) {
                                user.table[z][j] = 2 * num;
                                break;
                            }else{
                                user.table[z - 1][j] = num;
                                break;
                            }
                        }else if (z == 3) {
                            user.table[z][j ] = num;
                            break;
                        }
                    }
                }
            }
        }

        void left () {
            for (int i = 0; i < 4; i++) {
                for (int j = 1; j < 4; j++) {
                    int num = user.table[i][j];
                    if (num == 0) {
                        continue;
                    }
                    user.table[i][j] = 0;
                    for (int z = j - 1; z >= 0; z--) {
                        if (user.table[i][z] > 0) {
                            if (user.table[i][z] == num) {
                                user.table[i][z] = 2 * num;
                                break;
                            }else{
                                user.table[i][z + 1] = num;
                                break;
                            }
                        }else if (z == 0) {
                            user.table[i][z] = num;
                            break;
                        }
                    }
                }
            }
        }
        void right () {
            for (int i = 0; i < 4; i++) {
                for (int j = 2; j >= 0; j--) {
                    int num = user.table[i][j];
                    if (num == 0) {
                        continue;
                    }
                    user.table[i][j] = 0;
                    for (int z = j + 1; z < 4; z++) {
                        if (user.table[i][z] > 0) {
                            if (user.table[i][z] == num) {
                                user.table[i][z] = 2 * num;
                                break;
                            }else{
                                user.table[i][z - 1] = num;
                                break;
                            }
                        }else if (z == 3) {
                            user.table[i][z] = num;
                            break;
                        }
                    }
                }
            }
        }
        void addNumber () {
            int arr[16];
            int z = 0;
            for (int i = 0; i < 16; i++) {
                arr[i] = -1;
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (user.table[i][j] == 0) {
                        arr[z] = (i * 10) + j;
                        z++;
                    }
                }
            }

            srand(time(0));
            shuffle_array(arr , 16);

            for (int i = 0; i < 16; i++) {
                if (arr[i] != -1) {
                    int a = arr[i] / 10;
                    int b = arr[i] % 10;
                    user.table[a][b] = 2;
                    break;
                }
            }
        }
        void updateScore () {
            int max = 0;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (user.table[i][j] > max) {
                        max = user.table[i][j];
                    }
                }
            }

            user.score = max;
        }
};

int main () {

    while (true)
    {
        system("cls");
        cout << endl << endl;
        cout << "1_ New Game" << endl;
        cout << "2_ Ranking" << endl;
        cout << "3_ Exit" << endl;

        char ch;
        ch = getch();
        switch (ch) {
        case '1':
            play();
            break;
        case '2':
            ranking();
            break;
        case '3':
            return 0;
            break;
        }
    }
}

void play () {
    Move move;

    move.addNumber();
    move.addNumber();

    char key;
    while (true) 
    {
        system ("cls");
        front();
        key = getch ();
        switch (key)
        {
        case 'w':
            move.up();
            user.moves += "w_";
            break;
        case 's':
            move.down();
            user.moves += "s_";
            break;
        case 'a':
            move.left();
            user.moves += "a_";
            break;
        case 'd':
            move.right();
            user.moves += "d_";
            break;
        case 'e':
            endGame();
            return;
        default:
            continue;
        }

        int x = isGameEnd();
        if (x != -1) {
            if (x == 1) {
                printWin();
            }else {
                cout << endl << endl;
                cout << "*****************" << endl;
                cout << "**  Game over  **" << endl;
                cout << "*****************" << endl;
            }

            cout << "Enter your name : " ;
            string name;
            cin >> name;
            save_ranking(name , user.score);
        }

        move.addNumber();
        move.updateScore();
    }
}

void endGame () {
    cout << "Enter your name : " ;
    string name;
    cin >> name;
    save_ranking(name , user.score);
}

void shuffle_array (int arr[], int n)
{
    srand(time(0));
 
    // To obtain a time-based seed
    unsigned seed = 0;
 
    // Shuffling our array using random_shuffle
    random_shuffle(arr, arr + n);
}

int isGameEnd () {
    if (user.score == 2048) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (user.table[i][j] == 0) {
                return -1;
            } else if (user.table[i][j] == user.table[i][j + 1]) {
                return -1;
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (user.table[i][j] == 0) {
                return -1;
            }else if  (user.table[i][j] == user.table[i + 1][j]) {
                return -1;
            }
        }
    }

    return 0;
}

void printWin () {
    
    cout << endl << endl;
    cout << "***********************************" << endl;
    cout << "**    Congragulation you win!    **" << endl;
    cout << "***********************************" << endl;
}

void front() {
        string Table[9][21];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 21; j++) {

                if (j % 5 == 0) {
                    if (i % 2 == 0) {
                        Table[i][j] = "\u254B"; 
                    } else {
                        Table[i][j] = "\u2503";
                    }
                } else {
                    if (i % 2 == 0) {
                        Table[i][j] = "\u2501";
                    } else {
                        Table[i][j] = " ";
                    }
                }


                if (i == 0) {
                    if (j % 5 == 0) {
                        Table[i][j] = "\u2533";
                    } else {
                        Table[i][j] = "\u2501";
                    }
                    if (j == 0) {
                        Table[i][j] = "\u250F";
                    }
                    if (j == 20) {
                        Table[i][j] = "\u2513";
                    }
                }

                if (i == 8) {
                    if (j % 5 == 0) {
                        Table[i][j] = "\u253B";
                    } else {
                        Table[i][j] = "\u2501";
                    }
                    if (j == 0) {
                        Table[i][j] = "\u2517";
                    }
                    if (j == 20) {
                        Table[i][j] = "\u251B";
                    }
                }

                if (j == 0) {
                    if (i % 2 == 0 & i != 0 & i != 8) {
                        Table[i][j] = "\u2523";
                    }
                }
                if (j == 20) {
                    if (i % 2 == 0 & i != 0 & i != 8) {
                        Table[i][j] = "\u2528";
                    }
                }
            }
        }

        int c = 0;
        int a = 0;
        for (int i = 0; i< 4; i++) {
            for (int j = 0; j < 4; j++) {
                c = user.table[i][j];
                a = 1;
                while (c != 0){
                    Table[i*2+1][(j+1)*5-a] = to_string(c % 10);
                    a++;
                    c /= 10;
                }
            }
        }


        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 21; j++) {
                cout << Table[i][j];
            }
            cout << endl;
        }
        cout << "   Score : " << user.score;
        cout << "        Highest score : " << user.best_score << endl;
        cout << " Moves : " <<  user.moves << endl;
}

void ranking ()
{
    system ("cls");
    for (int i = 0 ; i < 10; i++)
    {
        cout << endl;
    }
    cout << "                                              ************************************" << endl;
    cout << "                                              *      ENTER to see ranking !      *" << endl;
    cout << "                                              ************************************" << endl;
    cin.get();

    ifstream file ("Othelo_ranking_save.txt");

    if ( !file ) {
        system ("cls");
        for (int i = 0 ; i < 20; i++ ) {
            cout << endl;
        }
        cout << "                                           ***********************************************" << endl;
        cout << "                                           *   EROR : You must play at least one time.   *" << endl;
        cout << "                                           ***********************************************" << endl;
        cin.get();
        return;
    }

    string list_ranking;
    char ch;

    while ( !file.eof() )
    {
        file.get(ch);
        list_ranking += ch;
    }

    int size = list_ranking.size ();
    int *rank_array = new int [100];
    for (int i = 0; i < 100; i++ )
    {
        rank_array[i] = 0;
    }
    int t = 0;
    for ( int i = 0 ; i < size - 1  ; i++ )
    {
        if (list_ranking[i + 1] != '%') {
            int temp = int ( list_ranking[++i] );
            i += temp + 1;
            rank_array[ t++ ] = int (list_ranking[ i ]);
        }
    }

    for ( int i = 0; i < 10; i++) 
    {
        for ( int j = 0; j < 99 - i ; j++ )
        {
            if ( rank_array[j] > rank_array[j + 1] )
            {
                int temp = rank_array[j];
                rank_array[j] = rank_array[j +1];
                rank_array[j + 1] = temp;
            }
        }
    }

    int best_score[10];
    int l = 1;
    best_score[0] = rank_array[99];
    for (int i = 1; i < 10; i++ )
    {
        if ( rank_array[98 - i] != rank_array [98 - i + 1]) {
            best_score[l++] = rank_array[98 - i]; 
        }
    }

    string *name_ranking = new string [10];
    int j = 0;
    for ( int bar = 0; bar < t; bar++ )
    {
        for ( int i = 1 ; i < size ; i++  )
        {
            if ( list_ranking[i] != '%' ) {
                int temp = int ( list_ranking[i] );
                if ( list_ranking[i + temp + 1] == rank_array[ 99 - bar] ) {
                    for (int l = 0; l < temp ; l++ ) 
                    {
                        name_ranking[j] += list_ranking[++i];
                    }
                    i++;
                    j++;
                } else {
                    i += temp + 1;
                }
            }
        }
    }

    output_ranking ( name_ranking[0] , rank_array[99] );

    cin.get();
    delete[] rank_array;
    delete[] name_ranking;
}

void output_ranking ( string name , int point )
{
	for (int i = 0 ; i < 5  ; i++ )
	{
		cout << endl ;
	}
	//line 1 
	cout << setw(55) ;
	for (int i = 0 ; i < 15 ; i++ )
	{
		cout << "*";
	}
	cout << endl ;
	//line 2
	cout << setw(55) ;
	cout << "*" << "   Ranking   " << "*" << endl ;
	// line 3 
	cout << setw(55) ;
	cout << "*" << setw(14) << "*" << endl ;
	cout << setw(55) ;
	for (int i = 0 ; i < 15 ; i++ )
	{
		cout << "*";
	}
	cout << endl << endl ;
	//line 4 
	cout << "                                                     And the Best Player is " << endl << endl << setw(65) << name << endl << endl << setw(65) << " with " << endl << endl << setw(60) << point << " points ! " << endl ;
	cout << endl << endl ;
	
	string line ;
	for (int i = 0 ; i < 16 ; i++ )
	{
		line+= "\u2500" ;
	}
	//
	cout << setw(57) << "\u256d" << line << "\u256e" << endl ;
	//
	cout << setw(57) << "\u2502" << "Congratulations!" << "\u2502" << endl ;
	//
	cout << setw(57) << "\u2570" << line << "\u256f" << endl ;
}

void save_ranking ( string name , int score ) 
{
    ifstream file1 ("Othelo_ranking_save.txt");
    if ( ! file1 ) {
        ofstream file ("Othelo_ranking_save.txt");
        for ( int i = 0 ; i < 100 ; i++ )
        {
            file.put ('%');
        }
        file.close ();
    }
    file1.close();

    ifstream file_ranking ("Othelo_ranking_save.txt");

    string names_list;
    char ch;
    while ( !file_ranking.eof() )
    {
        file_ranking.get (ch);
        names_list += ch;
    }

    bool chang = false;
    int size = name.size ();
    int sizeT = names_list.size();
    int counter = 0;
    for (int i = 0; i < sizeT; i++ )
    {
        if ( names_list [i] == '%' && names_list[i + 1] != '%') {
            int temp = int (names_list[++i]);
            if ( temp == size ) {
                for (int j = 0; j < size ; j++ )
                {
                    if ( names_list[++i] == name[j]) {
                        counter++;
                    }
                }
                if ( counter == size ) {
                    temp = int (names_list[i + 1]);
                    names_list[i + 1] = char ( temp + score );
                    chang = true;
                    break;
                }
            }else {
                i += temp + 1;
            }
        }
    }
    file_ranking.close ();
    remove("Othelo_ranking_save.txt");
    ofstream chang_file ("Othelo_ranking_save.txt");

    if ( !chang ) {
        chang_file.put ('%');
        chang_file.put ( char (size) );
        for (int i = 0; i < size; i++ ) 
        {
            chang_file.put (name[i]);
        }
        chang_file.put ( char ( score ));
        int t = 1;
        for (int i = 0; i < sizeT ; i++ ) 
        {
            if ( names_list[i] == '%') {
                t++;
            }
            if (t == 100){
                break;
            }
            chang_file.put( names_list[i] );
        }
    } else {
        for (int i = 0 ; i < sizeT; i++ )
        {
            chang_file.put (names_list[i]);
        }
    }

    chang_file.close ();
}

void getBestScore ()
{
        system ("cls");
    for (int i = 0 ; i < 10; i++)
    {
        cout << endl;
    }
    cout << "                                              ************************************" << endl;
    cout << "                                              *      ENTER to see ranking !      *" << endl;
    cout << "                                              ************************************" << endl;
    cin.get();

    ifstream file ("Othelo_ranking_save.txt");

    if ( !file ) {
        system ("cls");
        for (int i = 0 ; i < 20; i++ ) {
            cout << endl;
        }
        cout << "                                           ***********************************************" << endl;
        cout << "                                           *   EROR : You must play at least one time.   *" << endl;
        cout << "                                           ***********************************************" << endl;
        cin.get();
        return;
    }

    string list_ranking;
    char ch;

    while ( !file.eof() )
    {
        file.get(ch);
        list_ranking += ch;
    }

    int size = list_ranking.size ();
    int *rank_array = new int [100];
    for (int i = 0; i < 100; i++ )
    {
        rank_array[i] = 0;
    }
    int t = 0;
    for ( int i = 0 ; i < size - 1  ; i++ )
    {
        if (list_ranking[i + 1] != '%') {
            int temp = int ( list_ranking[++i] );
            i += temp + 1;
            rank_array[ t++ ] = int (list_ranking[ i ]);
        }
    }

    for ( int i = 0; i < 10; i++) 
    {
        for ( int j = 0; j < 99 - i ; j++ )
        {
            if ( rank_array[j] > rank_array[j + 1] )
            {
                int temp = rank_array[j];
                rank_array[j] = rank_array[j +1];
                rank_array[j + 1] = temp;
            }
        }
    }

    int best_score[10];
    int l = 1;
    best_score[0] = rank_array[99];
    for (int i = 1; i < 10; i++ )
    {
        if ( rank_array[98 - i] != rank_array [98 - i + 1]) {
            best_score[l++] = rank_array[98 - i]; 
        }
    }

    string *name_ranking = new string [10];
    int j = 0;
    for ( int bar = 0; bar < t; bar++ )
    {
        for ( int i = 1 ; i < size ; i++  )
        {
            if ( list_ranking[i] != '%' ) {
                int temp = int ( list_ranking[i] );
                if ( list_ranking[i + temp + 1] == rank_array[ 99 - bar] ) {
                    for (int l = 0; l < temp ; l++ ) 
                    {
                        name_ranking[j] += list_ranking[++i];
                    }
                    i++;
                    j++;
                } else {
                    i += temp + 1;
                }
            }
        }
    }

    user.best_score = rank_array[99];
}
