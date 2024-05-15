// C raylib client for a block game.
// written by dwrr on 202405131.211411

#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iso646.h>

typedef uint64_t nat; 
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t byte;

static const int screen_width = 800;
static const int screen_height = 450;

int main(void) {
	SetRandomSeed(42);

	Image img = LoadImage("assets/dirt.png");
	Texture2D tex = LoadTextureFromImage(img);
	UnloadImage(img);

	float heights[20] = {0};
	Vector3 positions[20] = {0};
	Color colors[20] = {0};

	for (int i = 0; i < 20; i++) {
		heights[i] = (float)GetRandomValue(1, 12);
		positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
		colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
	}

	InitWindow(screen_width, screen_width, "block game");

	Camera camera = {0};
	camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 2.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();
	SetTargetFPS(120);

	while (true) {

		if (IsKeyPressed(KEY_ESCAPE)) break; 
		if (IsKeyPressed(KEY_COMMA)) TakeScreenshot("screenshot.png");
		if (IsKeyPressed(KEY_PERIOD)) OpenURL("https://google.com");
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);
		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); 
		DrawCubeTexture(tex, (Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, BLUE);
		EndMode3D();

		DrawText("first person camera test", 15, 15, 10, BLACK);		
		DrawText(TextFormat("Position: (%06.3f, %06.3f, %06.3f)", 
				camera.position.x, camera.position.y, camera.position.z), 
			610, 60, 10, BLACK
		);

		EndDrawing();
	}
	CloseWindow(); 
}












/*


DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);
		DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
		DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);
		for (int i = 0; i < 20; i++) {
			DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
			DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
		}
		DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(5, 5, 330, 100, BLUE);
		DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(600, 5, 195, 100, BLUE);





int main(void) {

	InitWindow(screen_width, screen_width, "dwrr's sandbox block game");

	Mesh mesh = {0};

	mesh.triangleCount = 1;
	mesh.vertexCount = mesh.triangleCount * 3;
	mesh.vertices = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));  
	mesh.texcoords = (float *) MemAlloc(mesh.vertexCount * 2 * sizeof(float)); 
	mesh.normals = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float)); 

	mesh.vertices[0] = 0;
	mesh.vertices[1] = 0;
	mesh.vertices[2] = 0;
	mesh.normals[0] = 0;
	mesh.normals[1] = 1;
	mesh.normals[2] = 0;
	mesh.texcoords[0] = 0;
	mesh.texcoords[1] = 0;

	mesh.vertices[3] = 1;
	mesh.vertices[4] = 0;
	mesh.vertices[5] = 2;
	mesh.normals[3] = 0;
	mesh.normals[4] = 1;
	mesh.normals[5] = 0;
	mesh.texcoords[2] = 0.5f;
	mesh.texcoords[3] = 1.0f;

	mesh.vertices[6] = 2;
	mesh.vertices[7] = 0;
	mesh.vertices[8] = 0;
	mesh.normals[6] = 0;
	mesh.normals[7] = 1;
	mesh.normals[8] = 0;
	mesh.texcoords[4] = 1;
	mesh.texcoords[5] = 0;

	UploadMesh(&mesh, false);


	Image checked = GenImageChecked(3, 3, 1, 1, RED, GREEN);
	Texture2D texture = LoadTextureFromImage(checked);
	UnloadImage(checked);

	Model models[1] = {0};
	models[0] = LoadModelFromMesh(mesh);
	models[0].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	Camera camera = { 
		{ 5.0f, 5.0f, 5.0f }, 
		{ 0.0f, 0.0f, 0.0f }, 
		{ 0.0f, 1.0f, 0.0f }, 
		45.0f, 
		0 
	};

	Vector3 position = { 0.0f, 0.0f, 0.0f };
 
	SetTargetFPS(120);
    
	while (not WindowShouldClose()) {
        	UpdateCamera(&camera, CAMERA_ORBITAL);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			
		}

		if (IsKeyDown(KEY_A)) position.x -= 0.1f;
		else if (IsKeyDown(KEY_F)) position.x += 0.1f;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);
		DrawModel(models[0], position, 1.0f, WHITE);
		DrawGrid(10, 1.0);
		EndMode3D();

		DrawRectangle(30, 400, 310, 30, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(30, 400, 310, 30, Fade(DARKBLUE, 0.5f));
		DrawText("test of the block game...", 40, 410, 10, BLACK);
		DrawText("custom mesh", 580, 10, 20, DARKBLUE); 
		EndDrawing();
	}

    	UnloadTexture(texture);
	UnloadModel(models[0]);
	CloseWindow();
}
*/







