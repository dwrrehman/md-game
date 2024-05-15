
#include "raylib.h"


static Mesh GenMeshCustom(void) {

    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *) MemAlloc(mesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

int main(void) {
    InitWindow(800, 450, "dwrr");

    Texture2D texture = LoadTexture("./blocks.png");

    Model models[2] = {0};
    models[0] = LoadModelFromMesh(GenMeshCube(2.0f, 2.0f, 2.0f));
    models[1] = LoadModelFromMesh(GenMeshCustom());

    for (int i = 0; i < 2; i++) models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    int currentModel = 0;
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            
        }
	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(camera);
	DrawModel(models[currentModel], position, 1.0f, WHITE);
	DrawGrid(10, 1.0);
	EndMode3D();
	DrawRectangle(30, 400, 310, 30, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(30, 400, 310, 30, Fade(DARKBLUE, 0.5f));
	DrawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL MODELS", 40, 410, 10, BLUE);
	EndDrawing();
    }
    UnloadTexture(texture); // Unload texture
    for (int i = 0; i < 2; i++) UnloadModel(models[i]);
    CloseWindow(); 
}

