

#include<iostream>
#include<conio.h>//for getch() and kbhit()
#include<windows.h>//used for gotoxy() and sleep function
#include<fstream>//to record data
#include<time.h>//for sleep and for date and time
#include<stdlib.h>

using namespace std;

const int borderwidth = 40;//dimensions taken for the border
const int borderheight = 40;
int score;
int lives;
bool running;
int tailofsnake;//length of tail
void gotoxy(int x, int y);
void record();
enum controldirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
controldirection dir;
typedef struct position {
    int x0;
    int y0;
}position;
position Food, Head, Body[100];


class SnakeMovement {
private:
    int chance = 3;
public:
    void print();
    void loading();
    void border();
    void moving();
    void snakemove();
};



void SnakeMovement::moving() {
    running = true;
    tailofsnake = 0;
    while (running) {
        border();
        if (_kbhit()) {//it will return +ve number if key has been pressed
            //Use W for UP
            //Use A for LEFT
            //Use D for RIGHT
            //Use S for down
            switch (_getch()) {//return ASCII value if key has been pressed
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            default:
                chance--;
                if (chance <= 3 && chance > 0 || chance == 0) {
                    system("CLS");
                    cout << "You have pressed the wrong key!!!!Please try again!!!";
                    running = false;
                    system("CLS");
                    moving();
                }
                else
                {
                    system("CLS");
                    record();
                    running = false;
                }
                break;
            }

        }
        snakemove();
        Sleep(10);
    }

}

void SnakeMovement::print() {
    gotoxy(60, 60);
    system("Color 0B");
    cout << "       \t\tWELCOME TO THE\n\n" << endl;
    cout << "============================================================================================================================================================================\n\n" << endl;
    cout << "   |\\    /| =======  :\\    :  ======= \t\t\t\t =======  :\\    :     /\\     :  /  ...... \t\t              ......     /\\     |\\    /|  ......" << endl;
    cout << "   | \\  / |    |     : \\   :     |    \t\t\t\t |        : \\   :    /  \\    : /   :      \t\t             :          /  \\    | \\  / |  :     " << endl;
    cout << "   |  \\/  |    |     :  \\  :     |    \t\t\t\t |======  :  \\  :   /====\\   :/    :..... \t\t             :::::::   /====\\   |  \\/  |  :....." << endl;
    cout << "   |      |    |     :   \\ :     |     \t\t\t\t       |  :   \\ :  /      \\  :\\    :     \t\t             : :   :  /      \\  |      |  :     " << endl;
    cout << "   |      | =======  :    \\:  =======  \t\t\t\t ======|  :    \\: /        \\ : \\   :.....\t\t             :.:   : /        \\ |      |  :....." << endl;
    cout << "\n\n\n============================================================================================================================================================================\n\n" << endl;
    cout << "\n\t\t\t\t\t\t\t\tPress enter key to continue the game.............." << endl;
    cin.get();//getch();
    system("CLS");// to clear console window
    cout << "Here are the following game instructions to play the game" << endl;
    cout << "\n--------------------GAME INSTRUCTIONS--------------------" << endl;
    cout << "\n(1) Use W for UP, S for DOWN,D for RIGHT,A for LEFT arrow keys to move the snake in order to grab the food respectively" << endl;
    cout << "\n(2) Food will be generated at random positions of the screen which snake have to eat" << endl;
    cout << "\n(3) Everytime snake eat the food , length of the snake will be increased by 1 and thus the score" << endl;
    cout << "\n(4) Here only three lives will be provided.Life of the snake will be decreased when it hits the wall or to itself" << endl;
    cout << "\n(5) If you press any wrong key then only three chances would be given otherwise you will lose the game" << endl;
    cout << "\n(6) Press enter to play the game......ENJOY!!!" << endl;
    cin.get();
    system("CLS");
}


void SnakeMovement::loading() {

    int i;
    int  c = 176;
    gotoxy(65, 21);
    cout << ">>>>>>>>>>>>>>>>>>>LOADING>>>>>>>>>>>>>>>>>>>" << endl;
    gotoxy(65, 22);
    for (i = 0; i <= 44; i++) {
        Sleep(400);
        cout << char(c);
    }
    system("CLS");

}
void SnakeMovement::border() {
    gotoxy(0, 0);//it makes window to not flicker
    //system("CLS");// to clear console window
    int i, j, k;
    /*system("Color B5");//to give color to the text
    cout << "SnakeGame";
    system("Color 16");
    cout << " by";
    system("Color DE");
    cout << " Muskan\n\n";*/
    cout << "Snake Game by Muskan\n\n";
    for (i = 0; i < (borderwidth + 1); i++) {
        cout << "*"; // top wall
    }
    cout << endl;
    for (i = 0; i < borderheight; i++) {
        for (j = 0; j < borderwidth; j++) {
            if (j == 0) { //if it is first field
                cout << "*";
            }
            else if (i == Head.y0 && j == Head.x0) {
                cout << "O";//creates snake head part
            }
            else if (i == Food.y0 && j == Food.x0) {
                cout << "F";//creates food
            }
            else {
                bool printgame = false;//keeps track whether we print the tail segment to print tail
                for (k = 0; k < tailofsnake; k++) {
                    if (Body[k].x0 == j && Body[k].y0 == i) {
                        cout << "o";
                        printgame = true;
                    }
                }
                if (!printgame) {
                    cout << " ";//if we are not printing tail segment it will give blank space
                }
            }
            if (j == borderwidth - 1) {
                cout << "*";//it will print wall to next side
            }
        }
        cout << endl;
    }
    for (i = 0; i < (borderwidth + 1); i++) {
        cout << "*";//bottom wall
    }
    cout << endl;
    cout << "Score : " << score << "\t\t\tLives : " << lives << endl;

}


void SnakeMovement::snakemove() {
    int posx = Body[0].x0;
    int posy = Body[0].y0;
    int newposx, newposy;//these are used to make tail remember about prev coordinates
    Body[0].x0 = Head.x0;
    Body[0].y0 = Head.y0;
    for (int i = 1; i < tailofsnake; i++) {
        newposx = Body[i].x0;
        newposy = Body[i].y0;
        Body[i].x0 = posx;
        Body[i].y0 = posy;
        posx = newposx;
        posy = newposy;
    }
    switch (dir) {
    case LEFT: Head.x0--;
        break;
    case RIGHT: Head.x0++;
        break;
    case UP: Head.y0--;
        break;
    case DOWN: Head.y0++;
        break;
    default: break;
    }
    /*if (Head.x0 >= borderwidth) {
        Head.x0 = 0;
    }
    else if (Head.x0 < 0) {
        Head.x0 = borderwidth - 1;
    }
    else if (Head.y0 >= borderheight) {
        Head.y0 = 0;
    }
    else if (Head.y0 < 0) {
        Head.y0 = borderheight - 1;
    }*/
    if (Head.x0 == Food.x0 && Head.y0 == Food.y0) {
        score += 10;
        Food.x0 = rand() % borderwidth;
        Food.y0 = rand() % borderheight;
        tailofsnake++;
    }
    if (Head.x0 > borderwidth || Head.x0 < 0 || Head.y0 > borderheight || Head.y0 < 0) {
        lives--;
        if (lives > 0) {
            dir = STOP;
            Head.x0 = borderwidth / 2;
            Head.y0 = borderheight / 2;
            Food.x0 = rand() % borderwidth;
            Food.y0 = rand() % borderheight;
            moving();
        }
        else {
            record();
            system("CLS");
            exit(0);
        }
    }

    for (int i = 0; i < tailofsnake; i++) {
        if (Body[i].x0 == Head.x0 && Body[i].y0 == Head.y0) {
            lives--;
            if (lives > 0) {
                dir = STOP;
                Head.x0 = borderwidth / 2;
                Head.y0 = borderheight / 2;
                Food.x0 = rand() % borderwidth;
                Food.y0 = rand() % borderheight;
                moving();
            }
            else {
                record();
                system("CLS");
                exit(0);
            }

        }
    }
}


int main() {
    running = true;
    dir = STOP;//snake will not move until we start moving it
    Head.x0 = borderwidth / 2;
    Head.y0 = borderheight / 2;//snake will be centered initially
    Food.x0 = rand() % borderwidth;
    Food.y0 = rand() % borderheight;
    score = 0;
    lives = 3;
    SnakeMovement snakemove;
    snakemove.print();
    snakemove.loading();
    snakemove.moving();


    return 0;
}

void gotoxy(int x, int y) {
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}


void record() {
    system("CLS");
    char var;
    char name[100];
    cout << "Sorry,You have lose your chances!!!Better luck next time!!!\n\n";
    cout << "Enter player name : ";
    cin.getline(name, 100);
    time_t mytime;
    mytime = time(NULL);
    ofstream ofile("record.txt");
    ofile << name << endl;
    ofile << mytime << endl;
    ofile << score << endl;
    ofile.close();
    system("CLS");
    cout << "Press y if you want to see past records\n";
    cin >> var;
    system("CLS");
    if (var == 'y') {
        ifstream ifile("record.txt");
        ifile.getline(name, 100);
        cout << "Player Name : " << name << endl;
        cout << "Time of played game : " << mytime << endl;
        cout << "Score : " << score << endl;
        ifile.close();
    }
    _getch();
}

