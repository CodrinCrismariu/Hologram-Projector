#include <raylib-cpp.hpp>
#include <iostream>
#include <fstream>
#include <vector>

struct Triangle {
    Vector3 v1, v2, v3;
    Triangle(const Vector3 &V1, const Vector3 &V2, const Vector3 &V3) {
        v1 = V1;
        v2 = V2;
        v3 = V3;
    }
};

double maxVertex = 0;

std::vector< Triangle > parseSTLfile(std::string filepath) {

    std::vector< Triangle > parsedTriangles;
    std::vector< Vector3 > vertexBuffer;

    // noob parsing strategy but works for now

    std::ifstream fin(filepath);
    std::ofstream fout("out");

    std::string in;
    double x, y, z;

    while(fin >> in) {

        if(in == "vertex") {
            fin >> x >> y >> z;
            maxVertex = std::max(std::abs(x), maxVertex);
            maxVertex = std::max(std::abs(y), maxVertex);
            maxVertex = std::max(std::abs(z), maxVertex);
            vertexBuffer.push_back( (Vector3){x, y, z} );
        }

        if(vertexBuffer.size() == 3) {
            parsedTriangles.push_back( Triangle(
                vertexBuffer[0],
                vertexBuffer[1],
                vertexBuffer[2]
            ));
            vertexBuffer.clear();
        }

    }

    return parsedTriangles;

}

int main() {
    
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE);
    
    SetTargetFPS(60);

    std::vector < Triangle > triangles = parseSTLfile("cube.stl");

    for(Triangle &trig : triangles) {
        trig.v1.x = trig.v1.x / maxVertex - 0.5;
        trig.v1.y = trig.v1.y / maxVertex - 0.5;
        trig.v1.z = trig.v1.z / maxVertex - 0.5;

        trig.v2.x = trig.v2.x / maxVertex - 0.5;
        trig.v2.y = trig.v2.y / maxVertex - 0.5;
        trig.v2.z = trig.v2.z / maxVertex - 0.5;

        trig.v3.x = trig.v3.x / maxVertex - 0.5;
        trig.v3.y = trig.v3.y / maxVertex - 0.5;
        trig.v3.z = trig.v3.z / maxVertex - 0.5;
    }

    // Main game loop
    while (!w.ShouldClose()) {

        UpdateCamera(&camera);

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                for(Triangle trig : triangles) {
                    DrawTriangle3D(trig.v1, trig.v2, trig.v3, RED);
                    DrawLine3D(trig.v1, trig.v2, MAROON);
                    DrawLine3D(trig.v2, trig.v3, MAROON);
                    DrawLine3D(trig.v1, trig.v3, MAROON);
                }
                

            EndMode3D();

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText((std::string("- Z to zoom to (0, 0, 0)")).c_str(), 40, 120, 10, DARKGRAY);

        EndDrawing();

    }

    return 0;
}
