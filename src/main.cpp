#include <raylib.h>
#include "Vector.h"
#include "Matrix.h"
#include "Mesh.h"
#include <iostream>

float max(float a, float b)
{
    return (a > b) ? a : b;
}
float min(float a, float b)
{
    return (a < b) ? a : b;
}

float clamp(float value, float minValue, float maxValue)
{
    return (value < minValue) ? minValue : (value > maxValue) ? maxValue
                                                              : value;
}

class Main
{
public:
    geometry::Mesh mesh;
    utils::Vector4 lightDir;
    Main(int screenWidth, int screenHeight)
    {
        InitWindow(screenWidth, screenHeight, "Rasterizer");
        SetTargetFPS(60);
        mesh = geometry::Mesh::sphere(200.0f, 12, 8);
        // mesh = geometry::Mesh::box(200.0f, 200.0f, 200.0f);

        // value of 'w' coordinate for directions should be 0
        lightDir = utils::Vector4(1.0f, 1.0f, 0.0f, 0.0f).normalized();
    }
    ~Main()
    {
        CloseWindow();
    }

    void run()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            {
                ClearBackground(BLACK);
                update();
            }
            EndDrawing();
        }
    }

    void update()
    {
        for (const auto &face : mesh.getFaces())
        {
            utils::Matrix4 rotationX = utils::Matrix4::rotationX(0.5 * GetTime());
            utils::Matrix4 rotationZ = utils::Matrix4::rotationZ(1.5 * GetTime());
            utils::Vector4 v1 = utils::Vector4(mesh.getVertex(face.i0));
            utils::Vector4 v2 = utils::Vector4(mesh.getVertex(face.i1));
            utils::Vector4 v3 = utils::Vector4(mesh.getVertex(face.i2));
            v1 = rotationX * rotationZ * v1;
            v2 = rotationX * rotationZ * v2;
            v3 = rotationX * rotationZ * v3;
            utils::Vector4 normal = utils::Vector4::cross(v2 - v1, v3 - v1);
            normal.normalize();

            // TODO: remove hardcoded camera direction
            if (normal.dot(utils::Vector3(0, 0, 1)) < 0)
            {
                continue;
            }
            // Convert vertices to screen space
            utils::Vector2 screenV1 = toScreenSpace(v1);
            utils::Vector2 screenV2 = toScreenSpace(v2);
            utils::Vector2 screenV3 = toScreenSpace(v3);
            float brightness = max(0.2, utils::Vector4::dot(normal, lightDir));
            Color color = ColorFromHSV(0, 0.0f, brightness);
            fillTriangle(screenV1, screenV2, screenV3, color);
        }
    }
    // specify vertices in counter-clockwise order
    void drawTriangle(const utils::Vector2 &v1, const utils::Vector2 &v2, const utils::Vector2 &v3, const Color &color)
    {
        DrawTriangleLines(
            (Vector2){v1.x, v1.y},
            (Vector2){v2.x, v2.y},
            (Vector2){v3.x, v3.y},
            color);
    }
    // specify vertices in counter-clockwise order
    void fillTriangle(const utils::Vector2 &v1, const utils::Vector2 &v2, const utils::Vector2 &v3, const Color &color)
    {
        DrawTriangle(
            (Vector2){v1.x, v1.y},
            (Vector2){v2.x, v2.y},
            (Vector2){v3.x, v3.y},
            color);
    }

    utils::Vector2 toScreenSpace(const utils::Vector4 &v)
    {
        // Assuming a simple orthographic projection for now
        return utils::Vector2(v.x + GetScreenWidth() / 2.0f, -v.y + GetScreenHeight() / 2.0f);
    }
};

int main()
{
    Main app(1080, 720);
    app.run();
    return 0;
}
