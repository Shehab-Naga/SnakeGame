#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
using namespace sf;
#include "functions.h"
#include<string>
using namespace std;

int main()
{
srand(time(0));//seeds rand() with the return of time() to have better randomness
int snakeLength=3;
int direction=5;
snakeUnits u[25];
fruit f, bom;
obstacle obs[80];
Texture background, unit, fru, bomb, paus, start, gameOver,obstacl,lev2,lev3,victory;//our texture objects
bool n=1;
//loading images
background.loadFromFile("background.png");
unit.loadFromFile("red.png");
fru.loadFromFile("green.png");
bomb.loadFromFile("bomb.png");
paus.loadFromFile("pause.png");
start.loadFromFile("start.png");
gameOver.loadFromFile("gameOver.png");
obstacl.loadFromFile("obstacle.png");
victory.loadFromFile("victory.png");
////////////////////we may add the change of level based on the score in addition to speed.
//we make obs[n] where n is of lev3 then loop in the gameover loop for each level as we please (make a variable lev)
lev2.loadFromFile("LEV2.png");
lev3.loadFromFile("LEV3.png");
//////////////////
//spriting
Sprite sprite1(background);
Sprite sprite2(unit);
Sprite sprite3(fru);
Sprite sprite3_(bomb);
Sprite sprite4(paus);
Sprite sprite5(start);
Sprite sprite6(gameOver);
Sprite sprite7(obstacl);
Sprite sprite8(victory);
//sprite7.setRotation(90.f);
//our text
Font fot;
fot.loadFromFile("arial.ttf");
Text txt1, txt2, txt3, txt4;
txt1.setFont(fot);
txt2.setFont(fot);
txt3.setFont(fot);
txt4.setFont(fot);
int score =0;
string scre= to_string(score);
txt1.setString(scre);
txt2.setString("Score:");
txt3.setString("press P to pause");
txt4.setString("target:20");
/////
Music music, crunch, gameover;
gameover.openFromFile("die.ogg");
gameover.setVolume(100);
crunch.openFromFile("eat.ogg");
crunch.setVolume(100);
music.openFromFile("big.ogg");
music.setVolume(30);
music.play();
/////
//flags to act
int winFlag=0;
int fruFlag;
int pause=0;
int gameoverflag=0;

Clock clk; //a stopwatch-like object. it starts counting when declared and can be restarted.
float timer=0;
float delay=.1;
float time,timer_crunch=0,timer_gameover=0;
/////////////////////////////////////////////////////////////////////////////////////////////////initializing things ends here

initialize_pos_f_u(u,f,bom);

initialize_pos_obstacles(obs);

RenderWindow window(VideoMode(960,960), "Snake Yaaaaaaaaaaay",Style::Close );

Event e;
while (window.isOpen()){ //game loop Ba2aaa

    times(clk, timer, time,timer_crunch);// updating the window after each 0.1 s

    update_direction_end_pause(e,pause,direction,window);//responding to key pressing

    restart(gameoverflag,winFlag,snakeLength,direction,score,delay,scre,txt1,u,f,bom); //R is pressed

    nextFrame(timer_gameover,gameover,timer_crunch,pause,timer,gameoverflag,winFlag,delay,snakeLength,fruFlag,direction,score,scre,txt1,u,obs,f,bom,crunch);

    window.clear();

    draw_images(n,score,window,pause,u,f,bom,direction,gameoverflag,winFlag,snakeLength,sprite1,sprite2,sprite3,sprite3_,sprite4,sprite5,sprite6,sprite7,sprite8);

    draw_text(window,txt1,txt2,txt3,txt4);

    window.display();

}//end of game loop
    return 0;
}






