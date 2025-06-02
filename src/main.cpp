#include <raylib.h>
#include "Vector.h"
#include "Matrix.h"
#include "Mesh.h"

// specify vertices in counter-clockwise order
void drawTriangle(const utils::Vector3& v1, const utils::Vector3& v2, const utils::Vector3& v3, const Color& color) {
    DrawTriangleLines(
        (Vector2){v1.x, v1.y},
        (Vector2){v2.x, v2.y},
        (Vector2){v3.x, v3.y},
        color
    );
}
// specify vertices in counter-clockwise order
void fillTriangle(const utils::Vector3& v1, const utils::Vector3& v2, const utils::Vector3& v3, const Color& color) {
    DrawTriangle(
        (Vector2){v1.x, v1.y},
        (Vector2){v2.x, v2.y},
        (Vector2){v3.x, v3.y},
        color
    );
}

void update() {
    utils::Vector3 v1(100, 100, 0);
    utils::Vector3 v2(200, 100, 0);
    utils::Vector3 v3(150, 200, 0);
    fillTriangle(v1, v3, v2, RED);
}

int main() {
    const int SCREEN_WIDTH = 960, SCREEN_HEIGHT = 540;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rasterizer");
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);
            update();

        }
        EndDrawing();
    }

    CloseWindow();
}