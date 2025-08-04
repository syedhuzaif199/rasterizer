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
    utils::Matrix4 projectionMatrix;
    utils::Matrix4 translateConstantZ;
    float yaw, pitch;
    Main(int screenWidth, int screenHeight)
    {
        InitWindow(screenWidth, screenHeight, "Rasterizer");
        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
        SetTargetFPS(60);
        // mesh = geometry::Mesh::sphere(1.0f, 12, 8);
        // mesh = geometry::Mesh::box(1.0f, 1.0f, 1.0f);

        mesh = geometry::Mesh::loadFromFileStatic("models/face.obj");

        for(auto face: mesh.getFaces()) {
            std::cout << "f " << face.i0+1 << " " << face.i1+1 << " " << face.i2+1 << std::endl;
        }

        yaw = 0;
        pitch = 0;
        // value of 'w' coordinate for directions should be 0
        lightDir = utils::Vector4(1.0f, 1.0f, 0.0f, 0.0f).normalized();
        projectionMatrix = utils::Matrix4::projection(90.0f, screenWidth, screenHeight, -0.1, -1000.0f);
        translateConstantZ = utils::Matrix4::translation(utils::Vector3(0.0f, 0.0f, -4.0f));
        std::cout << projectionMatrix << std::endl;
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
        Vector2 mouseDelta = GetMouseDelta();
        yaw += 0.05 * mouseDelta.x;
        pitch += 0.05 * mouseDelta.y;
        pitch = clamp(pitch, -PI/2, PI/2);
        // disable fixed rotation
        // utils::Matrix4 rotationX = utils::Matrix4::rotationX(1 * 0.5 * GetTime());
        // utils::Matrix4 rotationZ = utils::Matrix4::rotationZ(1 * 1.5 * GetTime());
        utils::Matrix4 rotationX = utils::Matrix4::rotationX(pitch);
        utils::Matrix4 rotationY = utils::Matrix4::rotationY(yaw);
        for (const auto &face : mesh.getFaces())
        {
            utils::Vector4 v1 = utils::Vector4(mesh.getVertex(face.i0));
            utils::Vector4 v2 = utils::Vector4(mesh.getVertex(face.i1));
            utils::Vector4 v3 = utils::Vector4(mesh.getVertex(face.i2));
            v1 = rotationY * rotationX * v1;
            v2 = rotationY * rotationX * v2;
            v3 = rotationY * rotationX * v3;

            

            v1 = translateConstantZ * v1;
            v2 = translateConstantZ * v2;
            v3 = translateConstantZ * v3;

            utils::Vector4 normal = utils::Vector4::cross(v2 - v1, v3 - v1);
            normal.normalize();

            // TODO: remove hardcoded camera direction
            if (normal.dot(utils::Vector4(0, 0, 1, 0)) < 0)
            {
                continue;
            }
            float brightness = max(0.2, utils::Vector4::dot(normal, lightDir));
            Color color = ColorFromHSV(0, 0.0f, brightness);

            v1 = projectionMatrix * v1;
            v2 = projectionMatrix * v2;
            v3 = projectionMatrix * v3;

            // Convert vertices to screen space
            utils::Vector2 screenV1 = toScreenSpace(v1);
            utils::Vector2 screenV2 = toScreenSpace(v2);
            utils::Vector2 screenV3 = toScreenSpace(v3);
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
        utils::Vector2 vScreen = utils::Vector2(v.x, v.y);
        if (v.w != 0)
        {
            vScreen /= v.w;
        }
        vScreen += 1.0f;
        vScreen *= 0.5f;
        vScreen.x *= GetScreenWidth();
        vScreen.y = (1 - vScreen.y);
        vScreen.y *= GetScreenHeight();
        return vScreen;
    }
};

int main()
{
    Main app(1080, 720);
    app.run();
    return 0;
}
