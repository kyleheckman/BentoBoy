#include "gb_video.h"
#include "raylib.h"

int openWindow() {
    int scrn_width = 160;
    int scrn_height = 144;

    InitWindow(scrn_width, scrn_height, "BentoBoy");
    SetTargetFPS(60);
}

