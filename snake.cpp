#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height=40;
const int width=40;

int x,y,fruitX,fruitY;
int score = 0;
int tailX[100], tailY[100], ntail;

enum eDirection {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

void Setup(){
    gameOver=false;
    dir = STOP;
    x = width / 2; // zone de départ du serpent
    y = height / 2;
    fruitX = rand() %width; // spawn random des candies
    fruitY = rand() %height;
}
void Draw(){

    system("CLS"); // Clear le terminal

    for(int i = 0; i < width; i++){ // Cadre Haut
        cout<<"#";
    }cout<<endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(j == 0 | j == width-1){
                cout << "#";
            }else if (i == y && j == x){ // Tête du serpent
                cout << "O";
            }else if (i == fruitY && j == fruitX){ // Candies
                cout << "F";
            }else {

                bool print = false;

                for(int k = 0; k < ntail; k++){
                    if(i == tailY[k] && j == tailX[k]){ //print de la queue quand on mange un fruit
                        cout << "o";
                        print = true;
                    }
                }if (!print) {cout << " ";}
            }
        }cout << endl;
    }

    for(int i = 0; i < width; i++){ // Cadre Bas
        cout << "#";
    }cout << endl;
    cout << endl;
    cout << "Score: "<<score<<endl; // print le score

}
void Input(){
   if(_kbhit()){ // retourne une valeur différente de zéro si une touche a été enfoncée
       switch(_getch()){ // les _getch fonctions et _getwch lisent un caractère unique à partir de la console sans renvoyer le caractère.
           case 'z':
                    dir = UP;
                    break;

           case 'q':
                    dir = LEFT;
                    break;

            case 'd':
                    dir = RIGHT;
                    break;

           case 's':
                    dir = DOWN;
                    break;
            default:
            break;
       }
   } 
}
void Logic(){

    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for(int i = 1; i < ntail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir){ // si up est enclenché la valeur y décroit etc...
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    if (x < 0 | x > width | y < 0 | y > height){ // si on dépasse de la map GAMEOVER
        gameOver = true;
    }

    for(int i = 0; i < ntail; i++){
        if(x == tailX[i] && y ==tailY[i]){
            gameOver = true;
        }

    }


    if (x == fruitX && y == fruitY){ // si on mange un fruit score +10 et un autre fruit spawn
        score += 10;
        fruitX = rand() %width;
        fruitY = rand() %height;
        ntail++; // taille de la queue augmente
    }
        
}

int main(){

    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(200);
    }
    return 0;
}