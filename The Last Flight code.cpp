#include<iostream>
#include<fstream>
#include "raylib.h"
using namespace std;

//PROJECT GROUP MEMBERS
//MUHAMMAD HASSAN MOAZZAN
//RYYAN CHOUDHARY
//SHAYAN Qureshi


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "The Last Flight");

    // TODO: Initialize all required variables and load all required data here!
    InitAudioDevice();
    Texture2D player = LoadTexture("Assets\\SHIP1.png");
    Texture2D one = LoadTexture("Assets\\1.png");
    Texture2D two = LoadTexture("Assets\\2.png");
    Texture2D three = LoadTexture("Assets\\3.png");
    Texture2D four = LoadTexture("Assets\\4.png");
    Texture2D Text1 = LoadTexture("Assets\\Hero.png");
    Texture2D hero = LoadTexture("Assets\\Heroo.png");
    Texture2D enem1 = LoadTexture("Assets\\enem1.png");
    Texture2D bg1 = LoadTexture("Assets\\bg2.png");
    Texture2D ends = LoadTexture("Assets\\ends.png");
    Texture2D enem2 = LoadTexture("Assets\\enem2.png");
    Texture2D boses = LoadTexture("Assets\\boss.png");
    Texture2D laser = LoadTexture("Assets\\lazer.png");
    Texture2D laserwarn = LoadTexture("Assets\\bigex.png");
    Texture2D boulet = LoadTexture("Assets\\boulets.png");
    Texture2D bossbullet = LoadTexture("Assets\\bossb.png");
    Texture2D win_texture = LoadTexture("Assets\\win.png");
    Texture2D bois = LoadTexture("Assets\\Creators.png");

    //SOUNDS
    Sound heroic = LoadSound("Assets\\Titan GIGANTO.mp3");
    Sound op = LoadSound("Assets\\Opening.mp3");
    Sound boss = LoadSound("Assets\\boss.mp3");
    Sound damage = LoadSound("Assets\\damage.mp3");
    Sound game_over = LoadSound("Assets\\Gameover.mp3");
    Sound hehe = LoadSound("Assets\\Hehe.mp3");
    Sound main_theme = LoadSound("Assets\\main theme.mp3");
    Sound shoot = LoadSound("Assets\\shoot.mp3");
    Sound rayshoot = LoadSound("Assets\\rayshoot.mp3");
    Sound win = LoadSound("Assets\\WIN.mp3");
    Sound credits = LoadSound("Assets\\credits.mp3");

    SetTargetFPS(30);               // Set desired framerate (frames-per-second)

    //Initialize and open main game window
    // 
    //Score
    int highestscore = 0;
    int scoretimer = 0;
    //Player
    Rectangle character = { 400,600,40,32 };
    float const pspeed = 20;
    const float x1 = 0;
    const float x2 = 750;
    int screen = -2;
    int framecount = 0;
    int bulletcount = 0;
    int spentbulletcooldown = -400;
    int hp = 20;
    int score = 0;
    char temp = 0;
    int powa = 5;
    int powaFrameCount = 0;
    bool player_alive = true;
    int nextlevel = 2;
    int loadcounter = 220;
    int loadcounter2 = 220;
    int loadcounter3 = 220;
    int loadcounter4 = 220;
    int wait_for_credits = 600;
    //SOUND PLAYBACK CALLS
    int screen1sound = 0;
    int screen2sound = 0;
    int screen3sound = 0;
    int screen4sound = 0;
    int screen5sound = 0;
    int screen6sound = 0;
    int screen7sound = 0;
    int screen8sound = 0;
    //BULLETS FOR THE PLAYER
    Rectangle boret[3] = { 0,0,10,10,0,0,10,10,0,0,10,10 };
    int borettimer[3] = { 2,4,6 };
    bool active[3] = { false,false,false };
    int const bspeed = 25;

    //Enemies
    //enemy array
    Rectangle enemy[9] = { 150,300,40,20,400,300,40,20,650,300,40,20, //FRONT
                           200,200,40,20,400,200,40,20,600,200,40,20, //MID
                           150,100,40,20,400,100,40,20,650,100,40,20 }; //BACK

    int alive[9] = { 1,1,1,
                     2,2,2,
                     3,3,3 };

    int randstart = 90, randend = 300;
    int random[9] = { GetRandomValue(randstart,randend),GetRandomValue(randstart,randend),GetRandomValue(randstart,randend),
                      GetRandomValue(randstart,randend),GetRandomValue(randstart,randend),GetRandomValue(randstart,randend),
                      GetRandomValue(randstart,randend),GetRandomValue(randstart,randend),GetRandomValue(randstart,randend) };

    int const totalenem = 10;
    int const numenemies = 9;
    int mov[9] = { 2,2,2,
                   2,2,2,
                   2,2,2 };

    int jump = 40;
    int deadcount = 0;

    int enemtype = 1;
    //Enemy bullets
    Rectangle bull[9] = { -1,-1,10,10,-1,-1,10,10,-1,-1,10,10,
                         -1,-1,10,10,-1,-1,10,10,-1,-1,10,10,
                         -1,-1,10,10 ,-1,-1,10,10 ,-1,-1,10,10 };
    bool shot[9] = { false,false,false,
                    false,false,false,
                    false,false,false };
    int ebspeed = 10;

    //BOSE
    Rectangle Bose{ 300,300,82,44 };
    int alivebose = 0;
    int bossspd = 20;
    int bosjmp = 30;
    int bossrndst = 30, bossrndend = 60;
    int bossrnd = GetRandomValue(bossrndst, bossrndend);

    //BULLETS
    Rectangle bossbull[3] = { 100, 100, 15, 15, -1, -1, 15, 15, -1, -1, 15, 15 };
    bool boss_shot = false;
    int bossbspeed = 20;

    //GIGA RAY
    Rectangle Rays = { -500,-3000,150,700 };
    int raystart = 240, rayend = 400; //CHANGE
    int randray = GetRandomValue(raystart, rayend);

    int rayxstart = 200, rayxend = 600;
    int raypos = GetRandomValue(rayxstart, rayxend);

    bool shotray = false;
    int rayspeed = 80;

    //Opening cutscene
    long frame_count = 0;
    int texture_at_display = 0, soundtimer1 = 0, soundtimer2 = 0;
    bool ignoreInput = false;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (screen)
        {
        case -2:
        {
            //START SCREEN PRESS SPACE AND CONTROLS
            frame_count++;
            if (frame_count > 4)
            {
                frame_count = 0;
                texture_at_display = (texture_at_display + 1) % 4;
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                screen = -1;
                StopSound(op);
            }

        }break;
        case -1:
        {
            //CUTSCENE AND STORY

            if (IsKeyPressed(KEY_SPACE))
            {
                screen = 0;
            }

        }break;

        case 0:
        {
            //IMAGE

            if (IsKeyPressed(KEY_SPACE))
            {
                screen = 1;
                StopSound(heroic);

            }

        }break;

        case 1:
        {
            //MAIN GAME LOOP
            //Main theme
            if (screen1sound == 0)
            {
                PlaySound(main_theme);
                screen1sound++;
            }

            //Simple left right movement for player only(To make it harder to dodge and shoot)
            if (IsKeyDown(KEY_RIGHT) && character.x < x2)
            {
                character.x += pspeed;
            }

            if (IsKeyDown(KEY_LEFT) && character.x > x1)
            {
                character.x -= pspeed;
            }

            //Enemy movement
            for (int i = 0; i < numenemies; i++)
            {
                enemy[i].x += mov[i];
                if (enemy[i].x >= 750)
                {
                    mov[i] = -mov[i];
                    enemy[i].y += jump;
                }
                if (enemy[i].x <= 0)
                {
                    mov[i] = -mov[i];
                    enemy[i].y += jump;
                }

                random[i]--;
            }

            //Boss movement

            Bose.x += bossspd;
            bossrnd--;
            randray--;
            if ((Bose.x >= 700 || Bose.x <= 0) && alivebose > 0)
            {
                bossspd = -bossspd;
                if (Bose.y >= 400 || Bose.y <= 100)
                {
                    bosjmp = -bosjmp;
                }
                Bose.y += bosjmp;
            }

            //Player Shooting
            if (IsKeyDown(KEY_SPACE))
            {

                if (active[0] == false && bulletcount >= borettimer[0])
                {
                    PlaySound(shoot);
                    active[0] = true;
                    boret[0].x = character.x;
                    boret[0].y = character.y;
                    bulletcount = 0;

                }
                if (active[1] == false && bulletcount >= borettimer[1])
                {
                    PlaySound(shoot);
                    active[1] = true;
                    boret[1].x = character.x;
                    boret[1].y = character.y;
                    bulletcount = 0;

                }
                if (active[2] == false && bulletcount >= borettimer[2])
                {
                    PlaySound(shoot);
                    active[2] = true;
                    boret[2].x = character.x;
                    boret[2].y = character.y;
                    bulletcount = 0;

                }

            }

            //Enemy Shooting
            for (int i = 0; i < numenemies; i++)
            {
                if (random[i] <= 0 && alive[i] >= 0)
                {
                    shot[i] = true;
                    bull[i].x = enemy[i].x;
                    bull[i].y = enemy[i].y;
                    random[i] = (GetRandomValue(randstart, randend));
                }

                if (shot[i] == true)
                {
                    bull[i].y += ebspeed;
                }

                if (bull[i].y >= 700)
                {
                    shot[i] = false;
                    bull[i].y = -10;
                }
            }

            //Boss shooting
            if (bossrnd <= 0 && alivebose > 0)
            {
                for (int bu = 0; bu < 3; bu++)
                {
                    boss_shot = true;
                    bossbull[bu].x = Bose.x;
                    bossbull[bu].y = Bose.y;
                    bossrnd = GetRandomValue(bossrndst, bossrndend);
                }
            }

            if (boss_shot)
            {
                bossbull[0].y += bossbspeed;
                bossbull[0].x += -10;

                bossbull[1].y += bossbspeed;

                bossbull[2].y += bossbspeed;
                bossbull[2].x += 10;
            }

            //BOSS GIGA RAY
            if (randray <= 0 && alivebose > 0)
            {
                shotray = true;
                PlaySound(rayshoot);
                Rays.y = -3000;
                Rays.x = GetRandomValue(rayxstart, rayxend);
                randray = GetRandomValue(raystart, rayend);

            }
            if (shotray)
            {
                Rays.y += rayspeed;
            }

            //Making player bullets go up
            for (int i = 0; i < 3; i++)
            {
                boret[i].y -= bspeed;
            }

            //Reloading player bullets
            for (int i = 0; i < 3; i++)
            {
                if (boret[i].y < spentbulletcooldown)
                {
                    active[i] = false;
                }
            }

            //Enemy hit detection
            for (int i = 0; i < numenemies; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (CheckCollisionRecs(enemy[i], boret[j]))
                    {
                        alive[i]--;
                        score += 100;
                        boret[j].x = -20;
                        boret[j].y = -20;
                    }
                }
            }
            //Bose hit detection
            for (int j = 0; j < 3; j++)
            {
                if (CheckCollisionRecs(Bose, boret[j]))
                {
                    alivebose--;
                    score += 100;
                    boret[j].x = -20;
                    boret[j].y = -20;
                }
            }

            //Removing hitbox
            for (int i = 0; i < numenemies; i++)
            {
                if (alive[i] <= 0)
                {
                    enemy[i].x = -500;
                    enemy[i].y = -500;
                }
            }


            //Player hit detection
            for (int i = 0; i < numenemies; i++)
            {
                if (CheckCollisionRecs(character, bull[i]) || CheckCollisionRecs(character, enemy[i]))
                {
                    PlaySound(damage);
                    if (powa >= 5)
                    {
                        powa = 0;
                        hp--;
                        score -= 20;
                        if (hp <= 0)
                        {
                            //dead scenario, will show explosion and blast music will play only, and level will begin from beginnig
                            player_alive = false;
                            cout << "DEAD!";
                            character.x = -100;
                            character.y = -100;
                            bull[i].y = 900;
                        }
                    }
                }
            }

            //Boss
            for (int j = 0; j < 3; j++)
            {
                if (CheckCollisionRecs(character, bossbull[j]))
                {
                    PlaySound(damage);
                    if (powa >= 5)
                    {
                        powa = 0;
                        hp--;
                        score -= 20;
                        if (hp <= 0)
                        {
                            //dead scenario, will show explosion and blast music will play only, and level will begin from beginnig
                            player_alive = false;
                            character.x = -100;
                            character.y = -100;
                            bossbull[j].y = 900;
                        }
                    }
                }
            }

            //Enemy and player collision exploder >:D
            for (int gone = 0; gone < numenemies; gone++)
            {

                if (CheckCollisionRecs(character, enemy[gone]))
                {
                    PlaySound(damage);
                    alive[gone] = 0;
                }
            }

            //Final death laser moment
            if (CheckCollisionRecs(character, Rays))
            {
                hp = 0;
            }

            //Incrementing player bullet cooldown timer
            bulletcount++;
            powa++;

            //gamewin scenario
            //Level transition check
            deadcount = 0;
            if (alivebose <= 0)
            {
                deadcount++;
            }
            for (int k = 0; k < numenemies; k++)
            {
                if (alive[k] <= 0)
                {
                    deadcount++;
                }
            }

            if (deadcount == totalenem)
            {
                screen = nextlevel;
            }

            //Losegame
            if (hp <= 0)
            {
                screen = 7;
            }

        } break;


        case 2:
        {
            //LEVEL 2 UPDATING VALUES

            if (screen2sound == 0)
            {
                StopSound(main_theme);
                PlaySound(hehe);
                screen2sound++;
            }

            loadcounter--;
            if (loadcounter <= 0)
            {
                screen1sound = 0;
                nextlevel++;
                //Resetting enemies for next level
                //Make them alive
                alive[0] = 2;
                alive[1] = 2;
                alive[2] = 2;
                alive[3] = 3;
                alive[4] = 3;
                alive[5] = 3;
                alive[6] = 4;
                alive[7] = 4;
                alive[8] = 9;
                //Make their positions
                enemy[0].x = 200;
                enemy[0].y = 100;

                enemy[1].x = 400;
                enemy[1].y = 100;

                enemy[2].x = 600;
                enemy[2].y = 100;

                enemy[3].x = 200;
                enemy[3].y = 150;

                enemy[4].x = 400;
                enemy[4].y = 150;

                enemy[5].x = 600;
                enemy[5].y = 150;

                enemy[6].x = 300;
                enemy[6].y = 200;

                enemy[7].x = 500;
                enemy[7].y = 200;

                enemy[8].x = 400;
                enemy[8].y = 300;

                //Resetting movement
                for (int mover = 0; mover < numenemies; mover++)
                {
                    mov[mover] = 4;
                }

                //Resetting player for next level
                character.x = 400;
                character.y = 600;
                screen = 1;
            }


        }break;

        case 3:
        {
            //LEVEL 3 UPDATING VALUES
            if (screen3sound == 0)
            {
                StopSound(main_theme);
                screen3sound++;
            }

            loadcounter2--;
            if (loadcounter2 <= 0)
            {

                screen1sound = 0;
                nextlevel++;
                //Increase how much enemy moves in y for jumpscare
                jump = 80;

                //Enemy dillon ka shooter mera scooter
                ebspeed = 22;

                randstart = 30;

                randend = 60;
                //Resetting enemies for next level
                //Make them alive
                alive[0] = 3;
                alive[1] = 3;
                alive[2] = 3;
                alive[3] = 3;
                alive[4] = 3;
                alive[5] = 3;
                alive[6] = 3;
                alive[7] = 3;
                alive[8] = 6;

                //Make their positions
                enemy[0].x = 100;
                enemy[0].y = 100;

                enemy[1].x = 150;
                enemy[1].y = 200;

                enemy[2].x = 225;
                enemy[2].y = 100;

                enemy[3].x = 300;
                enemy[3].y = 200;

                enemy[4].x = 375;
                enemy[4].y = 100;

                enemy[5].x = 450;
                enemy[5].y = 200;

                enemy[6].x = 525;
                enemy[6].y = 100;

                enemy[7].x = 600;
                enemy[7].y = 200;

                enemy[8].x = 300;
                enemy[8].y = 300;

                for (int mover = 0; mover < numenemies; mover++)
                {
                    mov[mover] = 1;
                }

                //Resetting player for next level
                character.x = 400;
                character.y = 600;

                enemtype = 2;

                screen = 1;
            }
        }break;

        case 4:
        {
            //LEVEL 4 UPDATING VALUES
            if (screen4sound == 0)
            {
                StopSound(main_theme);
                screen4sound++;
            }

            loadcounter3--;
            if (loadcounter3 <= 0)
            {

                screen1sound = 0;
                nextlevel++;
                //Increase how much enemy moves in y for jumpscare
                jump = 10;

                //Enemy dillon ka shooter mera scooter
                ebspeed = 45;

                randstart = 45;

                randend = 60;
                //Resetting enemies for next level
                //Make them alive
                alive[0] = 2;
                alive[1] = 2;
                alive[2] = 2;
                alive[3] = 2;
                alive[4] = 2;
                alive[5] = 2;
                alive[6] = 2;
                alive[7] = 2;
                alive[8] = 3;

                //Make their positions
                enemy[0].x = 100;
                enemy[0].y = 100;

                enemy[1].x = 150;
                enemy[1].y = 200;

                enemy[2].x = 225;
                enemy[2].y = 100;

                enemy[3].x = 300;
                enemy[3].y = 200;

                enemy[4].x = 375;
                enemy[4].y = 100;

                enemy[5].x = 450;
                enemy[5].y = 200;

                enemy[6].x = 525;
                enemy[6].y = 100;

                enemy[7].x = 600;
                enemy[7].y = 200;

                enemy[8].x = 300;
                enemy[8].y = 300;

                for (int mover = 0; mover < numenemies; mover++)
                {
                    mov[mover] = 2;
                }

                //Resetting player for next level
                character.x = 400;
                character.y = 600;

                enemtype = 2;

                screen = 1;
            }
        }break;

        case 5:
        {
            //BOSS UPDATING VALUES
            if (screen5sound == 0)
            {
                StopSound(main_theme);
                PlaySound(boss);
                screen5sound++;
            }

            loadcounter4--;
            if (loadcounter4 <= 0)
            {
                nextlevel++;
                alivebose = 40;
                Bose.x = 300;
                Bose.y = 300;

                //Resetting player for next level
                character.x = 400;
                character.y = 600;

                screen = 1;
            }
        }break;

        case 6:
        {
            //Highscore AND GAME WIN SCREEN
            fstream highs("Assets\\HIGH_SCORE.txt", std::ios::out | std::ios::in);
            if (!highs.is_open())
            {
                cout << "Error opening the file!" << endl;
                cout << "PLEASE CREATE HIGH_SCORE FILE IN GAME ASSETS!";
                return 0;
            }
            if (scoretimer == 0)
            {
                highs >> highestscore;
                if (score > highestscore)
                {
                    highs.clear();
                    highs.seekg(0, std::ios::beg);
                    cout << "High score updated!";
                    highs << score;
                    highs.close();
                }

                scoretimer++;
            }

            if (screen6sound == 0)
            {
                StopSound(boss);
                PlaySound(win);
                screen6sound++;
            }
            if (wait_for_credits <= 0)
            {
                screen = 8;
                StopSound(win);
            }
            wait_for_credits--;
        }break;

        case 7:
        {
            //Highscore AND GAME LOSS SCREEN
            fstream highs("Assets\\HIGH_SCORE.txt", std::ios::out | std::ios::in);
            if (!highs.is_open())
            {
                cout << "Error opening the file!" << endl;
                cout << "PLEASE CREATE HIGH_SCORE FILE IN GAME ASSETS!";
                return 0;
            }
            if (scoretimer == 0)
            {
                highs >> highestscore;
                if (score > highestscore)
                {
                    highs.clear();
                    highs.seekg(0, std::ios::beg);
                    cout << "High score updated!";
                    highs << score;
                    highs.close();
                }

                scoretimer++;
            }

            if (screen7sound == 0)
            {
                StopSound(main_theme);
                StopSound(boss);
                PlaySound(game_over);
                screen7sound++;
            }
        }break;

        case 8:
        {
            //CREDITS :)
            if (screen8sound == 0)
            {
                PlaySound(credits);
                screen8sound++;
            }
        }break;

        default: break;
        }
        //----------------------------------------------------------------------------------





        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (screen)
        {
        case -2:
        {
            ClearBackground(BLACK);
            if (soundtimer1 == 0)
            {
                PlaySound(op);
                soundtimer1++;
            }
            switch (texture_at_display)
            {
            case 0:
                DrawTexture(one, 0, 0, WHITE);
                break;
            case 1:
                DrawTexture(two, 0, 0, WHITE);
                break;
            case 2:
                DrawTexture(three, 0, 0, WHITE);
                break;
            case 3:
                DrawTexture(four, 0, 0, WHITE);
                break;
            default:break;
            }
            DrawText("Controls: < and > arrow keys to move and spacebar to fire!!", 100, 600, 20, WHITE);
        }break;
        case -1:
        {
            ClearBackground(BLACK);
            if (soundtimer2 == 0)
            {
                PlaySound(heroic);
                soundtimer2++;
            }
            DrawTexture(Text1, 0, 0, WHITE);
        }break;

        case 0:
        {
            DrawTexture(hero, 0, 0, WHITE);
        }break;

        case 1:
        {

            DrawTexture(bg1, 0, 0, WHITE);
            //Centering texture as it is misalligned with the HITBOX(Making player image and the hitbox)
            if (powa <= 5)
            {
                DrawTexture(player, character.x - (player.width - character.width) / 2, character.y - (player.width - character.width) / 2 + 8, RED);
            }
            else
            {
                DrawTexture(player, character.x - (player.width - character.width) / 2, character.y - (player.width - character.width) / 2 + 8, ORANGE);
            }


            DrawRectangleRec(character, BLANK);


            //HUD
            DrawText(TextFormat("Health = %02i", hp), 650, 50, 25, ORANGE);
            DrawText(TextFormat("Score = %05i", score), 50, 50, 25, ORANGE);


            //Making Player bullet
            for (int i = 0; i < 3; i++)
            {
                DrawRectangleRec(boret[i], RED);
                DrawTexture(boulet, boret[i].x, boret[i].y, GREEN);
            }



            //Making enemies and their bullets
            for (int i = 0; i < numenemies; i++)
            {
                if (alive[i] > 0)
                {
                    DrawRectangleRec(enemy[i], BLANK);
                    if (enemtype == 1)
                    {
                        DrawTexture(enem1, enemy[i].x - (enem1.width - enemy[i].width) / 2, enemy[i].y - (enem1.width - enemy[i].width) / 2, WHITE);
                    }
                    else
                    {
                        DrawTexture(enem2, enemy[i].x - (enem2.width - enemy[i].width) / 2, enemy[i].y - (enem2.width - enemy[i].width) / 2, WHITE);
                    }

                    if (shot[i])
                    {
                        DrawRectangleRec(bull[i], GREEN);
                        DrawTexture(boulet, bull[i].x, bull[i].y, PINK);
                    }
                }

            }

            //Making Bose and bullets
            if (alivebose > 0)
            {

                //DRAWING MEGA GIGA DEATH
                DrawRectangleRec(Rays, BLUE);
                if (Rays.y <= -100)
                {
                    DrawTexture(laserwarn, Rays.x, 350, WHITE);
                }
                DrawTexture(laser, Rays.x - (laser.width - Rays.width) / 2, Rays.y - (laser.width - Rays.width) / 2, WHITE);

                DrawText(TextFormat("CONQUEROR = %02i", alivebose), 350, 100, 15, RED);
                //BULLETS
                for (int bu = 0; bu < 3; bu++)
                {
                    DrawRectangleRec(bossbull[bu], BLANK);
                    DrawTexture(bossbullet, bossbull[bu].x, bossbull[bu].y, PINK);
                }

                DrawRectangleRec(Bose, BLANK);
                DrawTexture(boses, Bose.x - (boses.width - Bose.width) / 2, Bose.y - (boses.width - Bose.width) / 2, WHITE);
            }
        }break;


        case 2:
        {
            ////////////////////

            DrawText("Loading.....", 350, 350, 25, WHITE);
            DrawText("See you soon >:D (signed conqueror)", 350, 400, 20, PURPLE);
            DrawText("Pro Tip: Shoot the leader", 350, 500, 20, GREEN);

        }break;
        case 3:
        {
            DrawText("Loading.....", 350, 350, 25, WHITE);
            DrawText("Pro Tip: Wait for them to fire", 350, 500, 20, GREEN);
        }break;
        case 4:
        {
            DrawText("Loading.....", 350, 350, 25, WHITE);
            DrawText("Pro Tip: Try to dodge.", 350, 500, 20, GREEN);
        }break;
        case 5:
        {
            DrawText("You won't survive.....", 350, 350, 25, RED);
            DrawText("Pro Tip: Avoid the warning!", 350, 500, 20, GREEN);
        }break;

        case 6:
        {

            DrawTexture(win_texture, 0, 0, WHITE);
            DrawText("In the middle of the night, when the people \nsaw brightness in the sky from a far off blast, \nthey realized the hero had done it !!! \nAlthough the space conquerer disappeared, so did the hero. \nUnfortunately nobody ever saw or heard from the hero ever again.", 100, 550, 20, WHITE);
            DrawText(TextFormat("Your score = %07i", score), 500, 50, 18, WHITE);
            DrawText(TextFormat("Previous high score = %07i", highestscore), 500, 100, 18, WHITE);
        }break;

        case 7:
        {
            DrawTexture(ends, -250, 0, WHITE);
            DrawText(TextFormat("Your score = %07i", score), 400, 350, 18, WHITE);
            DrawText(TextFormat("Previous high score = %07i", highestscore), 400, 400, 18, WHITE);
        }break;

        case 8:
        {
            DrawTexture(bois, 0, 0, WHITE);
            DrawText("Made with love by Hassaan, Ryyan and Shayyan", 50, 500, 30, BLUE);
            DrawText("Music by : Cody O'Quinn, Epic Royalty Free and Free Music", 65, 600, 19, GREEN);
        }break;

        default: break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(one);
    UnloadTexture(two);
    UnloadTexture(three);
    UnloadTexture(four);
    UnloadTexture(player);
    UnloadTexture(Text1);
    UnloadTexture(hero);
    UnloadTexture(enem1);
    UnloadTexture(bg1);
    UnloadTexture(ends);
    UnloadTexture(enem2);
    UnloadTexture(boses);
    UnloadTexture(laser);
    UnloadTexture(laserwarn);
    UnloadTexture(boulet);
    UnloadTexture(bossbullet);
    UnloadTexture(win_texture);
    UnloadTexture(bois);

    UnloadSound(op);
    UnloadSound(heroic);
    UnloadSound(hehe);
    UnloadSound(shoot);
    UnloadSound(damage);
    UnloadSound(game_over);
    UnloadSound(win);
    UnloadSound(rayshoot);
    UnloadSound(credits);
    UnloadSound(boss);
    UnloadSound(main_theme);
    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

    return 0;
}