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

float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

class Main
{
public:
    geometry::Mesh mesh;
    utils::Vector4 lightDir;
    utils::Matrix4 projectionMatrix;
    utils::Matrix4 translateConstantZ;
    float yaw, pitch;
    utils::Vector4 cameraPosition = utils::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    Main(int screenWidth, int screenHeight)
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenWidth, screenHeight, "Rasterizer");
        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
        SetTargetFPS(60);
        // mesh = geometry::Mesh::sphere(1.0f, 12, 8);
        // mesh = geometry::Mesh::box(1.0f, 1.0f, 1.0f);

        mesh = geometry::Mesh::loadFromFileStatic("models/face.obj");

        yaw = 0;
        pitch = 0;
        // value of 'w' coordinate for directions should be 0
        lightDir = utils::Vector4(1.0f, 1.0f, 0.0f, 0.0f).normalized();
        projectionMatrix = utils::Matrix4::projection(90.0f, screenWidth, screenHeight, -0.1, -1000.0f);
        translateConstantZ = utils::Matrix4::translation(utils::Vector3(0.0f, 0.0f, -4.0f));
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
        yaw -= 0.05 * mouseDelta.x;
        pitch -= 0.05 * mouseDelta.y;
        pitch = clamp(
            pitch,
            degreesToRadians(-85),
            degreesToRadians(85)
        );
        // disable fixed rotation
        utils::Matrix4 rotationX = utils::Matrix4::rotationX(0 * 0.5 * GetTime());
        utils::Matrix4 rotationZ = utils::Matrix4::rotationZ(0 * 1.5 * GetTime());

        utils::Matrix4 rotateCameraX = utils::Matrix4::rotationX(pitch);
        utils::Matrix4 rotateCameraY= utils::Matrix4::rotationY(yaw);
        utils::Vector4 cameraLookDir = rotateCameraY * rotateCameraX * utils::Vector4(0, 0, -1, 0);
        cameraLookDir.normalize();
        utils::Vector4 cameraRight = utils::Vector4::cross(cameraLookDir, utils::Vector4(0, 1, 0, 0));
        cameraRight.normalize();
        utils::Vector4 cameraUp = utils::Vector4::cross(cameraRight, cameraLookDir);

        float cameraSpeedUp = 10.0f;
        float cameraSpeedRight = 10.0f;
        float cameraSpeedForward = 10.0f;
        if(IsKeyDown(KEY_Q)) {
            cameraPosition.y += cameraSpeedUp * GetFrameTime();
        }

        if(IsKeyDown(KEY_E)) {
            cameraPosition.y -= cameraSpeedUp * GetFrameTime();
        }

        if(IsKeyDown(KEY_A)) {
            cameraPosition -= cameraRight * cameraSpeedRight * GetFrameTime();
        }

        if(IsKeyDown(KEY_D)) {
            cameraPosition += cameraRight * cameraSpeedRight * GetFrameTime();
        }

        if(IsKeyDown(KEY_W)) {
            utils::Vector4 worldUp = utils::Vector4(0, 1, 0, 0);
            utils::Vector4 forward = cameraLookDir -  worldUp * cameraLookDir.dot(worldUp);
            forward.normalize();
            cameraPosition += forward * cameraSpeedForward * GetFrameTime();
        }

        if(IsKeyDown(KEY_S)) {
            utils::Vector4 worldUp = utils::Vector4(0, 1, 0, 0);
            utils::Vector4 forward = cameraLookDir -  worldUp * cameraLookDir.dot(worldUp);
            forward.normalize();
            cameraPosition -= forward * cameraSpeedForward * GetFrameTime();
        }

        utils::Matrix4 translateCameraToOrigin = utils::Matrix4::translation(
            -cameraPosition.x,
            -cameraPosition.y,
            -cameraPosition.z
        );
        utils::Matrix4 changeBasisToCamera = utils::Matrix4(
            cameraRight.x, cameraRight.y, cameraRight.z, 0,
            cameraUp.x, cameraUp.y, cameraUp.z, 0, 
            -cameraLookDir.x, -cameraLookDir.y, -cameraLookDir.z, 0,
            0, 0, 0, 1
        );
        utils::Matrix4 viewMatrix = changeBasisToCamera * translateCameraToOrigin;
        for (const auto &face : mesh.getFaces())
        {
            utils::Vector4 v1 = utils::Vector4(mesh.getVertex(face.i0));
            utils::Vector4 v2 = utils::Vector4(mesh.getVertex(face.i1));
            utils::Vector4 v3 = utils::Vector4(mesh.getVertex(face.i2));
            v1 = rotationZ * rotationX * v1;
            v2 = rotationZ * rotationX * v2;
            v3 = rotationZ * rotationX * v3;
            

            v1 = translateConstantZ * v1;
            v2 = translateConstantZ * v2;
            v3 = translateConstantZ * v3;

            utils::Vector4 normal = utils::Vector4::cross(v2 - v1, v3 - v1);
            normal.normalize();

            // TODO: remove hardcoded camera direction
            // NOTE: the face facing the camera must have it's normal in the opposite
            // direction to that of the camera's forward (-1 along z in this case).
            // So, the dot product of the normal of the face that is visible with
            // the camera's fowrard cannot be non-negative.
            // if (normal.dot(utils::Vector4(0, 0, -1, 0)) >= 0)
            if (normal.dot(cameraLookDir) >= 0)
            {
                continue;
            }
            float brightness = max(0.2, utils::Vector4::dot(normal, lightDir));
            Color color = ColorFromHSV(0, 0.0f, brightness);

            v1 = viewMatrix * v1;
            v2 = viewMatrix * v2;
            v3 = viewMatrix * v3;

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
