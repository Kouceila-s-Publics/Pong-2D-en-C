#include "raylib.h"
#include <math.h>
struct paddle
{
    float X,Y;
    float Speed;
    int but;
    char score[3];
};
struct Ball
{
    float X,Y;
    float SpeedX,SpeedY,Speed;
};
void IntialiserPong()
{
    InitWindow(1366,768,"jeu pong");
    SetWindowState(FLAG_FULLSCREEN_MODE);
    InitAudioDevice();
    SetTargetFPS(60);
}
void AfficherPong(float a,Texture2D b,Texture2D c,Texture2D d,float Xball,float Yball,float Xleftpaddle,float Yleftpaddle,float Xrightpaddle,float Yrightpaddle)
{
    BeginDrawing();
    //affichage de terrain:
    if(a==0.5)
    {
        DrawTexture(b, -20,-80,WHITE);
    }
    if(a==1)
    {
        DrawTexture(c, -20,-80,WHITE);
    }
    if(a==2)
    {
        DrawTexture(d, -20,-80,WHITE);
    }
    DrawLine(683,10,683,758,WHITE);
    DrawLine(0,10,1366,10,WHITE);
    DrawLine(0,758,1366,758,WHITE);
    //affichage de la balle :
    DrawRectangle(Xball-7.5,Yball-7.5,15,15,WHITE);
    // affichage du la raquette gauche :
    DrawRectangle(Xleftpaddle,Yleftpaddle,15,150,RED);
    DrawRectangle(Xleftpaddle+3,Yleftpaddle+3,9,144,WHITE);
    // affichage du la raquette droite :
    DrawRectangle(Xrightpaddle,Yrightpaddle,15,150,GREEN);
    DrawRectangle(Xrightpaddle+3,Yrightpaddle+3,9,144,WHITE);
    // affichage du controle
    DrawText("pause/controle 'Espace'",10,720,25,WHITE);
}
void DeplacerBall(float Xballspeed,float Yballspeed,float *Xball,float *Yball)
{
    *Xball += Xballspeed * GetFrameTime();
    *Yball += Yballspeed * GetFrameTime();
}
void RebondirBallBord(float *Yballspeed,float Yball)
{
    // rebondissement de la balle vers le haut :
    if(Yball<=0)
    {
        Yball = 1;
        *Yballspeed =-*Yballspeed;
    }
    //rebondissement de la ball vers le bas :
    if(Yball>=GetScreenHeight())
    {
        Yball = GetScreenHeight()-1;
        *Yballspeed = -*Yballspeed;
    }
}
void RebondirBallraquette(Sound ballbounc,float Xball,float Yball,float Yrightpaddle,float Yleftpaddle,float speedmoy,float *Xballspeed,float *Yballspeed,float *ballspeed,float b)
{   //speedmoy=yballspeed/85*2/3;
    speedmoy=sqrt(pow(*ballspeed,2))/85*2/3;
    //rebondissement du la raquette droite :
    if((Xball>= GetScreenWidth()-35) && (Xball<=GetScreenWidth()-10) && (Yball <= Yrightpaddle +160) && (Yball >=Yrightpaddle-10))
    {
        PlaySound(ballbounc);
        *Yballspeed=(Yball-(Yrightpaddle+75))*speedmoy;
        *Xballspeed=-(sqrt(pow(*ballspeed,2)-pow(*Yballspeed,2)));
        *ballspeed+=(424.264/15)*b;

    }
    //rebondissement du la raquette gauche :
    if((Xball<=35) && (Xball>=10) && (Yball <=(Yleftpaddle +160) )&& (Yball >= Yleftpaddle-10))
    {
        PlaySound(ballbounc);
        *Yballspeed=(Yball-(Yleftpaddle+75))*speedmoy;
        *Xballspeed=(sqrt(pow(*ballspeed,2)-pow(*Yballspeed,2)));
        *ballspeed+=(424.264/15)*b;
    }
}
void IncrementerCompteur(int *k,char s[])
{
    char score[]="01234567";
    *k=*k+1;
    s[0]=score[*k];
    s[1]='\0';
}
void TerminerPartie(Texture2D a,Texture2D b,Texture2D c,Texture2D d,Music music,Sound bouton,Sound ballbounc,Sound diffselect,Sound win,Sound gameover,Music goal)
{
    UnloadSound(bouton);
    UnloadSound(ballbounc);
    UnloadSound(diffselect);
    UnloadSound(win);
    UnloadSound(gameover);
    UnloadMusicStream(goal);
    UnloadMusicStream(music);
    UnloadTexture(a);
    UnloadTexture(b);
    UnloadTexture(c);
    UnloadTexture(d);
    EndDrawing();
    CloseAudioDevice();
    CloseWindow();
}
void MusicBoucle(Music music)
{
    if(GetMusicTimePlayed(music)/GetMusicTimeLength(music)>=1)
    {
        StopMusicStream(music);
        PlayMusicStream(music);
    }
}
void MenuPrincipale(Texture2D a)
{
        BeginDrawing();
        DrawTexture(a, -20,-80,WHITE);
        DrawRectangle(1050,600,10,150,WHITE);
        DrawRectangle(1050,600,300,10,WHITE);
        DrawRectangle(1350,750,-10,-150,WHITE);
        DrawRectangle(1350,750,-300,-10,WHITE);
        DrawText("Menu'R'",1110,650,50,WHITE);
        DrawText("ping pong",230,230,200,WHITE);
        DrawRectangle(10,600,300,10,WHITE);
        DrawRectangle(10,600,10,150,WHITE);
        DrawRectangle(10,740,300,10,WHITE);
        DrawRectangle(300,600,10,150,WHITE);
        DrawText("Quitter'Q'",40,650,50,WHITE);
}
void MenuDEChoix(Sound diffselect,Sound bouton,Texture2D a,int *c,float *b,int *p)
{
    //afficher et cntrole des options
    BeginDrawing();
    DrawTexture(a, -20,-80,WHITE);

    DrawRectangle(483,185,410,484,BLACK);

    DrawRectangle(1050,600,300,150,BLACK);
    DrawRectangle(1055,605,290,140,WHITE);
    DrawText("Jouer'J'",1105,650,50,BLACK);

    DrawRectangle(20,20,300,150,BLACK);
    DrawRectangle(25,25,290,140,WHITE);
    DrawText("Retour'R'",55,70,50,BLACK);

    if(*b!=0.5)
    {
        DrawRectangle(493,195,390,148,WHITE);
        DrawText("Debutant'D'",GetScreenWidth()/2-145,240,50,GREEN);
    }
    else
    {
        DrawRectangle(493,195,390,148,GREEN);
        DrawText("Debutant'D'",GetScreenWidth()/2-145,240,50,WHITE);
        DrawRectangle(1055,605,290,140,GREEN);
        DrawText("Jouer'J'",1105,650,50,WHITE);
    }
    if(*b!=1)
    {
        DrawRectangle(493,353,390,148,WHITE);
        DrawText("Intermediaire 'I'",GetScreenWidth()/2-175,400,45,YELLOW);
    }
    else
    {
        DrawRectangle(493,353,390,148,YELLOW);
        DrawText("Intermediaire 'I'",GetScreenWidth()/2-175,400,45,WHITE);
        DrawRectangle(1055,605,290,140,YELLOW);
        DrawText("Jouer'J'",1105,650,50,WHITE);
    }
    if(*b!=2)
    {
        DrawRectangle(493,511,390,148,WHITE);
        DrawText("Expert'E'",GetScreenWidth()/2-120,550,50,RED);
    }
    else
    {
        DrawRectangle(493,511,390,148,RED);
        DrawText("Expert'E'",GetScreenWidth()/2-120,550,50,WHITE);
        DrawRectangle(1055,605,290,140,RED);
        DrawText("Jouer'J'",1105,650,50,WHITE);
    }
    if(IsKeyDown(KEY_D))
    {
        PlaySound(diffselect);
        *c=1;
        *b=0.5;
    }
    if(IsKeyDown(KEY_I))
    {
        PlaySound(diffselect);
        *c=1;
        *b=1;

    }
    if(IsKeyDown(KEY_E))
    {
        PlaySound(diffselect);
        *c=1;
        *b=2;
    }
}
void PauseProcessus(bool d,Sound bouton)
{
    PlaySound(bouton);
    while(d)
    {
        BeginDrawing();
        DrawText("Continue'C'",610,180,30,WHITE);
        DrawText("Controle",620,240,30,RED);
        DrawLine(580,280,786,280,RED);
        DrawText("Rejouer'J'",610,330,30,BLACK);
        DrawText("Menu'R'",630,420,30,BLACK);
        DrawText("Quitter'Q'ou'esc'",555,510,30,BLACK);
        EndDrawing();
        if((IsKeyDown(KEY_C))||(IsKeyDown(KEY_A))||(IsKeyDown(KEY_R))||(IsKeyDown(KEY_J))||(IsKeyDown(KEY_ESCAPE)))
        {
            PlaySound(bouton);
            d=!d;
        }
    }

}
void Player1Controle(float *Ypaddle,float paddlespeed)
{//controle manuelle:

    if((IsKeyDown(KEY_UP))||IsKeyDown(KEY_KP_9))
    {
        *Ypaddle -= paddlespeed * GetFrameTime();
    }
    if((IsKeyDown(KEY_DOWN))||(IsKeyDown(KEY_KP_3)))
    {
        *Ypaddle += paddlespeed * GetFrameTime();
    }
}
void Player2Controle(float *Ypaddle,float paddlespeed)
{//controle manuelle:

    if(IsKeyDown(KEY_W))
    {
        *Ypaddle -= paddlespeed * GetFrameTime();
    }
    if(IsKeyDown(KEY_S))
    {
        *Ypaddle += paddlespeed * GetFrameTime();
    }
}
void AutoControle(float Xball,float Yball,float *Ypaddle,float paddlespeed)
{ //controle automatic:
    if(Xball<=GetScreenWidth()/2)
    {
        if(Yball<=*Ypaddle+74)
        {
            *Ypaddle -= paddlespeed * GetFrameTime();
        }
        if(Yball>=*Ypaddle+74)
        {

            *Ypaddle += paddlespeed * GetFrameTime();
        }
    }
}
void LimitesDeMouvement(float *Ypaddle)
{
    //limites de mouvement;
    if(*Ypaddle<=0)
    {
        *Ypaddle = 0;

    }
    if(*Ypaddle>=GetScreenHeight()-150)
    {
        *Ypaddle = GetScreenHeight()-150;
    }

}
int main()
{
    IntialiserPong();
    //declaratin des variable :
    int c=3,p=3;char score[]="0";float b,SpeedMoy;
    bool k,d,g,h=true;
    Texture2D background_a = LoadTexture("Ressources/sunnyday.png");
    Texture2D background_b = LoadTexture("Ressources/bluemoon.png");
    Texture2D background_c = LoadTexture("Ressources/foggy.png");
    Texture2D background_d = LoadTexture("Ressources/graveyard.png");
    Music music = LoadMusicStream("Ressources/Arcade Game Music.mp3");
    Music goal = LoadMusicStream("Ressources/goal.mp3");
    Sound diffselect = LoadSound("Ressources/difficultèselect.wav");
    Sound gameover = LoadSound("Ressources/gameover.wav");
    Sound bouton = LoadSound("Ressources/bouton.wav");
    Sound ballbounc =  LoadSound("Ressources/ballbounc.wav");
    Sound win = LoadSound("Ressources/win.wav");
    struct Ball ball = {};
    struct paddle leftpaddle = {};
    struct paddle rightpaddle = {};
    PlayMusicStream(music);
    //la boucle principale de jeu :
    while((!WindowShouldClose())&&(!IsKeyDown(KEY_A)))
    {
        //music de fond
        UpdateMusicStream(music);
        MusicBoucle(music);

        //l'affichage de le menu principale :
        if(c==3)
        {
            MenuPrincipale(background_a);
        }
        //le controle de le bouton 'H' :
        if(IsKeyDown(KEY_R))
        {
        PlaySound(bouton);
        c=4;
        b=0;
        p=3;
        }
        if((c==4)&&(b==0))
        {
        BeginDrawing();
        DrawTexture(background_c, -20,-80,WHITE);
        DrawRectangle(1050,600,10,150,GREEN);
        DrawRectangle(1050,600,300,10,GREEN);
        DrawRectangle(1350,750,-10,-150,GREEN);
        DrawRectangle(1350,750,-300,-10,GREEN);
        DrawText("   controle\n   up/9=up\ndown/3=down",1130,500,20,WHITE);
        DrawText("1 p'1'",1130,640,75,BLACK);
        DrawText("ping pong",230,230,200,BLACK);
        DrawRectangle(10,600,300,10,RED);
        DrawRectangle(10,600,10,150,RED);
        DrawRectangle(10,740,300,10,RED);
        DrawRectangle(300,600,10,150,RED);
        DrawText("   controle\n     Z=up\n    S=down",60,500,20,WHITE);
        DrawText("2 p'2'",60,640,75,BLACK);
        if((IsKeyDown(KEY_ONE))||(IsKeyDown(KEY_KP_1)))
        {
            PlaySound(bouton);
            p=0;
            c=2;
            b=0;
        }
        if((IsKeyDown(KEY_TWO))||(IsKeyDown(KEY_KP_2)))
        {
            PlaySound(bouton);
            p=1;
            c=0;
            b=1;
            g=1;
        }
        }
        //l'affichage de le menu de choix :
        if((c==2)||(c==1))
        {
            if(p==0)
            MenuDEChoix(diffselect,bouton,background_a,&c,&b,&p);
        }
        //statut primaire et restart :
        if(((IsKeyDown(KEY_KP_2))||(IsKeyDown(KEY_TWO))&&(g==1))||((IsKeyDown(KEY_J))&&(c<=1)&&(b>0)))
        {
            PlaySound(bouton);
            g=0;
            //la ball :
            ball.X = GetScreenWidth()/2;
            ball.Y = GetScreenHeight()/2;

            ball.SpeedX = 300;
            ball.SpeedY = 0;
            ball.Speed = 424.264;

            //la raquette droite :
            rightpaddle.but = 0;
            rightpaddle.X = GetScreenWidth() -25;
            rightpaddle.Y = GetScreenHeight()/2-75;
            rightpaddle.Speed = 250+250/b;
            rightpaddle.score[0]=score[0];
            rightpaddle.score[1]='\0';

            //la raquette gauche :
            leftpaddle.X = 10;
            leftpaddle.Y = GetScreenHeight()/2-75;
            leftpaddle.but = 0;
            if(p==0)leftpaddle.Speed = 250+250*b;
            else leftpaddle.Speed = 250+250/b;
            leftpaddle.score[0]=score[0];
            leftpaddle.score[1]='\0';

            c-=2;;
            h=true;
        }
        // la c
        if(c<1)
        {
            // le processus de pause :
            if(IsKeyDown(KEY_SPACE))
            {
                PauseProcessus(d,bouton);
            }

            //*deplacement de la ball :
            DeplacerBall(ball.SpeedX,ball.SpeedY,&ball.X,&ball.Y);

            //*rebondir la ball avec le bord haut et bas;
            RebondirBallBord(&ball.SpeedY,ball.Y);

            //*rebondir la ball avec la raquette gouche et droite;
            RebondirBallraquette(ballbounc,ball.X,ball.Y,rightpaddle.Y,leftpaddle.Y,SpeedMoy,&ball.SpeedX,&ball.SpeedY,&ball.Speed,b);

            /*controle de la raquette de joueur :*/
            Player1Controle(&rightpaddle.Y,rightpaddle.Speed);
            //les limites de mouvement de la raquette de joueur 1 :
            LimitesDeMouvement(&rightpaddle.Y);

            if(p==0)
            {
                /*controle de la raquette d'ordinateur :*/
                AutoControle(ball.X,ball.Y,&leftpaddle.Y,leftpaddle.Speed);
            }
            else
            {
                //controle de le joueur 2 :
                Player2Controle(&leftpaddle.Y,leftpaddle.Speed);
            }

            //les limites de mouvement de la raquette d'ordinateur:
            LimitesDeMouvement(&leftpaddle.Y);

            //affichage du but :
            if(ball.X > GetScreenWidth())
            {
                if(leftpaddle.but<6)
                {
                    PlayMusicStream(goal);
                    do
                    {   UpdateMusicStream(music);
                        UpdateMusicStream(goal);
                        EndDrawing();
                        BeginDrawing();
                        if(b==0.5)
                        {
                            DrawTexture(background_b, -20,-80,WHITE);
                        }
                        if(b==1)
                        {
                            DrawTexture(background_c, -20,-80,WHITE);
                        }
                        if(b==2)
                        {
                            DrawTexture(background_d, -20,-80,WHITE);
                        }
                        DrawText("but!!!!",GetScreenWidth()/2 -100,GetScreenHeight()/2-50,50,RED);

                        ball.SpeedX =300;
                        ball.SpeedY =0;
                        ball.Speed = 424.264;
                        rightpaddle.Y = GetScreenHeight()/2-75;
                        leftpaddle.Y = GetScreenHeight()/2-75;
                        ball.X += ball.SpeedX * GetFrameTime();
                    }while(ball.X <= GetScreenWidth()+570);
                    StopMusicStream(goal);
                }
                ball.Y=GetScreenHeight()/2;
                ball.X=GetScreenWidth()/2;
                IncrementerCompteur(&leftpaddle.but,leftpaddle.score);
                k=0;

                EndDrawing();
            }
            if(ball.X<0)
            {
                if(rightpaddle.but<6)
                {
                    PlayMusicStream(goal);
                    do
                    {   UpdateMusicStream(music);
                        UpdateMusicStream(goal);
                        EndDrawing();
                        BeginDrawing();
                        if(b==0.5)
                        {
                            DrawTexture(background_b, -20,-80,WHITE);
                        }
                        if(b==1)
                        {
                            DrawTexture(background_c, -20,-80,WHITE);
                        }
                        if(b==2)
                        {
                            DrawTexture(background_d, -20,-80,WHITE);
                        }
                        DrawText("but!!!!",GetScreenWidth()/2 -100,GetScreenHeight()/2-50,50,GREEN);
                        ball.SpeedX =-300;
                        ball.SpeedY =0;
                        ball.Speed = 424.264;
                        rightpaddle.X = GetScreenWidth() -20;
                        rightpaddle.Y = GetScreenHeight()/2-75;
                        leftpaddle.X = 10;
                        leftpaddle.Y = GetScreenHeight()/2-75;
                        ball.X += ball.SpeedX * GetFrameTime();
                    }while(ball.X >= -570);
                    StopMusicStream(goal);
                }
                ball.Y=GetScreenHeight()/2;
                ball.X=GetScreenWidth()/2;
                IncrementerCompteur(&rightpaddle.but,rightpaddle.score);
                k=1;
                EndDrawing();
            }
            //afficher le victoire ou la defaite
            if((rightpaddle.but >= 7)||(leftpaddle.but >= 7))
            {
                BeginDrawing();
                if(h==true)
                {
                    if(k==1)PlaySound(win);
                    else PlaySound(gameover);
                    h=false;
                }
                if(b==0.5)
                {
                    DrawTexture(background_b, -20,-80,WHITE);
                }
                if(b==1)
                {
                    DrawTexture(background_c, -20,-80,WHITE);
                }
                if(b==2)
                {
                    DrawTexture(background_d, -20,-80,WHITE);
                }
                if(k==1)DrawText("Tu Gagnes",GetScreenWidth()/2 -280,GetScreenHeight()/2-110,100,GREEN);
                else
                {
                    if(p==0)DrawText("Tu as perdu",GetScreenWidth()/2 -310,GetScreenHeight()/2-110,100,RED);
                    else DrawText("Tu Gagnes",GetScreenWidth()/2 -280,GetScreenHeight()/2-110,100,RED);
                }
                DrawText("click sur 'J' pour rejouer",GetScreenWidth()/2 -330,GetScreenHeight()-250,50,BLACK);
                ball.X = GetScreenWidth()/2;
                ball.Y = GetScreenHeight()/2;
                leftpaddle.X = 10;
                leftpaddle.Y = 0;
                rightpaddle.X = GetScreenWidth() -20;
                rightpaddle.Y = 0;
                EndDrawing();
            }
            //l'affichage principale de jeu :
            if((rightpaddle.but<7)&&(leftpaddle.but<7)&&(c<1))
            {
                AfficherPong(b,background_b,background_c,background_d,ball.X,ball.Y,leftpaddle.X,leftpaddle.Y,rightpaddle.X,rightpaddle.Y);
                DrawText(leftpaddle.score,325,10,100,RED);
                DrawText(rightpaddle.score,1008,10,100,GREEN);

            }

        }
        EndDrawing();

    }
    TerminerPartie(background_a,background_b,background_c,background_d,music,bouton,ballbounc,diffselect,win,gameover,goal);

    return 0;
}
