#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
#include<string>
using namespace std;
class snakeUnits{
public:
    int x,y;
};

class fruit{
public:
    int x,y;
};

class obstacle{
public:
    int x,y;
};
void initialize_pos_f_u(snakeUnits*u, fruit &f,fruit&bom){
    u[0].x=5; u[0].y=7;
    u[1].x=5; u[1].y=6;
    u[2].x=5; u[2].y=5;
    f.x=15; f.y=15;
    bom.x=10; bom.y=13;
}
void initialize_pos_obstacles(obstacle*obs){
    for(int i=0;i<7;i++){
    obs[i].x=0; obs[i].y=i;
}
int yCordin=23;
for(int i=7;i<14;i++){
    obs[i].x=0; obs[i].y=yCordin;
    yCordin++;
}
int yCordin2=0;
for(int i=14;i<21;i++){
    obs[i].x=29; obs[i].y=yCordin2;
    yCordin2++;
}
int yCordin3=23;
for(int i=21;i<28;i++){
    obs[i].x=29; obs[i].y=yCordin3;
    yCordin3++;
}
//second, the horizontal obstacles
int xCordin=1;
for(int i=28;i<34;i++){
    obs[i].x=xCordin; obs[i].y=0;
    xCordin++;
}
int xCordin2=23;
for(int i=34;i<40;i++){
    obs[i].x=xCordin2; obs[i].y=0;
    xCordin2++;
}
int xCordin3=1;
for(int i=40;i<46;i++){
    obs[i].x=xCordin3; obs[i].y=29;
    xCordin3++;
}
int xCordin4=23;
for(int i=46;i<52;i++){
    obs[i].x=xCordin4; obs[i].y=29;
    xCordin4++;
}
//the two obstacles in the center
int xCordin5=7;
for(int i=52;i<66;i++){
    obs[i].x=xCordin5; obs[i].y=9;
    xCordin5++;
}
int xCordin6=7;
for(int i=66;i<80;i++){
    obs[i].x=xCordin6; obs[i].y=18;
    xCordin6++;
}
}
void times(Clock &clk, float &timer, float &time, float&timer_crunch){
    time=clk.getElapsedTime().asSeconds();
    //timer_crunch=clk.getElapsedTime().asSeconds();
    clk.restart();
    timer+=time;
    //timer_crunch+=time;
}
void update_direction_end_pause(Event&e,int &pause, int &direction,Window&window){
    while (window.pollEvent(e)){ //responding to mouse events like clicking on the window
        if (e.type == Event::Closed)
            window.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)){
         pause=0; direction=1;}
    if (Keyboard::isKeyPressed(Keyboard::Right)){
         pause=0; direction=2;}
    if (Keyboard::isKeyPressed(Keyboard::Up)){
         pause=0; direction=3;}
    if (Keyboard::isKeyPressed(Keyboard::Down)){
         pause=0; direction=0;}
    if (Keyboard::isKeyPressed(Keyboard::P)){
        pause=1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)){ //closing the game with escape button
        window.close();
    }
}
void restart(int&gameoverflag, int&winFlag,int&snakeLength,int&direction,int&score,float&delay,string&scre,Text&txt1,snakeUnits*u,fruit&f,fruit&bom){
    if (Keyboard::isKeyPressed(Keyboard::R)){
        gameoverflag=0;
        winFlag=0;
        snakeLength=3;
        direction=5;
        score=0;
        delay=.1;
        scre= to_string(score);
        txt1.setString(scre);
        u[0].x=5; u[0].y=7;
        u[1].x=5; u[1].y=6;
        u[2].x=5; u[2].y=5;
        f.x=15; f.y=15;
        bom.x=10; bom.y=13;
    }
}
void update(float&timer_crunch,float&timer,float&delay,int&snakeLength, int&fruFlag,int&direction,int&score,string&scre,Text&txt1,snakeUnits*u,obstacle*obs,fruit&f,fruit&bom,Music&crunch){
    if (direction!=5){
            for (int i=snakeLength-1;i>0;--i){ //every cube takes the position of the previous one (head is first)
                    u[i].x=u[i-1].x; u[i].y=u[i-1].y;
            }

            /////////taking care of the head
            if ((direction==0)&&((u[2].y-u[1].y)!=1)){
                u[0].y+=1;}else if((direction==0)&&((u[2].y-u[1].y)==1)){u[0].y-=1;
            }
            if ((direction==1)&&((u[1].x-u[2].x)!=1)){
                u[0].x-=1;}else if ((direction==1)&&((u[1].x-u[2].x)==1)){u[0].x+=1;
            }
            if ((direction==2)&&((u[2].x-u[1].x)!=1)){
                u[0].x+=1;}else if ((direction==2)&&((u[2].x-u[1].x)==1)){u[0].x-=1;
            }
            if ((direction==3)&&((u[1].y-u[2].y)!=1)){
                u[0].y-=1;}else if((direction==3)&&((u[1].y-u[2].y)==1)){u[0].y+=1;
            }
            if (u[0].x>29){ u[0].x=0;}
            if (u[0].x<0) { u[0].x=29;}
            if (u[0].y>29){ u[0].y=0;}
            if (u[0].y<0) { u[0].y=29;}
            ////////////////////////////////////////////////////////////////
//            if(timer_crunch>2000){
//                crunch.stop();
//                timer_crunch=0;
//            }
//            timer_crunch+=100;
            if ((u[0].x==f.x) && (u[0].y==f.y)){ //snake have eaten a fruit. change length, score, and fruit position
                    crunch.play();
                    snakeLength++; u[snakeLength-1].x=u[snakeLength-2].x;
                    u[snakeLength-1].y=u[snakeLength-2].y;
                    score++;
                    scre=to_string(score);
                    txt1.setString(scre);
                    fruFlag=1;
                while(fruFlag==1){ //making sure the new fruit position is valid
                    fruFlag=0;
                    f.y=rand()%29+0; f.x=rand()%29+0;
                    bom.y=rand()%29+0; bom.x=rand()%29+0;
                    for (int i=0;i<snakeLength;i++){
                        if (((f.x==u[i].x) && (f.y==u[i].y))||((bom.x==u[i].x) && (bom.y==u[i].y))){
                            fruFlag=1;
                        }
                    }
                    for (int i=0;i<80;i++){
                        if(((f.x==obs[i].x)&&(f.y==obs[i].y))||((bom.x==u[i].x) && (bom.y==u[i].y))){
                        fruFlag=1;
                        }

                    }
                }
            }
    }
}
void leveling(int&score,float&delay){
    //level 2
        if(score==5){
            delay=.08;
        }
    //level 3
        if(score==10){
            delay=.06;
        }
    //level 4
        if(score==18){
            delay=.05;
        }
}

void Gameover(Music&gameover,int&snakeLength,snakeUnits*u,obstacle*obs,int&gameoverflag,fruit&bom){
        for (int i=1;i<snakeLength;i++){
            if (u[0].x==u[i].x && u[0].y==u[i].y){
                gameover.play();
                gameoverflag=1;
            }
        }
        for (int i=0;i<80;i++){
            if(u[0].x==obs[i].x && u[0].y==obs[i].y){
                gameover.play();
                gameoverflag=1;
            }
        }
        if(bom.x==u[0].x&&bom.y==u[0].y){
            gameoverflag=1;
            gameover.play();
        }
}
void draw_text(RenderWindow&window,Text&txt1,Text&txt2,Text&txt3,Text&txt4){
    txt1.setCharacterSize(28);
    txt2.setCharacterSize(25);
    txt1.setPosition(32*2.5,0);
    window.draw(txt1);
    window.draw(txt2);
    txt3.setCharacterSize(25);
    txt3.setPosition(32*23.3,0);
    window.draw(txt3);
    txt4.setCharacterSize(25);
    txt4.setPosition(32*3.5,0);
    window.draw(txt4);
}

void draw_images(bool n,int&score,RenderWindow&window,int&pause,snakeUnits*u,fruit&f,fruit&bom,int&direction,int&gameoverflag,int&winFlag,int&snakeLength,Sprite&sprite1,Sprite&sprite2,Sprite&sprite3,Sprite&sprite3_,Sprite&sprite4,Sprite&sprite5,Sprite&sprite6,Sprite&sprite7,Sprite&sprite8){
    window.draw(sprite1);
    window.draw(sprite7);
//    if((score==1)&&n){
//        sprite7.setRotation(90.f);
//        n=0;
//    }
    for (int i=0;i<snakeLength;i++){
        sprite2.setPosition(u[i].x*32, u[i].y*32);
        window.draw(sprite2);
    }
    sprite3.setPosition(f.x*32,f.y*32);
    window.draw(sprite3);
    sprite3_.setPosition(bom.x*32,bom.y*32);
    window.draw(sprite3_);
    if(pause!=0){
        window.draw(sprite4);
    }
    if ((direction==5)&&(gameoverflag==0)&&(winFlag==0)){
        window.draw(sprite5);
    }
    if (gameoverflag==1){
        window.draw(sprite6);
    }
    if(winFlag==1){
        window.draw(sprite8);
    }
}
void nextFrame(float&timer_gameover,Music&gameover,float&timer_crunch,int&pause,float&timer,int&gameoverflag,int&winFlag,float&delay,int&snakeLength,int&fruFlag,int&direction,int&score,string&scre,Text&txt1,snakeUnits*u,obstacle*obs,fruit&f,fruit&bom,Music&crunch){
    if(timer>delay){
        timer=0;
        if(timer_crunch>2000){
                crunch.stop();
                //gameover.stop();
                timer_crunch=0;
        }
        timer_crunch+=100;
        if(timer_gameover>9000){
                //crunch.stop();
                gameover.stop();
                timer_gameover=0;
        }
        timer_gameover+=100;
        if((pause==0)&&(gameoverflag==0)&&(winFlag==0)){

            update(timer_crunch,timer,delay,snakeLength,fruFlag,direction,score,scre,txt1,u,obs,f,bom,crunch);

            Gameover(gameover,snakeLength,u,obs,gameoverflag,bom);

            leveling(score,delay);

            if(score==30){
                winFlag=1;
            }

        }
    }
}
#endif // FUNCTIONS_H_INCLUDED
