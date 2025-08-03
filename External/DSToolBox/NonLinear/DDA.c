#include "DDA.h"
#include "raylib.h"

/*
    Digital Differencial Analyzer
*/

#define MAPSIZE_X 32
#define MAPSIZE_Y 30
#define CELLSIZE 16

void DDA_update(float DeltaTime,vec2f Player)
{
    vec2f MousePos = {GetMousePosition().x,GetMousePosition().y};
    vec2f MouseCell = {MousePos.x / CELLSIZE,MousePos.y / CELLSIZE};
    int VecMap[MAPSIZE_X][MAPSIZE_Y];

    // definir input para mover el player con el mouse 
    // definir input para crear solidos en el mundo con el click izq;

    // DDA
    vec2f RayStart = Player;
    vec2f dir = {MouseCell.x - Player.x,MouseCell.y - Player.y};
    vec2f RayDir = vec2f_normalize(dir);
    
    vec2f RayUnitStepSize = { sqrt(1+(RayDir.y / RayDir.x)*(RayDir.y/RayDir.x)),
                                sqrt(1+(RayDir.x/RayDir.y)*(RayDir.x/RayDir.y))};
    
    vec2i MapCheck = to_vec2i(RayStart);
    vec2i RayLength1D;
    vec2i Step;

    if(RayDir.x < 0)
    {
        Step.x = -1;
        RayLength1D.x = (RayStart.x - MapCheck.x) * RayUnitStepSize.x;
    }
    else
    {
        Step.x = 1;
        RayLength1D.x = ((RayStart.x + 1) - RayStart.x) * RayUnitStepSize.x;
    }

    if(RayDir.y < 0)
    {
        Step.y = -1;
        RayLength1D.y = (RayStart.y - MapCheck.y) * RayUnitStepSize.y;
    }
    else
    {
        Step.y = 1;
        RayLength1D.y = ((RayStart.y + 1) - RayStart.y) * RayUnitStepSize.y;
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
       if(MapCheck.x >= 0 && MapCheck.x < MAPSIZE_X && MapCheck.y >= 0 && MapCheck.y < MAPSIZE_Y)
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
    for(int y = 0; y < MAPSIZE_Y;++y)
    {
        for(int x = 0; x < MAPSIZE_X;++x)
        {
            Color color = (VecMap[x][y] == 1) ? BLUE : DARKGRAY;
            DrawRectangle(x,y,CELLSIZE,CELLSIZE,color);
        }
    }

    // create a solid tile
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) // Mouse is being click)
        {
            DrawLine(Player.x , Player.y, Player.x * CELLSIZE,Player.y * CELLSIZE,WHITE); // 0xF0F0F0F0 intermitent
            if(bTileFound)
            {
                DrawCircle(Intersection.x * CELLSIZE,Intersection.y * CELLSIZE,4.0f,YELLOW);
            }
        }
        // draw player
        DrawCircle(Intersection.x * CELLSIZE,Intersection.y * CELLSIZE,4.0f,RED);
        // draw Mouse
        DrawCircle(MousePos.x,MousePos.y,4.0f,GREEN);
}

void DDA_test()
{
    InitWindow(640,480,"DDA Test");
    SetTargetFPS(60);
    vec2f loc_player = {0,0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DDA_update(1.0f,loc_player);
        EndDrawing();
    }
    CloseWindow();    
}