//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
#include<fstream>
using namespace std;

//global vars
double startx=350,starty=400;

//snake start
int bodycolor =0;
int snakex=0,snakey=0;
int size =2;
int level= 1;
int score = 1;
int prevscore;
int featen =0;

//enemy snake
int estartx=220,estarty=220;
int esize = 5;
int dir = GLUT_KEY_RIGHT;
int backdir = GLUT_KEY_LEFT;
//movement esnake
int etailx[650] = {210,200,190,180,170,};
int etaily[650] = {220,220,220,220,220,};
int eprevx= estartx;
int eprevy= estarty;
int eprev2x=etailx[0], eprev2y=etaily[0];

//normal food vars
int foodi=0;
int food[5][2] = { };
int ftime=0;
int flim= 30;

//super food vars
int sfoodx = GetRandInRange(20,630);
int sfoody = GetRandInRange(20,570);
int sftime = 0;
int slim = 180;
int dsfoodtime = 0;
bool dsfood = false;

int prevkey = GLUT_KEY_RIGHT;
bool hitwall = false;

//movement
int tailx[650] = {325,320,};
int taily[650] = {405,405,};
int prevx= startx+snakex;
int prevy= starty+snakey;
int prev2x=tailx[0], prev2y=taily[0];


//hurdels
int uUpx=-50, uUpy=-50;
int uDownx = -50, uDowny = -50;
int usidex = -50, usidey = -50, orientation=0;
int hurdelcounter=0;
int hlim = 150;

////menue
int selected=0;
int choice =1;

//
int playdead =0;

int speed =1;

//file vars
ifstream input;

ofstream outfile;


void genuUp(){
    uUpx = GetRandInRange(60,580);
    uUpy = GetRandInRange(60,530);
    while(uUpx%7 !=0 && uUpx != (startx + snakex) && uUpy !=(starty + snakey) ){
        uUpx = GetRandInRange(60,580);
        uUpy = GetRandInRange(60,530);
    }
}
void genuDown(){
    uDownx = GetRandInRange(60,580);
    uDowny = GetRandInRange(60,530);
    while(uDownx%7 !=0 && uDownx != (startx + snakex) && uDowny !=(starty + snakey)&&
            uDownx != uUpx && uDowny != uUpy){
        uDownx = GetRandInRange(60,580);
        uDowny = GetRandInRange(60,530);
    }
}
void genuSide(){
    orientation = rand()%2;
    usidex = GetRandInRange(60,580);
    usidey = GetRandInRange(60,530);
    while(usidex%7 !=0 && usidex != (startx + snakex) && usidey !=(starty + snakey)&&
          usidex != uUpx && usidey != uUpy && usidex != uDownx && usidey != uDowny){
        usidex = GetRandInRange(60,580);
        usidey = GetRandInRange(60,530);
    }
}

void uUpHurdel(){
    DrawSquare(uUpx,uUpy,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx,uUpy-15,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx,uUpy-30,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx+15,uUpy-45,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx+30,uUpy-45,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx+45,uUpy,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx+45,uUpy-15,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uUpx+45,uUpy-30,15,colors[DARK_SEA_GREEN]);
}

void uDownHurdel(){
    DrawSquare(uDownx,uDowny,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx,uDowny+15,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx,uDowny+30,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx+15,uDowny+45,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx+30,uDowny+45,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx+45,uDowny,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx+45,uDowny+15,15,colors[DARK_SEA_GREEN]);
    DrawSquare(uDownx+45,uDowny+30,15,colors[DARK_SEA_GREEN]);
}

void uSideHurdel(){
    if(orientation == 0){
        DrawSquare(usidex,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+15,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+30,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+45,usidey+15,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+45,usidey+30,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex,usidey+45,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+15,usidey+45,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+30,usidey+45,15,colors[DARK_SEA_GREEN]);
    }
    else{
        DrawSquare(usidex+15,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+30,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+45,usidey,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex, usidey+15,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex,usidey+30,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+15,usidey+45,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+30,usidey+45,15,colors[DARK_SEA_GREEN]);
        DrawSquare(usidex+45,usidey+45,15,colors[DARK_SEA_GREEN]);
    }
}

void collideUp(){
    if(
        ((startx + snakex)> uUpx && (startx + snakex) < uUpx+15 &&
        (starty + snakey) > uUpy-30 && (starty + snakey) < uUpy+15)
        ||
        ((startx + snakex)> uUpx+15 && (startx + snakex) < uUpx+45 &&
        (starty + snakey) > uUpy-45 && (starty + snakey) < uUpy-30)
        ||
        ((startx + snakex)> uUpx+45 && (startx + snakex) < uUpx+60 &&
        (starty + snakey) > uUpy-30 && (starty + snakey) < uUpy+15)

    ){
        hitwall = true;
    }
}
void collideDown(){
    if(
        ((startx + snakex)> uDownx && (startx + snakex) < uDownx+15 &&
        (starty + snakey) > uDowny && (starty + snakey) < uDowny+45)
        ||
        ((startx + snakex)> uDownx+15 && (startx + snakex) < uDownx+45 &&
        (starty + snakey) > uDowny+45 && (starty + snakey) < uDowny+60)
        ||
        ((startx + snakex)> uDownx+45 && (startx + snakex) < uDownx+60 &&
        (starty + snakey) > uDowny && (starty + snakey) < uDowny+45)

    ){
        hitwall = true;
    }
}
void collideSide(){
    if(orientation ==0){
        if(
            ((startx + snakex)> usidex && (startx + snakex) < usidex+45 &&
            (starty + snakey) > usidey && (starty + snakey) < usidey+15)
            ||
            ((startx + snakex)> usidex+45 && (startx + snakex) < usidex+60 &&
            (starty + snakey) > usidey+15 && (starty + snakey) < usidey+45)
            ||
            ((startx + snakex)> usidex && (startx + snakex) < usidex+45 &&
            (starty + snakey) > usidey+45 && (starty + snakey) < usidey+60)

        ){
            hitwall = true;
        }
    }
    else if(orientation ==1){
        if(
            ((startx + snakex)> usidex+15 && (startx + snakex) < usidex+60 &&
            (starty + snakey) > usidey && (starty + snakey) < usidey+15)
            ||
            ((startx + snakex)> usidex && (startx + snakex) < usidex+15 &&
            (starty + snakey) > usidey+15 && (starty + snakey) < usidey+45)
            ||
            ((startx + snakex)> usidex+15 && (startx + snakex) < usidex+60 &&
            (starty + snakey) > usidey+45 && (starty + snakey) < usidey+60)

        ){
            hitwall = true;
        }
    }
}



void genfood(int &fx, int &fy){
    int x = GetRandInRange(10,640);
    int y=GetRandInRange(10,580);

    while((x%5 !=0) && (y%5!=0) &&
    !(x > uUpx && x< uUpx+15) &&
     !(y > uUpy-30 && y < uUpy+15)
    &&
    !(x > uUpx+15 && x < uUpx+45) &&
    !(y> uUpy-45 && y < uUpy-30)
    &&
    !(x > uUpx+45 && x < uUpx+60)&&
    !(y > uUpy-30 && y < uUpy+15)
    &&
    !(x > uDownx && x < uDownx+15) &&
    !(y > uDowny && y < uDowny+45)
    &&
    !(x > uDownx+15 && x < uDownx+45) &&
    !(y > uDowny+45 && y < uDowny+60)
    &&
    !(x > uDownx+45 && x < uDownx+60) &&
    !(y > uDowny && y < uDowny+45)

){
        x = GetRandInRange(10,640);
        y=GetRandInRange(10,580);
    }
    fx =x;
    fy = y;

}

void collisionNFood(double startx, double starty){

    for(int i=0; i<5; i++){
        //approach from right

        if((starty+snakey) < food[i][1]+10 && (starty + snakey) > food[i][1]-10){

            if((startx + snakex)> food[i][0]-10 && (startx + snakex)< food[i][0]+10){

                tailx[size] = (tailx[size-1]-10);
                taily[size] = (taily[size-1]-10);

                size +=1;
                score +=5;
                featen+=5;
                DrawString(food[i][0]+5,food[i][1]+5,"+5", colors[ORANGE]);
                food[i][0] = -20;
                food[i][1] = -20;



            }
        }
    }
}

void collisionSFood(double startx, double starty){

    if((starty+snakey) < sfoody+15 && (starty + snakey) > sfoody-15){
        if((startx + snakex)> sfoodx-15 && (startx + snakex)< sfoodx+15){

            score +=20;
            featen +=20;
            DrawString(sfoodx+5,sfoody+5,"+20!!", colors[ORANGE]);

            sfoodx = -50;
            sfoody = -50;

        }
    }
}

void collisionwall(){
    int a = startx + snakex;
    int b = starty + snakey;

    if( a >640 || a <10 || b >580|| b ==5) {
           hitwall = true;
       }

}

void colissionSelf(){
    for(int i=0; i<size; i++){
        if((starty+snakey) < taily[i]+2 && (starty + snakey) > taily[i]-2){
            if((startx + snakex)> tailx[i]-5 && (startx + snakex)< tailx[i]+5){

                hitwall = true;
                break;

            }
        }
    }
}


void moveSnake(){
    for(int i=0; i<size; i++){
        colissionSelf();
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
}

void moveEsnake(){
    eprevx= estartx;
    eprevy= estarty;
    for(int i=0; i<esize; i++){
    eprev2x = etailx[i];
    eprev2y = etaily[i];
    etailx[i] = eprevx;
    etaily[i] = eprevy;
    eprevx = eprev2x;
    eprevy = eprev2y;
}
}

void ecollisionwall(){
    int a = estartx;
    int b = estarty;
    if(a > 630 && b>570 && dir == GLUT_KEY_UP){
        dir = GLUT_KEY_LEFT;
        backdir = GLUT_KEY_RIGHT;
    }
    else if(a > 630 && b>570 && dir == GLUT_KEY_RIGHT){
        dir = GLUT_KEY_DOWN;
        backdir = GLUT_KEY_UP;
    }
    else if(a > 630 && b<=5 && dir == GLUT_KEY_DOWN){
        dir = GLUT_KEY_LEFT;
        backdir = GLUT_KEY_RIGHT;

    }
    else if(a > 630 && b<=5 && dir == GLUT_KEY_RIGHT){
        dir = GLUT_KEY_UP;
        backdir = GLUT_KEY_DOWN;

    }
    else if(a < 10&& b>570 && dir == GLUT_KEY_LEFT){
        dir = GLUT_KEY_DOWN;
        backdir = GLUT_KEY_UP;

    }
    else if(a < 10&& b>570 && dir == GLUT_KEY_UP){
        dir = GLUT_KEY_RIGHT;
        backdir = GLUT_KEY_LEFT;

    }
    else if(a <10 && b<=5 && dir == GLUT_KEY_DOWN){
        dir = GLUT_KEY_RIGHT;
        backdir = GLUT_KEY_LEFT;

    }
    else if(a <10 && b<=5 && dir == GLUT_KEY_LEFT){
        dir = GLUT_KEY_UP;
        backdir = GLUT_KEY_DOWN;

    }
    else{

    if( a >630 && backdir== GLUT_KEY_LEFT){
           if(rand()%2){
               dir = GLUT_KEY_UP;
               backdir = GLUT_KEY_DOWN;
           }
           else{
               dir = GLUT_KEY_DOWN;
               backdir = GLUT_KEY_UP;
           }
   }
   if(a <10 && backdir == GLUT_KEY_RIGHT){
          if(rand()%2){
              dir = GLUT_KEY_UP;
              backdir = GLUT_KEY_DOWN;
          }
          else{
              dir = GLUT_KEY_DOWN;
              backdir = GLUT_KEY_UP;
          }
   }
   if(b >580 && backdir == GLUT_KEY_UP){
          if(rand()%2){
              dir = GLUT_KEY_LEFT;
              backdir = GLUT_KEY_RIGHT;
          }
          else{
              dir = GLUT_KEY_RIGHT;
              backdir = GLUT_KEY_LEFT;
          }
   }
   if(b <=5 && backdir == GLUT_KEY_DOWN){
          if(rand()%2){
              dir = GLUT_KEY_LEFT;
              backdir = GLUT_KEY_RIGHT;
          }
          else{
              dir = GLUT_KEY_RIGHT;
              backdir = GLUT_KEY_LEFT;
          }
   }
    }

}

void game(){
    //my snowman
    if(level==2){
        speed = 5;
        flim = 80;
    }
    if(level > 3){
        speed = 10;
        flim = 150;
        slim = 380;
        hlim = 550;
    }

    DrawCircle( 120 , 250 , 65 , colors[WHITE]); // This will draw a circle at x=200,y=200 of radius 50
    DrawCircle( 120 , 100 , 100 , colors[WHITE]);
    DrawCircle( 100 , 270 , 10 , colors[BLACK]);
    DrawCircle( 140 , 270 , 10 , colors[BLACK]);
    DrawTriangle( 110, 230 , 120, 260, 130, 250, colors[ORANGE] );

    DrawString(120,620,"Level: "+ to_string(level),colors[BLACK]);
    DrawLine(120,605,(120+featen),605,15, colors[LAWN_GREEN]);
    DrawLine((120+featen) , 605, 200,605,15, colors[WHITE]);

    DrawString(450,620,"Your Score: " + to_string(score),colors[BLACK]);

    //my borders
    DrawLine( 0 , 0 ,  0 , 590 , 10 , colors[MISTY_ROSE] );
    DrawLine( 0  ,0 ,  650 , 0 , 10 , colors[MISTY_ROSE] );
    DrawLine( 650  ,0 ,  650 , 590 , 10 , colors[MISTY_ROSE] );
    DrawLine( 0, 590, 650, 590, 10, colors[MISTY_ROSE]);

    //track previous key pressed
    if(prevkey == GLUT_KEY_LEFT){
        colissionSelf();
        snakex -=5;
        //moveSnake();
    }
    else if(prevkey == GLUT_KEY_RIGHT){
        colissionSelf();
        snakex +=5;
        //moveSnake();
    }
    else if(prevkey == GLUT_KEY_UP){
        colissionSelf();
        snakey +=5;
        //moveSnake();
    }
    else if (prevkey == GLUT_KEY_DOWN) {
        colissionSelf();
        snakey-=5;
        //moveSnake();
    }
    moveSnake();
    collideUp();
    collideDown();
    collideSide();
    //Snake
    bodycolor++;
    if(bodycolor == 139){
        bodycolor =0;
    }
    if(prevkey == GLUT_KEY_RIGHT){
        DrawCircle(startx+snakex+10, starty+snakey+5, 5, colors[RED]);
    }
    else if(prevkey == GLUT_KEY_UP){
        DrawCircle(startx+snakex+5, starty+snakey+10, 5, colors[RED]);
    }
    else if(prevkey == GLUT_KEY_DOWN){
        DrawCircle(startx+snakex+5, starty+snakey, 5, colors[RED]);
    }
    else{
        DrawCircle(startx+snakex, starty+snakey+5, 5, colors[RED]);
    }
      for(int i=0; i<size;i++){

          for(int j=0; j<size; j++){
              DrawSquare(tailx[j], taily[j], 10, colors[bodycolor]);
          }
          moveSnake();
          collideUp();
          collideDown();
          collideSide();
      }

    //draw esnake
    //esnake
    if (dir == GLUT_KEY_LEFT && selected == 13 /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        //colissionSelf();
        ::estartx-=5;
        ecollisionwall();
        //prevkey = key;


    } else if (dir== GLUT_KEY_RIGHT && selected == 13 /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
        //colissionSelf();
        ::estartx+=5;
        ecollisionwall();
        //prevkey = key;

    } else if (dir== GLUT_KEY_UP && selected == 13) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        //colissionSelf();
        ::estarty+=5;
        ecollisionwall();
        //prevkey = key;

    }
    else if (dir == GLUT_KEY_DOWN && selected == 13)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
        //colissionSelf();
        ::estarty-=5;
        ecollisionwall();
        //prevkey = key;
    }
    if(dir== GLUT_KEY_RIGHT){
        DrawCircle(estartx+10, estarty+5, 5, colors[BLUE]);
    }
    else if(dir == GLUT_KEY_UP){
        DrawCircle(estartx+5, estarty+10, 5, colors[BLUE]);
    }
    else if(dir == GLUT_KEY_DOWN){
        DrawCircle(estartx+5, estarty, 5, colors[BLUE]);
    }
    else{
        DrawCircle(estartx, estarty+5, 5, colors[BLUE]);
    }
      for(int i=0; i<esize;i++){

          for(int j=0; j<esize; j++){
              DrawSquare(etailx[j], etaily[j], 10, colors[BLUE]);
          }
          //moveSnake();
          //collideUp();
          //collideDown();
          //collideSide();
      }
      moveEsnake();



    //display food
    if(ftime==flim){
        genfood(food[foodi][0],food[foodi][1]);
        foodi++;
        if(foodi ==5){
            foodi=0;
        }
        ftime=0;
    }

    for(int j=0; j<5; j++){
        DrawCircle(food[j][0],food[j][1],5,colors[ORANGE]);
    }
    //detect collision with normal food
    collisionNFood(startx, starty);


    //display super food
    if(sftime == slim){
        dsfood = true;
    }
    if(dsfood){
        DrawCircle(sfoodx, sfoody,10,colors[BLUE_VIOLET]);
        dsfoodtime++;
    }
    if(dsfoodtime == 100){
        dsfood = false;
        sftime = 0;
        sfoodx = GetRandInRange(20,630);
        sfoody = GetRandInRange(20,570);
        dsfoodtime=0;
    }
    //detect colission with superfood
    collisionSFood(startx,starty);

    //display hurdels
    if(hurdelcounter > hlim && level==2){
        genuUp();
        hurdelcounter=0;

    }
    else if(hurdelcounter > hlim && level==3){
        genuUp();
        genuDown();
        hurdelcounter=0;
    }
    else if(hurdelcounter > hlim && level>3){
        genuUp();
        genuDown();
        genuSide();
        hurdelcounter=0;
    }
    if(level ==2){
        uUpHurdel();
        //detect colission
        collideUp();

    }
    else if(level ==3){
        uUpHurdel();
        uDownHurdel();
        //detect colission
        collideUp();
        collideDown();
    }
    else if(level >3){
        uUpHurdel();
        uDownHurdel();
        uSideHurdel();
        //detect colission
        collideUp();
        collideDown();
        collideSide();
    }

    //detect wall collision
    collisionwall();


}

void dead(){
    //my snowman
    DrawCircle( 120 , 250 , 65 , colors[RED]); // This will draw a circle at x=200,y=200 of radius 50
    DrawCircle( 120 , 100 , 100 , colors[RED]);
    DrawCircle( 100 , 270 , 10 , colors[BLACK]);
    DrawCircle( 140 , 270 , 10 , colors[BLACK]);
    DrawTriangle( 110, 230 , 120, 260, 130, 250, colors[YELLOW] );

    DrawString(290,380,"RIP SNEK ",colors[BLACK]);
    DrawString(315,360," :( ",colors[BLACK]);
    DrawString(290,340,"Game Over! ",colors[BLACK]);
    DrawString(280,320,"Your Score: " + to_string(score),colors[BLACK]);
    DrawString(280,200,"Press R to goto Menue",colors[BLACK]);
    //DrawString(280,100,"Press S to continue",colors[BLACK]);

    if(score > prevscore){
        DrawString(280,290,"NEW HIGH SCORE!",colors[BLACK]);
        outfile.open("Highscore.txt");
        outfile << score;
        outfile.close();
    }

}

void reset(){
    snakex=0,snakey=0;
    size =2;
    level= 1;
    score = 1;
    featen =0;

    //normal food vars
    foodi=0;
    ftime=0;
    flim= 30;

    //super food vars
    sfoodx = GetRandInRange(20,630);
    sfoody = GetRandInRange(20,570);
    sftime = 0;
    slim = 180;
    dsfoodtime = 0;
    dsfood = false;

    prevkey = GLUT_KEY_RIGHT;
    hitwall = false;

    //movement
    tailx[0] = 325;
    tailx[1] = 320;
    taily[0] = 405;
    taily[1] = 405;
    prevx= startx+snakex;
    prevy= starty+snakey;
    prev2x=tailx[0], prev2y=taily[0];

    uUpx = -50;
    uUpy = -50;
    uDownx = -50;
    uDowny = -50;
    hlim = 150;


    ////menue
    selected=0;
    choice =1;
    playdead = 0;
    speed =1;
}

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

void Display(){
    prevx= startx+snakex;
    prevy= starty+snakey;
    ftime++;
    sftime++;
    hurdelcounter++;
    if(featen >= 80){
        level+=1;
        featen -=80;
    }

    glClearColor(0.3/*Red Component*/, 0.3/*Green Component*/,
                0.3/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors

    if(selected !=13){
        DrawString(220,420,"DONT STEP ON SNEK", colors[ALICE_BLUE]);
        //backhighlight
        switch(choice){
            case 1:
                DrawRoundRect(250,335,100,30,colors[15],2);
                break;
            case 2:
                DrawRoundRect(250,305,175,30,colors[15],2);
                break;
            case 3:
                DrawRoundRect(250,275,80,30,colors[15],2);

                break;
            case 4:
                choice =1;
                break;
            case 0:
                choice = 3;
                break;
        }

        DrawString(260,340,"START " ,colors[BLACK]);
        DrawString(260,310,"HIGH SCORE ",colors[BLACK]);
        DrawString(260,280,"EXIT ",colors[BLACK]);

    }

    else{
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.


    //DrawSquare( 300 , 300 ,100,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
    //DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
    //DrawString( 50, 570, "You will  use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
    // DrawSquare(220,220,20, colors[YELLOW]);
        if(choice == 1){
            if(!hitwall){
                game();
                moveSnake();
            }
            else{
                if(playdead == 0){
                    system("canberra-gtk-play -f DieSound.ogg");
                    playdead = 1;
                }
                dead();
            }
        }
        if(choice == 2){
            input.open("Highscore.txt");
            input >> prevscore;
            input.close();
            DrawString(220,320,"Your Last High Score: " + to_string(prevscore),colors[BLACK]);
            DrawString(220,295,"Press R to goto Menue",colors[BLACK]);
        }
        if(choice == 3){
            exit(1);
        }

    }
	//                    v1( x,y )   v2( x,y )  , v3( x,y )
    //DrawTriangle( 300+x, 50+y , 500+x, 50+y , 400+x , 250+y, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
   glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT && prevkey != GLUT_KEY_RIGHT && selected == 13 /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        colissionSelf();
        ::snakex-=5;
        collisionwall();
        prevkey = key;

        				// what to do when left key is pressed...


    } else if (key == GLUT_KEY_RIGHT  && prevkey != GLUT_KEY_LEFT && selected == 13 /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
        colissionSelf();
        ::snakex+=5;
        collisionwall();
        prevkey = key;

    } else if (key == GLUT_KEY_UP  && prevkey != GLUT_KEY_DOWN && selected == 13) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        colissionSelf();
        ::snakey+=5;
        collisionwall();
        prevkey = key;

    }
    else if (key == GLUT_KEY_DOWN && prevkey != GLUT_KEY_UP && selected == 13)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
        colissionSelf();
        ::snakey-=5;
        collisionwall();

        prevkey = key;
    }

    //esnake
    if (dir == GLUT_KEY_LEFT && selected == 13 /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        //colissionSelf();
        ::estartx-=5;
        //collisionwall();
        //prevkey = key;


    } else if (dir== GLUT_KEY_RIGHT && selected == 13 /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
        //colissionSelf();
        ::estartx+=5;
        //collisionwall();
        //prevkey = key;

    } else if (dir== GLUT_KEY_UP && selected == 13) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        //colissionSelf();
        ::estarty+=5;
        //collisionwall();
        //prevkey = key;

    }
    else if (dir == GLUT_KEY_DOWN && selected == 13)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
        //colissionSelf();
        ::estarty-=5;
        //collisionwall();
        //prevkey = key;
    }

    if (key == GLUT_KEY_UP && selected !=13){
        choice -=1;
    }
    else if (key == GLUT_KEY_DOWN&& selected !=13){
        choice +=1;
    }
    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if ( ((key == 'R' || key=='r') && hitwall == true) ||  ( (key == 'R' || key=='r') && choice == 2)/* Escape key ASCII*/) {
        reset();
        glutDisplayFunc(Display);
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }

    else if (int(key) == 13)
    {
        selected = 13;
	}

    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
    //normal food generated
    glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc( 1000/(FPS*speed), Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

    //REDING PREVIOUS Score
    ifstream input;
    input.open("Highscore.txt");
    input >> prevscore;
    input.close();

    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("MAAZ's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
