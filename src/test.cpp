#include <iostream>
#include <raylib.h>
#include <cmath>
#include "Vector.h"
#include "Mesh.h"

void fillTriangle(const utils::Vector2 &v1, const utils::Vector2 &v2, const utils::Vector2 &v3, const Color &color)
{
    float x1, x2, x3, y1, y2, y3;
    if(v1.y < v2.y) {
        if(v1.y < v3.y) {
        x1 = v1.x;
        y1 = v1.y;
        if(v2.y < v3.y) {
            x2 = v2.x;
            y2 = v2.y;
            x3 = v3.x;
            y3 = v3.y;
        } else {
            x2 = v3.x;
            y2 = v3.y;
            x3 = v2.x;
            y3 = v2.y;
        }
        } else {
        x1 = v3.x;
        y1 = v3.y;
        x2 = v1.x;
        y2 = v1.y;
        x3 = v2.x;
        y3 = v2.y;
        }
    } else {
        if(v2.y < v3.y) {
        x1 = v2.x;
        y1 = v2.y;
        if(v1.y < v3.y) {
            x2 = v1.x;
            y2 = v1.y;
            x3 = v3.x;
            y3 = v3.y;
        } else {
            x2 = v3.x;
            y2 = v3.y;
            x3 = v1.x;
            y3 = v1.y;
        }
        } else {
        x1 = v3.x;
        y1 = v3.y;
        x2 = v2.x;
        y2 = v2.y;
        x3 = v1.x;
        y3 = v1.y;
        }
    }
    
    float ma = (y2 - y1) / (x2 - x1);
    float ka = ma == 0 ? 0 : x1 - y1/ma;
    
    float mb = (y3 - y2) / (x3 - x2);
    float kb = mb == 0 ? 0 : x2 - y2/mb;
    
    float mc = (y1 - y3) / (x1 - x3);
    float kc = mc == 0 ? 0 : x3 - y3/mc;
    
    float y = y1;
    while(y < y2) {
        float x_left  = mc == 0 ? 0 : y/mc + kc;
        float x_right = ma == 0 ? 0 : y/ma + ka;
        int p = (int)round(x_left);
        int q = (int)round(x_right);
        int pixel_y = (int)round(y);
        int pixel_left_x, pixel_right_x;
        if(p < q) {
            pixel_left_x = p;
            pixel_right_x = q;
        } else {
            pixel_right_x = p;
            pixel_left_x = q;
        }
        for(int x = pixel_left_x; x <= pixel_right_x; x++) {
            DrawPixel(x, pixel_y, color);
        }
        y += 1;
    }
    while(y < y3) {
        float x_left = y/mc + kc;
        float x_right = y/mb + kb;
        int p = (int)round(x_left);
        int q = (int)round(x_right);
        int pixel_y = (int)round(y);
        int pixel_left_x, pixel_right_x;
        if(p < q) {
            pixel_left_x = p;
            pixel_right_x = q;
        } else {
            pixel_right_x = p;
            pixel_left_x = q;
        }
        for(int x = pixel_left_x; x <= pixel_right_x; x++) {
            DrawPixel(x, pixel_y, color);
        }
        y += 1;
    }
}

int main() {
    InitWindow(800, 600, "Test Window!");
    SetTargetFPS(60);
    utils::Vector2 p1 = utils::Vector2(200, 100);
    utils::Vector2 p2 = utils::Vector2(300, 200); 
    utils::Vector2 p3 = utils::Vector2(150, 300); 
    int selected = 0;
    while(!WindowShouldClose()) {
        utils::Vector2 mv = utils::Vector2(GetMouseX(), GetMouseY());
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if((mv - p1).length() < 10) {
                selected = 1;
            }
            if((mv - p2).length() < 10) {
                selected = 2;
            }
            if((mv - p3).length() < 10) {
                selected = 3;
            }
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            selected = 0;
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            switch(selected) {
                case 1: {
                    p1 = mv;
                    break;
                }
                case 2: {
                    p2 = mv;
                    break;
                }
                case 3: {
                    p3 = mv;
                    break;
                }
                default: {
                    break;
                }

            }
        }
        BeginDrawing();
        {
            ClearBackground(BLACK);
            fillTriangle(p1, p2, p3, WHITE);
            DrawCircle(p1.x, p1.y, 10, RED);
            DrawCircle(p2.x, p2.y, 10, RED);
            DrawCircle(p3.x, p3.y, 10, RED);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    return 0;
}