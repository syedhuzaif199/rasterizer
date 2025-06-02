#include <raylib.h>
#include "Vector.h"
#include "Matrix.h"
#include "Mesh.h"
#include <iostream>

class Main {
    public:
    geometry::Mesh cube;
    Main(int screenWidth, int screenHeight) {
        InitWindow(screenWidth, screenHeight, "Rasterizer");
        SetTargetFPS(60);
        cube = geometry::Mesh::box(100.0f, 100.0f, 100.0f);
    }
    ~Main() {
        CloseWindow();
    }

    void run() {
        while(!WindowShouldClose()) {
            BeginDrawing();
            {
                ClearBackground(BLACK);
                update();
            }
            EndDrawing();
        }
    }

    void update() {
        for(const auto& face : cube.getFaces()) {
            const utils::Vector3& v1 = cube.getVertex(face.i0);
            const utils::Vector3& v2 = cube.getVertex(face.i1);
            const utils::Vector3& v3 = cube.getVertex(face.i2);
            Color color = BLUE;
            if (utils::Vector3::dot(v2 - v1, v3 - v1) < 0) {
                color = RED;
            }
            // Convert vertices to screen space
            v1 = toScreenSpace(v1);
            v2 = toScreenSpace(v2);
            v3 = toScreenSpace(v3);
            drawTriangle(v1, v2, v3, color);
        }
    }
    // specify vertices in counter-clockwise order
    void drawTriangle(const utils::Vector3& v1, const utils::Vector3& v2, const utils::Vector3& v3, const Color& color) {
        std::cout << "Drawing triangle: "
                  << v1 << ", " << v2 << ", " << v3 << std::endl;
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

    utils::Vector3 toScreenSpace(const utils::Vector3& v) {
        // Assuming a simple orthographic projection for now
        return utils::Vector3(v.x + GetScreenWidth() / 2.0f, -v.y + GetScreenHeight() / 2.0f, v.z);
    }
};

int main() {
    Main app(800, 600);
    app.run();
    return 0;
}