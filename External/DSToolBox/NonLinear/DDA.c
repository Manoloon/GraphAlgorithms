#include "DDA.h"
#include "raylib.h"

/*
    Digital Differencial Analyzer
*/

#define NUMCELLS_X 32
#define NUMCELLS_Y 30
#define CELLSIZE 16
#define PLAYER_SPEED 0.05

void DDA_update(float DeltaTime)
{
    static vec2f Player = {0,0};
    vec2f MousePos = {GetMousePosition().x,GetMousePosition().y};
    vec2f MouseCell = {MousePos.x / CELLSIZE,MousePos.y / CELLSIZE};
    static int VecMap[NUMCELLS_X][NUMCELLS_Y];

    // definir input para mover el player con AWSD
    if(IsKeyDown(KEY_W))
    {
        Player.y -= PLAYER_SPEED * DeltaTime;
    }
    else if (IsKeyDown(KEY_S))
    {
        Player.y += PLAYER_SPEED * DeltaTime;
    }
    if(IsKeyDown(KEY_A))
    {
        Player.x -= PLAYER_SPEED * DeltaTime;
    }
    else if (IsKeyDown(KEY_D))
    {
        Player.x += PLAYER_SPEED * DeltaTime;
    }
    // definir input para crear solidos en el mundo con el click izq;
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Mouse is being click)
    {
        //TODO : opcion a borrar la pared si ya existe
        VecMap[(int)MouseCell.x][(int)MouseCell.y] = 1;
    }
    // DDA
    vec2f RayStart = Player;
    vec2f dir = {MouseCell.x - Player.x,MouseCell.y - Player.y};
    vec2f RayDir = vec2f_normalize(dir);
    vec2f RayUnitStepSize = {sqrt(1+(RayDir.y / RayDir.x)*(RayDir.y/RayDir.x)),
                            sqrt(1+(RayDir.x/RayDir.y)*(RayDir.x/RayDir.y))};
    
    vec2i MapCheck = to_vec2i(RayStart);
    vec2f RayLength1D;
    vec2i Step;

    if(RayDir.x < 0)
    {
        Step.x = -1;
        RayLength1D.x = (RayStart.x - MapCheck.x) * RayUnitStepSize.x;
    }
    else
    {
        Step.x = 1;
        RayLength1D.x = ((MapCheck.x + 1) - RayStart.x) * RayUnitStepSize.x;
    }

    if(RayDir.y < 0)
    {
        Step.y = -1;
        RayLength1D.y = (RayStart.y - MapCheck.y) * RayUnitStepSize.y;
    }
    else
    {
        Step.y = 1;
        RayLength1D.y = ((MapCheck.y + 1) - RayStart.y) * RayUnitStepSize.y;
    }

    // walk until collision or range check
    bool bTileFound = false;
    float MaxDistance = 100.f;
    float Distance = 0.0f;
    vec2f Intersection = {0};
    
    while (!bTileFound && Distance < MaxDistance)
    {
        // Shortest path
       if(RayLength1D.x < RayLength1D.y)
       {
            MapCheck.x += Step.x;
            Distance = RayLength1D.x;
            RayLength1D.x += RayUnitStepSize.x;
       }
       else
       {
            MapCheck.y += Step.y;
            Distance = RayLength1D.y;
            RayLength1D.y += RayUnitStepSize.y;
       }

       // test tile at new test point
       if(MapCheck.x >= 0 && MapCheck.x < NUMCELLS_X && MapCheck.y >= 0 && MapCheck.y < NUMCELLS_Y)
       {
        // if(VecMap[MapCheck.y * MAPSIZE_X + MapCheck.x] == 1)
            if(VecMap[MapCheck.x][MapCheck.y] == 1)
                bTileFound = true;
       }
    }

    // calculate intersection
  
    if(bTileFound)
    {
        Intersection = (vec2f){RayStart.x + RayDir.x * Distance,RayStart.y + RayDir.y * Distance};
    }

    ClearBackground(BLACK);
    // Draw map
    for(int y = 0; y < NUMCELLS_Y;++y)
    {
        for(int x = 0; x < NUMCELLS_X;++x)
        {
            if(VecMap[x][y] == 1)
            {
                DrawRectangle(x * CELLSIZE,y * CELLSIZE,CELLSIZE,CELLSIZE,BLUE);
            }
            else
            {
                DrawRectangleLines(x * CELLSIZE,y * CELLSIZE,CELLSIZE,CELLSIZE,DARKGRAY);
            }
        }
    }

       // rayCast
        DrawLine(Player.x * CELLSIZE , Player.y * CELLSIZE, MousePos.x,MousePos.y,WHITE); // 0xF0F0F0F0 intermitent
            
        if(bTileFound)
        {
            DrawCircle(Intersection.x * CELLSIZE,Intersection.y * CELLSIZE,4.0f,YELLOW);
        }
        // draw player
        DrawCircle(Player.x * CELLSIZE,Player.y * CELLSIZE,4.0f,RED);
        // draw Mouse
        DrawCircle(MousePos.x,MousePos.y,4.0f,GREEN);
}

void DDA_test()
{
    InitWindow(640,480,"DDA Test");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        double DeltaTime = GetTime();
        BeginDrawing();
        DDA_update(DeltaTime);
        EndDrawing();
    }
    CloseWindow();    
}