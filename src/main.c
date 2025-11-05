#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define WIDTH 400
#define HEIGHT 400
#define TITLE "Balls and their admirers"
#define BALL_COUNT 100
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 20
#define RADIUS_MIN 5

Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};

// Definition of Ball
// Ball stores state and other properties
// MY CODE START
typedef struct Ball {
  int posx, posy, velx, vely, radius;
  Color color;
  struct Ball
      *follows; // Pointer to the Ball struct that this Ball struct follows.
} Ball;
// MY CODE END

Ball balls[BALL_COUNT];

// Initializes a ball with random values
Ball *init_ball_random(Ball *p) {
  // Randomly initialize state and properties

  // MY CODE START
  // Set the x position to a random number in the range [0 ; WIDTH - 1].
  // Set the y position to a random number in the range [0 ; HEIGHT - 1].
  p->posx = rand() % WIDTH;
  p->posy = rand() % HEIGHT;

  // Set the x and y velocities to a random number
  // in the range [-VEL_MAX ; VEL_MAX].
  p->velx = -VEL_MAX + (rand() % (2 * VEL_MAX + 1));
  p->vely = -VEL_MAX + (rand() % (2 * VEL_MAX + 1));

  // Set the radius to a random number in the range [RADIUS_MIN ; RADIUS_MAX].
  p->radius = RADIUS_MIN + (rand() % (RADIUS_MAX - RADIUS_MIN + 1));

  // Set the color to a random color in the COLORS array.
  size_t colors_count = sizeof(COLORS) / sizeof(COLORS[0]);
  p->color = COLORS[rand() % colors_count];
  // MY CODE END

  // MY CODE START
  // Make the ball follow nothing temporarily, as its not necessary to
  // find a leader immediately.
  // Making a ball follow an uninitialized ball causes the program
  // to dereference uninitialized memory, causing problems.
  p->follows = nullptr;
  // MY CODE END

  return p;
}

// Initialize all `balls`
void init_balls_random() {
  // MY CODE START
  // Seed rand() with the current time.
  srand(time(NULL));

  // Make a pointer to the Ball struct with memory allocated for its size.
  Ball *ball_ptr = malloc(sizeof(Ball));

  // Loop through and randomly initialize all of the balls in the balls array.
  for (size_t i = 0; i < BALL_COUNT; i++) {
    ball_ptr = &balls[i];
    *ball_ptr = *init_ball_random(ball_ptr);

    // Keep finding new balls for balls[i] to follow
    // until it doesn't follow itself.
    while (ball_ptr == &balls[i]) {
      ball_ptr = &balls[rand() % BALL_COUNT];
    }
    // Make balls[i] follow the randomly generated ball (not balls[i]).
    balls[i].follows = ball_ptr;
  }
  // MY CODE END
}

Ball *draw_ball(Ball *p) {
  DrawCircle(p->posx, p->posy, p->radius, p->color);
  return p;
}

// Updates the positions of balls according to their velocities
Ball *update_pos(Ball *p) {
  p->posx = (WIDTH + p->posx + p->velx) %
            WIDTH; // `WIDTH +` because C uses truncated division
  p->posy = (HEIGHT + p->posy + p->vely) % HEIGHT;
  return p;
}

// Updates the velocity of a ball so that it follows the leading ball
Ball *update_vel_for_following(Ball *p) {
  int errx = p->follows->posx - p->posx;
  int erry = p->follows->posy - p->posy;
  p->velx = errx > 0 ? 1 : -1;
  p->vely = erry > 0 ? 1 : -1;
  return p;
}

// Update all elements
void update_elements() {
  for (size_t i = 0; i < _Countof balls; ++i) {
    draw_ball(update_pos(update_vel_for_following(&balls[i])));
  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  init_balls_random();

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    update_elements();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}