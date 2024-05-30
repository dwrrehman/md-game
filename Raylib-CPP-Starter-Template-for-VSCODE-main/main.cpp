// test of the raylib library: 202405153.132240: dwrr
#include <raylib.h>
#include "rcamera.h"
#include <stdio.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#define CAMERA_ROTATION_SPEED         0.03f
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.003f   
#define camera_accel  0.01f
Vector3 camera_velocity = (Vector3){ 0.0f, 0.0f, 0.0f};

static const int screen_width = 1280;
static const int screen_height = 800;
static const float playerheight = 1.0; //blue to orange, so real height is 2F
static const float playerwidth = .50; //blue to orange, so real height is 2F
static const int s = 200; //size
static const int space_count = s * s * s; //3d terrain
static int8_t* space = nullptr; //initialized in main



enum blocks { // BLOCKS!
    air_block, grass_block, dirt_block,
    stone_block, granite_block, wood_block,
    leaves_block, water_block, moss_block,
    iron_ore_block, off_cell_block, on_cell_block,
    off_path_block, on_path_block, glass_block, plank_block, flower, block_count
};




void my_UpdateCamera(Camera *camera, int mode) {
	Vector2 mousePositionDelta = GetMouseDelta();
	bool moveInWorldPlane = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
	bool rotateAroundTarget = ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
	bool lockView = ((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
	bool rotateUp = false;
	if (IsKeyDown(KEY_DOWN)) CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
	if (IsKeyDown(KEY_UP)) CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
	if (IsKeyDown(KEY_RIGHT)) CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
	if (IsKeyDown(KEY_LEFT)) CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);
	CameraYaw(camera, -mousePositionDelta.x*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);//looking up/down
	CameraPitch(camera, -mousePositionDelta.y*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);//left to right (head movement)
	
     //1 = positive
   int c000, c001, c011, c010, c100, c101, c111, c110;


    c000 = ((int)(camera->position.x-playerwidth)*s*s) + ((int)(camera->position.y-playerheight)*s) + ((int)(camera->position.z-playerwidth)) ;
    c001 = ((int)(camera->position.x-playerwidth)*s*s) + ((int)(camera->position.y-playerheight)*s) + ((int)(camera->position.z+playerwidth)) ;
    c010 = ((int)(camera->position.x-playerwidth)*s*s) + ((int)(camera->position.y+playerheight)*s) + ((int)(camera->position.z-playerwidth)) ;
    c011 = ((int)(camera->position.x-playerwidth)*s*s) + ((int)(camera->position.y+playerheight)*s) + ((int)(camera->position.z+playerwidth)) ;
    c100 = ((int)(camera->position.x+playerwidth)*s*s) + ((int)(camera->position.y-playerheight)*s) + ((int)(camera->position.z-playerwidth)) ;
    c101 = ((int)(camera->position.x+playerwidth)*s*s) + ((int)(camera->position.y-playerheight)*s) + ((int)(camera->position.z+playerwidth)) ;
    c110 = ((int)(camera->position.x+playerwidth)*s*s) + ((int)(camera->position.y+playerheight)*s) + ((int)(camera->position.z-playerwidth)) ;
    c111 = ((int)(camera->position.x+playerwidth)*s*s) + ((int)(camera->position.y+playerheight)*s) + ((int)(camera->position.z+playerwidth)) ;
//if c000 etc != 0 or 1 set velocity ot 0.


	bool feetonfloor = space[((int)camera->position.x*s*s) + ((int)(camera->position.y-playerheight)*s) + ((int)camera->position.z)];
           std:: cout << int(space[c000]) << " ";
            std:: cout << int(space[c001]) << " ";
            std:: cout << int(space[c010]) <<" ";
            std:: cout << int(space[c011]) << " ";
            std:: cout << int(space[c100]) << " ";
            std:: cout << int(space[c101]) << " ";
            std:: cout << int(space[c110]) << " ";
            std:: cout << int(space[c111]) << " \n";



	 if(!feetonfloor){
		std:: cout << "! !found air block\n";
			if (IsKeyDown(KEY_W)) camera_velocity.z += camera_accel;
			if (IsKeyDown(KEY_S)) camera_velocity.z -= camera_accel;
			if (IsKeyDown(KEY_A)) camera_velocity.x -= camera_accel;
			if (IsKeyDown(KEY_D)) camera_velocity.x += camera_accel;
			if (IsKeyDown(KEY_SPACE)) camera_velocity.y += camera_accel;
			if (IsKeyDown(KEY_LEFT_SHIFT)) camera_velocity.y -= camera_accel;
			CameraMoveForward(camera, camera_velocity.z, moveInWorldPlane);
			CameraMoveRight(camera, camera_velocity.x, moveInWorldPlane);
			CameraMoveUp(camera, camera_velocity.y);
			camera_velocity.x *= 0.95;
			camera_velocity.y *= 0.95;
			camera_velocity.z *= 0.95;
			CameraMoveToTarget(camera, -GetMouseWheelMove());
			if (IsKeyPressed(KEY_G)) CameraMoveToTarget(camera, 2.0f);
			if (IsKeyPressed(KEY_Y)) CameraMoveToTarget(camera, -2.0f);

	 }
	 else{
		float friction = 0.2;
           
          
     
          


     if (int(space[c000]) != 1 || int(space[c001]) != 1 ){  camera_velocity.z = 0;  camera->position.z  -= .07;}
            else if (IsKeyDown(KEY_W) && space[c000] && space[c001] ) {    camera_velocity.z += camera_accel; camera_velocity.z *= (1 - friction * 0.1); }
           
            if (int(space[c010]) != 0 || int(space[c011]) != 0 ){  camera_velocity.z = 0;  camera->position.z  -=.07;}
            else if (IsKeyDown(KEY_S) && !space[c010] && !space[c011]){    camera_velocity.z -= camera_accel; camera_velocity.z *= (1 - friction * 0.1); }


            if (int(space[c100]) != 1 || int(space[c101]) != 1 ){  camera_velocity.x  = 0;  camera->position.x -= .07;}
            else if (IsKeyDown(KEY_A) && space[c101]  && space[c100]  ) {    camera_velocity.x -= camera_accel; camera_velocity.x *= (1 - friction * 0.1); }


            if (int(space[c111]) != 0 || int(space[c110]) != 0 ){  camera_velocity.x  = 0;  camera->position.x  -= .07;}
            else if (IsKeyDown(KEY_D) && !space[c111] && !space[c110])  {    camera_velocity.x += camera_accel; camera_velocity.x *= (1 - friction * 0.1); }



				CameraMoveForward(camera, camera_velocity.z, moveInWorldPlane);
			CameraMoveRight(camera, camera_velocity.x, moveInWorldPlane);
			camera_velocity.x *= 0.95;
			camera_velocity.z *= 0.95;
			CameraMoveToTarget(camera, -GetMouseWheelMove());
			if (IsKeyPressed(KEY_G)) CameraMoveToTarget(camera, 2.0f);
			if (IsKeyPressed(KEY_Y)) CameraMoveToTarget(camera, -2.0f);

            
	 }
	

}

#define push_vertex(xo, yo, zo, nx, ny, nz, u, v) \
	mesh.vertices[3 * vertex_count + 0] = x + xo; \
	mesh.vertices[3 * vertex_count + 1] = y + yo; \
	mesh.vertices[3 * vertex_count + 2] = z + zo; \
	mesh.normals[3 * vertex_count + 0] = nx; \
	mesh.normals[3 * vertex_count + 1] = ny; \
	mesh.normals[3 * vertex_count + 2] = nz; \
	mesh.texcoords[2 * vertex_count + 0] = u; \
	mesh.texcoords[2 * vertex_count + 1] = v; \
	vertex_count++;

static int seed = 10000;
static int hash[] = { //the randomness part "so called specific hashbrown fucntiion":-) 
	208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
	185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
	9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
	70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
	203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
	164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
	228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
	232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
	193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
	101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
	135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
	114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
}; //2D RANDOM NUM

static int noise2(int x, int y) { //Perlin noise
	int tmp = hash[(y + seed) % 256]; 
	return hash[(tmp + x) % 256];
}

static float lin_inter(float x, float y, float s) { //linear interpolation 
	return x + s * (y - x);
}

static float smooth_inter(float x, float y, float s) { 
	return lin_inter(x, y, s * s * ( 3 - 2 * s ));
}

static float noise2d(float x, float y) { // perlin noise
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int);
	int t = noise2(x_int+1, y_int);
	int u = noise2(x_int, y_int+1);
	int v = noise2(x_int+1, y_int+1);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

static float perlin2d(float x, float y, float freq, int depth) {//perlin noise
	float xa = x * freq;
	float ya = y * freq;
	float amp = 1.0;
	float fin = 0;
	float div = 0.0;
	for (int i = 0; i < depth; i++) {
		div += 256 * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
	}
	return fin / div;
}





static void treemaker(int8_t* space, const int s, const int x, const int y,const int z ){ //new
	//min = 3, max = 7
	int height = (rand()%5 + 3);
	space[s * s * x + s*(y+height+1)  + z] = leaves_block;

	int leafheight = (y + height); 
	for(int i = -1; i < 2; i++){
		for(int j = -1; j<2; j++){
			if(((x+i)>=0 && (x+i)<200 ) && ((z+j)>=0 && (z+j)<200) &&space[s * s * (x+i) +s*leafheight+(z+j)] == air_block )
			space[s * s * (x+i) +s*leafheight+(z+j)] = leaves_block; //leaves placer
		}
	}

	for(int i = 0; i<height; i++) space[s * s * x + s*(y+i) + z] = wood_block;

}

static Mesh generate_mesh(void) {  //GENERATING ACTUAL BLOCKS
	
	Mesh mesh = {0};
	mesh.triangleCount = 12 * space_count;
	mesh.vertexCount = mesh.triangleCount * 3;
	mesh.vertices  = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));
	mesh.normals   = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));
	mesh.texcoords = (float *) MemAlloc(mesh.vertexCount * 2 * sizeof(float)); 

	for (int x = 0; x < s; x++) {
		
		for (int z = 0; z < s; z++) {
			const float f = perlin2d(x, z, 0.01, 20);
			const int height = f * 0; //change back to 50 later for terrain height
			const int divide = height / 2;
			for (int y = 0; y < height; y++) {
				if (y >= divide) space[s * s * x + s * y + z] = dirt_block;
				if (y < divide) space[s * s * x + s * y + z] = stone_block + (rand() % 2) * (rand() % 2);
			}
			space[s * s * x + s * height + z] = grass_block;

			if(rand()%100 == 3  && space[s * s * x + s * height + (z)] == grass_block){ 
			treemaker(space,s,x,height,z);

			}
		}
	}
	space[s * s * 50 + s * 50 + 4] = air_block; 
	space[s * s * 50 + s * 50 + 6] = grass_block;
	space[s * s * 50 + s * 50 + 8] = dirt_block;
	space[s * s * 50 + s * 50 + 10] = stone_block;
	space[s * s * 50 + s * 50 + 12] = granite_block;
	space[s * s * 50 + s * 50 + 14] = wood_block;
	space[s * s * 50 + s * 50 + 16] = leaves_block;
	space[s * s * 50 + s * 50 + 18] = water_block;
	space[s * s * 50 + s * 50 + 20] = moss_block;
	space[s * s * 50 + s * 50 + 22] = iron_ore_block;
	space[s * s * 50 + s * 50 + 24] = off_cell_block;
	space[s * s * 50 + s * 50 + 26] = on_cell_block;
	space[s * s * 50 + s * 50 + 28] = off_path_block;
	space[s * s * 50 + s * 50 + 30] = on_path_block;
	space[s * s * 50 + s * 50 + 32] = glass_block;
	space[s * s * 50 + s * 50 + 34] = wood_block;
    space[s * s * 50 + s * 50 + 36] = plank_block;
	space[s * s * 50 + s * 50 + 40] = flower;

	unsigned int vertex_count = 0;
	unsigned short front_x[256] 	= {1,0,3,4,5,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short front_y[256] 	= {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2};
	unsigned short back_x[256] 		= {1,0,3,4,5,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short back_y[256] 		= {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2};
	unsigned short up_x[256] 		= {2,0,3,4,0,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short up_y[256] 		= {0,0,0,0,1,0,0,1,1,1,1,1,1,1,2,2};
	unsigned short down_x[256] 		= {0,0,3,4,0,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short down_y[256] 		= {0,0,0,0,1,0,0,1,1,1,1,1,1,1,2,2};
	unsigned short left_x[256] 		= {1,0,3,4,5,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short left_y[256] 		= {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2};
	unsigned short right_x[256] 	= {1,0,3,4,5,6,7,2,3,4,5,6,7,1,0,1};
	unsigned short right_y[256] 	= {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2};


	for (int x = 0; x < s; x++) {
		for (int y = 0; y < s; y++) {
			for (int z = 0; z < s; z++) {
				int8_t block = space[s * s * x + s * y + z];
				if (not block) continue;
				block--; const float e = 1.0 / 8.0, _ = 0;
				if (not z or not space[s * s * (x) + s * (y) + (z - 1)]) {  // LEFT
					const float ut = e * left_x[block], vt = e * left_y[block];
					push_vertex(0,0,0, 0,0,0, ut+e,vt+e);
					push_vertex(0,1,0, 0,0,0, ut+e,vt+_);
					push_vertex(1,0,0, 0,0,0, ut+_,vt+e);
					push_vertex(1,1,0, 0,0,0, ut+_,vt+_);
					push_vertex(1,0,0, 0,0,0, ut+_,vt+e);
					push_vertex(0,1,0, 0,0,0, ut+e,vt+_);
				}

				if (z >= s - 1 or not space[s * s * (x) + s * (y) + (z + 1)]) { //RIGHT
					const float ut = e * right_x[block], vt = e * right_y[block];
					push_vertex(0,0,1, 0,0,0, ut+e,vt+e);
					push_vertex(1,0,1, 0,0,0, ut+_,vt+e);
					push_vertex(0,1,1, 0,0,0, ut+e,vt+_);
					push_vertex(1,1,1, 0,0,0, ut+_,vt+_);
					push_vertex(0,1,1, 0,0,0, ut+e,vt+_);
					push_vertex(1,0,1, 0,0,0, ut+_,vt+e);
				} 

				if (x >= s - 1 or not space[s * s * (x + 1) + s * (y) + (z)]) { // BACK
					const float ut = e * back_x[block], vt = e * back_y[block];
					push_vertex(1,1,1, 0,0,0, ut+e,vt+_); // back top right
					push_vertex(1,0,0, 0,0,0, ut+_,vt+e); // back bottom left
					push_vertex(1,1,0, 0,0,0, ut+_,vt+_); // back bottom right
					push_vertex(1,1,1, 0,0,0, ut+e,vt+_); // back top right
					push_vertex(1,0,1, 0,0,0, ut+e,vt+e); // back top left
					push_vertex(1,0,0, 0,0,0, ut+_,vt+e); // back bottom left
				}

				if (not x or not space[s * s * (x - 1) + s * (y) + (z)]) { // FRONT
					const float ut = e * front_x[block], vt = e * front_y[block];
					push_vertex(0,1,1, 0,0,0, ut+_,vt+_); //top right
					push_vertex(0,1,0, 0,0,0, ut+e,vt+_); //bottom right
					push_vertex(0,0,0, 0,0,0, ut+e,vt+e); //bottom left
					push_vertex(0,1,1, 0,0,0, ut+_,vt+_); //top right
					push_vertex(0,0,0, 0,0,0, ut+e,vt+e); //bottom left
					push_vertex(0,0,1, 0,0,0, ut+_,vt+e); //top left
				}

				if (not y or not space[s * s * (x) + s * (y - 1) + (z)]) { // DOWN
					const float ut = e * down_x[block], vt = e * down_y[block];
					push_vertex(1,0,1, 0,0,0, ut+_,vt+_);
					push_vertex(0,0,1, 0,0,0, ut+_,vt+e);
					push_vertex(1,0,0, 0,0,0, ut+e,vt+_);
					push_vertex(0,0,0, 0,0,0, ut+e,vt+e);
					push_vertex(1,0,0, 0,0,0, ut+e,vt+_);
					push_vertex(0,0,1, 0,0,0, ut+_,vt+e);
				}

				if (y >= s - 1 or not space[s * s * (x) + s * (y + 1) + (z)]) { // UP
					const float ut = e * up_x[block], vt = e * up_y[block];
					push_vertex(1,1,1, 0,0,0, ut+_,vt+_);
					push_vertex(1,1,0, 0,0,0, ut+_,vt+e);
					push_vertex(0,1,1, 0,0,0, ut+e,vt+_);
					push_vertex(0,1,0, 0,0,0, ut+e,vt+e);
					push_vertex(0,1,1, 0,0,0, ut+e,vt+_);
					push_vertex(1,1,0, 0,0,0, ut+_,vt+e);
				}
			}
		}
	}
	mesh.vertexCount = vertex_count;
	mesh.triangleCount = vertex_count / 3;
	UploadMesh(&mesh, false);
	return mesh;
}


int main(void) {
	srand(seed);
	space = (int8_t*) calloc(space_count, 1);
	InitWindow(screen_width, screen_height, "block game");
	Texture2D texture = LoadTexture("C:\\Users\\marwe\\Downloads\\Raylib-CPP-Starter-Template-for-VSCODE-main\\md-game\\Raylib-CPP-Starter-Template-for-VSCODE-main\\.vscode\\blocks.png");
	Camera camera = {0};
	camera.position = (Vector3){ 50.0f, 50.0f, 50.0f };
	camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 70.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	int cameraMode = CAMERA_FIRST_PERSON;
	DisableCursor(); SetTargetFPS(60);
	Mesh mesh = generate_mesh();
	Model model = LoadModelFromMesh(mesh);
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	while (true) {
		if (IsKeyPressed(KEY_ESCAPE)) break;
		if (IsKeyPressed(KEY_ONE)) ToggleFullscreen();
		if (IsKeyPressed(KEY_TWO)) cameraMode = CAMERA_FIRST_PERSON;
		if (IsKeyPressed(KEY_THREE)) cameraMode = CAMERA_THIRD_PERSON;
		if (IsKeyPressed(KEY_FOUR)) TakeScreenshot("screenshot0.png");
		if (IsKeyPressed(KEY_FIVE)) OpenURL("https://google.com");
		my_UpdateCamera(&camera, cameraMode);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);
		DrawModel(model, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
		if (cameraMode == CAMERA_THIRD_PERSON) {
			DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
			DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
		}
		EndMode3D();
		DrawText(TextFormat("Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 10, 15, 10, BLACK);
		DrawText(TextFormat("Velocity: (%06.3f, %06.3f, %06.3f)", camera_velocity.x, camera_velocity.y, camera_velocity.z), 10, 60, 10, BLACK);
		DrawText(TextFormat("Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 10, 30, 10, BLACK);
		DrawText(TextFormat("Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 10, 45, 10, BLACK);

		DrawFPS(100, 100);
		EndDrawing();
	}
	CloseWindow();
}