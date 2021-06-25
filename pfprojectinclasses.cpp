double startx=350,starty=400;
int level= 1;
int score = 1;
int prevscore;
int featen =0;

class snake{
    int bodycolor =0;
    int snakex=0,snakey=0;
    int size =2;
    int tailx[650] = {325,320,};
    int taily[650] = {405,405,};
    int prevx= startx+snakex;
    int prevy= starty+snakey;
    int prev2x=tailx[0], prev2y=taily[0];
public:

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

};

class food(){
    //normal food vars
    int foodi=0;
    int food[5][2] = { };
    int ftime=0;
    int flim= 30;

public:
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
        !(y > uDowny && y < uDowny+45) ){
            x = GetRandInRange(10,640);
            y=GetRandInRange(10,580);
        }
        fx =x;
        fy = y;

    }
};

class superfood{
public:
    int sfoodx = GetRandInRange(20,630);
    int sfoody = GetRandInRange(20,570);
    int sftime = 0;
    int slim = 180;
    int dsfoodtime = 0;
    bool dsfood = false;

};

class hurdels{
    int uUpx=-50, uUpy=-50;
    int uDownx = -50, uDowny = -50;
    int usidex = -50, usidey = -50, orientation=0;
    int hurdelcounter=0;
    int hlim = 150;
public:
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

};
