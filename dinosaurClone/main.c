#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX_OBSTACLES 2;
typedef struct obstacles{
  Vector2 position;
  Vector2 size;
  Color color;
  Rectangle hitbox;
  bool collision;
}obstacles ;
typedef struct player{
  Vector2 position;
  float speed;
  bool canJump;
  float velocityY;
  bool isGrounded;
}player;
void jump(struct player* man,float jumpForce,float gravity){
  man->velocityY = jumpForce;
  man->isGrounded = false;
}
void isGrounded(struct player* man,int floor){
  if(man->position.y > floor){
    man->isGrounded = false;
  }else {
    man->isGrounded = true;
    man->canJump = 1;
  }
}
void updatePhysics(struct player* man,int floor,float gravity){
  if (!man->isGrounded) {
    man->velocityY += gravity;
    man->position.y -= man->velocityY;
  }
  if (man->position.y >= floor ) {
    man->position.y = floor;
    man->velocityY = 0;
    man->isGrounded = true;
  }else {
    man->isGrounded = false;
  }
}
Vector2 generateRandomLocation(float min,float max,float spawnArea,int posY){
  Vector2 randomLocation;
  randomLocation.x = GetRandomValue( min, max);
  randomLocation.x+=spawnArea;
  randomLocation.y = posY;
  return randomLocation;
}
void spawnObstacle(obstacles* obstacleStorage,int* amount,float min,float max,float spawnArea,int posY){
  // i need to spawn it in a random location, maybe make another function that generates a random x value within 
  // the necessary spawn area
  Vector2 randomLocation;
  Rectangle hitboxNew;
  for (int i = *amount; i<2; i++) {
    randomLocation = generateRandomLocation(min,max,spawnArea,posY);
    obstacles new;  
    new.position = randomLocation;
    new.hitbox.x = new.position.x;
    new.hitbox.y = new.position.y;
    new.collision = false;
    obstacleStorage[i] = new;
    (*amount)++;
  }
}
void drawObstacles(obstacles* obstacleStorage, int amount,float speed,int posY,Texture2D lightPost){
  for (int i = 0; i<amount; i++) {
    obstacleStorage[i].hitbox.width = lightPost.width - 47;
    obstacleStorage[i].hitbox.height = lightPost.height;
    // for each lightpost drawn we need to draw the rectangle as well(its hitbox)
    //DrawRectangleRec(obstacleStorage[i].hitbox, BLUE);
    DrawTextureEx(lightPost, obstacleStorage[i].position,0.0f , 1.0f, WHITE);
  }
}
void updateObjects(int obstacleCount,obstacles* obstacleStorage,float locationX){
  if (obstacleCount > 0) {
    for (int i = 0; i<obstacleCount; i++) {
     obstacleStorage[i].position.x += locationX;
     obstacleStorage[i].hitbox.x += locationX;
    }
  }
}
void checkObstacles(obstacles* obstacleStorage,int* amount,float min,float max,float spawnArea,int posY){
    for (int i = 0; i<*amount; i++) {
      if (obstacleStorage[i].position.x <= -40) {
        obstacleStorage[i].position = generateRandomLocation(min, max, spawnArea,posY);
      }
      obstacleStorage[i].hitbox.x = obstacleStorage[i].position.x + 23;
    }
}
void drawCollisionsRec(obstacles* obstacleStorage,int amount,Rectangle* collisionRectangles){
  for (int i = 0; i<amount; i++) {
    if (obstacleStorage[i].collision) {
      DrawRectangleRec(collisionRectangles[i], PURPLE);
    }
  }
}
int main(void)
{
  InitWindow(800, 800, "Dinosaur Game");
  InitAudioDevice();
  // below are text that appears within game
  char gameOver[10] = "Game Over";
  char pressR[19] = "Press R to Restart";
  char pressSpace[21] = "Press SPACE to Start";
  int pressSpaceLength = MeasureText(pressSpace, 50);
  int gameOverLength = MeasureText(gameOver, 40);
  int pressRLength = MeasureText(pressR, 40);
  // textures and sounds
  Texture2D man = LoadTexture("resources/manUpdated.png"); 
  Texture2D background = LoadTexture("resources/updatedBackground.png");
  Texture2D lightPost = LoadTexture("resources/lightPost.png");
  Sound jumpSoundWav = LoadSound("resources/jumpSound.wav");
  Sound deathSound = LoadSound("resources/deathSound.wav");
  // game states
  int gameOverScreen = 0;
  int startState = 1;
  // pos of objects within game
  int windowWidth = GetScreenWidth();
  int windowHeight = GetScreenHeight();
  int textureWidth = background.width;
  int textureHeight = background.height;
  int posX = (windowWidth - textureWidth) /2;
  int posY = (windowHeight - textureHeight) /2;
  int manHeight = man.height;
  int manWidth = man.width;
  int manPosX = (windowWidth - manWidth) /2;
  int manPosY = (windowHeight - manHeight) /2;
  // game loop
  // scrolling values for background
  Vector2 manPos = {manPosX,manPosY};
  float scrolling = 0.0f;
  float spriteScrolling = 850.0f;
  Rectangle manHitBox = {manPosX+5,manPosY,man.width - 15,man.height};
  // check collision
  bool collision = false;
  player manStruct = {manPos,0.0f,true,0.0f,true};
  // velocity in y direction given by jump force
  float jumpForce = 20;
  float gravity = -0.8f;
  // beginning of trying to spawn multiple objects
  // bounds of random num generator
  float minDistance = 200;
  float maxDistance = 500;
  float spawnArea = 840;
  // define obstacles and amount of hitboxes
  obstacles lightPosts[2];
  Rectangle collisionRectObstacles[2];
  int obstacleCount = 0;
  // create a way to spawn multiple objects
  // create default font
  Font font;
  // values for drawing word at specifieced vector locations
  int centerX = (windowWidth - gameOverLength) /2;
  int centerY = (windowHeight - 280)/2;
  int centerXPressR = (windowWidth - pressRLength)/2;
  int centerXPressSpace = (windowWidth - pressSpaceLength)/2;
  Vector2 gameOverPos = {centerX,centerY};
  Vector2 pressRPos = {centerXPressR,centerY + 40};
  Vector2 pressSpacePos = {centerXPressSpace,centerY-100};
  // set fps to 60
  SetTargetFPS(60);
  // game loop
  while(!WindowShouldClose()){
    if (startState && IsKeyPressed(KEY_SPACE)) {
      startState = 0;
    }
    if (!startState) {
      if (IsKeyPressed(KEY_R) && gameOverScreen) {
       if (!manStruct.isGrounded) {
         manStruct.velocityY = 0;
         manStruct.position.y = manPosY;
       }
       for (int i = 0; i<obstacleCount; i++) {
         lightPosts[i].position.x = -51;
       }
       gameOverScreen = 0;
      }
      if (obstacleCount < 2) {
       spawnObstacle(lightPosts, &obstacleCount,minDistance,maxDistance,spawnArea,manPosY);
      }
    if (!gameOverScreen) {
     if (IsKeyPressed(KEY_SPACE)) {
       if (manStruct.isGrounded == true) {
         jump(&manStruct,jumpForce,gravity);
         PlaySound(jumpSoundWav);
       }
     }
     updatePhysics(&manStruct, manPosY, gravity);
     manHitBox.y = manStruct.position.y;
     scrolling -= 4.0f;
     checkObstacles(lightPosts,&obstacleCount,minDistance,maxDistance,spawnArea,manPosY);
     if (scrolling <= -(background.width)) {
       scrolling = 0;
     }
     for (int i = 0; i<obstacleCount; i++) {
       collision = CheckCollisionRecs(manHitBox, lightPosts[i].hitbox);
       if (collision) {
         collisionRectObstacles[i] = GetCollisionRec(manHitBox, lightPosts[i].hitbox);
         lightPosts[i].collision = true;
         gameOverScreen = 1;
         PlaySound(deathSound);
       }else {
         lightPosts[i].collision = false;
       }
     }
      if(!gameOverScreen){
       updateObjects(obstacleCount,lightPosts,-4.0f);
       }
      } 

    }
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTextureEx(background, (Vector2){scrolling,posY}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(background, (Vector2){background.width + scrolling,posY}, 0.0f, 1.0f, WHITE);
    if (gameOverScreen) {
      DrawTextEx(font, "Game Over", gameOverPos, 40, 1.0, BLACK);
      DrawTextEx(font, pressR, pressRPos, 40, 1.0, RED);
    }
    if (startState) {
      DrawTextEx(font, pressSpace, pressSpacePos, 50, 1.0f, BLACK);
    }
    drawObstacles(lightPosts, obstacleCount,spriteScrolling,manPosY,lightPost);
    DrawTextureEx(man, manStruct.position, 0, 1, WHITE);
    EndDrawing();
  }
  UnloadTexture(man);
  UnloadTexture(background);
  UnloadTexture(lightPost);
  UnloadSound(jumpSoundWav);
  UnloadSound(deathSound);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
