#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
using namespace std;

// This class represents a 3 x 3 board
// used in X_O game
char chboard[3][3];
class Board {
protected:
    char board[3][3] = { {0} };
    int  n_moves = 0;

public:
    // Return true  if move is valid and put it on board
    // within board boundaries in empty cell
    // Return false otherwise
    bool update_board(int x, int y, char symbol);
    // Returns true if there is any winner
    // either X or O
    // Written in a complex way. DO NOT DO LIKE THIS.
    bool is_winner();
    // Return true if 9 moves are done and no winner
    bool is_draw();
    // Display the board and the pieces on it
    void display_board();
};
// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        chboard[x][y] = board[x][y];
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void Board::display_board() {
    for (int i : {0, 1, 2}) {
        cout << "\n| ";
        for (int j : {0, 1, 2}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i : {0, 1, 2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i : {0, 1, 2}) {
        if ((row_win[i] && (row_win[i] == board[i][0])) ||
            (col_win[i] && (col_win[i] == board[0][i])))
        {
            return true;
        }
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
    {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
bool Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}


///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
protected:
    string name;
    char symbol;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player(char symbol); // Needed for computer players
    Player(int order, char symbol);
    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
};

Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player(int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string() {
    return "Player: " + name;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}

///////////////////////////////////////////
// This class represents a random computer player
// that generates random positions x y (0 to 2)
// If invalid, game manager asks to regenerate
class computerPlayer : public Player {
public:
    // Take a symbol and pass it to parent
    computerPlayer(char symbol);
    // Generate a random move
    void get_move(int& x, int& y);
};
// Set player symbol and name as Random Computer Player
computerPlayer::computerPlayer(char symbol) :Player(symbol)
{
    this->name = "Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void computerPlayer::get_move(int& x, int& y) {
    int DigO[3] = { 0 }, rowsO[3] = { 0 }, columnsO[3] = { 0 };
    int emptyR[3] = { 0 }, emptyC[3] = { 0 },emptydig[3];
    int DigX[3] = { 0 }, rowsX[3] = { 0 }, columnsX[3] = { 0 };
    if (chboard[1][1] != 'O' && chboard[1][1] != 'X') {
        x = 1; y = 1; return;
    }
    for (int i : {0, 1, 2}) {
        for (int j : {0, 1, 2}) {
            if (chboard[i][j] == 'X') {
                if (max(i - j, j - i) == 0)DigX[0]++; 
                columnsX[j]++; rowsX[i]++;
                if(i+j==2)DigX[2]++;             
            }
            else if (chboard[i][j] == 'O') {
                if (max(i - j, j - i) == 0)DigO[0]++;
                columnsO[j]++;  rowsO[i]++;
                if (i + j == 2)DigO[2]++;             
            }
            else { emptyR[i]++; emptyC[j]++; 
            if (i + j == 2)emptydig[2]++;
            if (max(i - j, j - i) == 0)emptydig[0]++;
            }
        }
    }
    pair<int, int> owin = { -1,-1 }; pair<int, int> xwin = { -1,-1 };
    int flag = 0;
    for (int i : {0, 1, 2}) {
        for (int j : {0, 1, 2}) {
            if (chboard[i][j] == 'X'|| chboard[i][j] == 'O')continue;
            if (rowsO[i] == 2|| columnsO[j] == 2 ||((i + j == 2)&&(DigO[2]==2))||
                ((max(i - j, j - i) == 0)&&DigO[0]==2)) {
                owin.first = i; owin.second = j;
            }
            else if (columnsX[j] == 2 || rowsX[i] == 2 ||
                ((i + j == 2) && (DigX[2] == 2))
                || ((max(i - j, j - i) == 0)&& DigX[0] == 2)) {
                xwin.first = i; xwin.second = j;
            }
            else if((emptyR[i] == 2&&(emptyR[i]+ rowsO[i])==3)||((i+j==2)&&(emptydig[2]==2)&&(emptydig[2]+DigO[2] == 3))||
         ((max(i-j, j-i)==0)&&(emptydig[0]==2)&&(emptydig[0]+ DigO[2]==3))||
                ((emptyC[j] == 2)&&emptyC[j]+columnsO[j])==3){
                x = i; y = j;
                flag = 2;
            }
            else if((flag!=2)&&emptyR[i]==3||emptyC[j]==3) {
                x = i; y = j;
                flag = 1;
            }
            else if(flag==0){ x = i; y = j; }
        }
    }
    if (owin.first != -1) {
        x = owin.first; y = owin.second;
    }
    else if (xwin.first != -1) {
        x = xwin.first; y = xwin.second;
    }
    else if(DigO[0]<1&& DigX[0] >0) {
        if (chboard[0][0] != 'X') {x = 0; y = 0; }
        else if(chboard[2][2]!='X') { x = 2; y = 2; }
    }
    else if (DigO[2] < 1 && DigX[2] >0) {
        if (chboard[0][2] != 'X') { x = 0; y = 2; }
        else if (chboard[2][0] != 'X') { x = 2; y = 0; }
    }
}

///////////////////////////////////////////
class GameManager {
public:
    void run();
    // This method creates board and players
    // It displays board
    // While True
    //   For each player
    //      It takes a valid move as x, y pair (between 0 - 2)
    //      It updates board and displays otit
    //      If winner, declare so and end
    //      If draw, declare so and end

};

void GameManager::run() {
    Board x_o;
    int x, y, choice;
    Player* players[2];
    players[0] = new Player(1, 'x');
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Player(2, 'o');
    else
        //Player pointer points to child
        players[1] = new computerPlayer('o');

    x_o.display_board();
    while (true) {
        for (int i : {0, 1}) {
            players[i]->get_move(x, y);
            while (!x_o.update_board(x, y, players[i]->get_symbol())) {
                players[i]->get_move(x, y);
            }
            x_o.display_board();
            if (x_o.is_winner()) {
                cout << players[i]->to_string() << " wins\n";
                return;
            }
            if (x_o.is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}


int main() {
    
        GameManager x_o_game;
        x_o_game.run();
        system("pause");
        
    
}
