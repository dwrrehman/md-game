
#include "raylib.h"

static void DrawCubeCustom(
	Texture2D texture1, Texture2D texture2, 
	Vector3 position, float width, float height, 
	float length, Color color
) {
	float x = position.x;
	float y = position.y;
	float z = position.z;
	if (rlCheckBufferLimit(36)) Rlgl.rlglDraw();
	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);
	rlEnableTexture(texture1.id);
	rlNormal3f(0.0f, 0.0f, 1.0f);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
	rlNormal3f(0.0f, 0.0f, -1.0f);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
	rlEnableTexture(texture2.id);
	rlNormal3f(0.0f, 1.0f, 0.0f);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
	rlNormal3f(0.0f, -1.0f, 0.0f);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
	rlNormal3f(1.0f, 0.0f, 0.0f);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
	rlNormal3f(-1.0f, 0.0f, 0.0f);
	rlTexCoord2f(0.0f, 0.0f);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(1.0f, 0.0f);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f(1.0f, 1.0f);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(0.0f, 1.0f);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
	rlEnd();
	rlDisableTexture();
}

int main(void) {

	Raylib.SetConfigFlags(ConfigFlag.FLAG_MSAA_4X_HINT);

	Raylib.InitWindow(800, 450, "CubemapTexture1");

	Camera3D camera = {0};
		position = new Vector3(10.0f, 10.0f, 10.0f),
		target = new Vector3(0.0f, 0.0f, 0.0f),
		up = new Vector3(0.0f, 1.0f, 0.0f),
		fovy = 45.0f,
		type = CameraType.CAMERA_PERSPECTIVE,
	};
	Vector3 cubePosition = new Vector3(0.0f, 0.0f, 0.0f);
	Texture2D texture1 = Raylib.LoadTexture("data/container2.png");
	Texture2D texture2 = Raylib.LoadTexture("data/awesomeface.png");
	Raylib.SetCameraMode(camera, CameraMode.CAMERA_ORBITAL);
	SetTargetFPS(60); 

	while (!WindowShouldClose()) {

		UpdateCamera(&camera);
		BeginDrawing();
		ClearBackground(new Color(51, 76, 76, 255));
		BeginMode3D(camera);
		DrawCubeCustom(texture1, texture2, cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
		DrawGrid(10, 1.0f);
		EndMode3D();
		EndDrawing();
	}

	Raylib.UnloadTexture(texture1);
	Raylib.UnloadTexture(texture2);
	Raylib.CloseWindow();

	return 0;
}

