
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <bitset>
#include <string.h>

int main(void){

    //variables and initlaisation

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "mole buster");
    Texture2D mole = LoadTexture("texturs/mole.png");
    Texture2D bg = LoadTexture("texturs/bg.png");
    short moleCoords[2] = {640, 360};
    double currentWaitTime = 180;
    double wait = 180;
    unsigned long score = 0;
    Vector2 MXY = { -100.0f, -100.0f };
    InitAudioDevice();
    Music music = LoadMusicStream("texturs/un.mp3");
    std::string scoreSTR;
    short incramentLevel = 2;
    float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
    bool pause = false;  

    SetTargetFPS(60);
    PlayMusicStream(music);

    //game loop

    while (!WindowShouldClose()){

        UpdateMusicStream(music);   // Update music buffer with new stream data
        
        // Restart music playing (stop and play)
        if (IsKeyPressed(KEY_SPACE))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }

        // Pause/Resume music playing
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        // Get normalized time played for current music stream
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

        if (timePlayed > 1.0f) timePlayed = 1.0f;

        //Waiting function
        DrawTexture(bg, 0, 0, WHITE);

        if(wait < 1){
            wait = currentWaitTime;
            moleCoords[0] = rand() % 1280;
            moleCoords[1] = rand() % 720;; 
        }

        //score and difficulty calculator

        if(score > 1.5*incramentLevel){
            incramentLevel++;
            currentWaitTime = currentWaitTime - 2;
        }
        wait--;

        //random mole teleport

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(mole, moleCoords[0], moleCoords[1], WHITE);
        MXY = GetMousePosition();
        if(MXY.x < moleCoords[0] + 64 && MXY.y < moleCoords[1] + 48 && MXY.x > moleCoords[0] && MXY.y > moleCoords[1] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            score = score + 1;
            wait = currentWaitTime;
            moleCoords[0] = rand() % 1280 - 64;
            moleCoords[1] = rand() % 720 - 48; 
        }

        //convert C++ std::string to C string
        scoreSTR = std::to_string(score);
        
        std::string name = scoreSTR;
        char *c_string;

        c_string = new char[name.length()];

        for (int index = 0; index < name.length(); index++){
            c_string[index] = name[index];
        }
        c_string[name.length()] = '\0';
        char msg1[] = "Score: ";
        strcat(msg1, c_string);

        DrawText(msg1, 190, 200, 20, LIGHTGRAY);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}
