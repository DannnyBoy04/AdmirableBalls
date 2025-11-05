# Overview

This is a basic C program that uses raylib v5.5 and a struct type called Ball to generate 100 2D balls with a random position, velocity, radis, color and following a random other ball. It makes use of struct pointers in order to avoid passing the Ball struct by value, and the same logic is applied elswhere.
I have only written the parts wrapped by ``MY CODE START`` and ``MY CODE END``.

## Example output

A short screen recording is included in the GitHub repository.

## Flowchart

The flowchart and included mermaid code only represents the code that I have personally written.

# Files

## main.c

Explanations of the code blocks I have written:

### Ball struct

This is a structure defined type containing integer values for the ball's x & y positions, x & y velocity components and its radius. It has a color variable of the type Color defined in raylib, and contains a pointer called follows to another Ball struct.

### Inside ``init_ball_random()``

This function randomly initializes the properties in the Ball struct for the ball, which is passed to the function by reference.
I.e. it gives the ball a random position, velocity, radius, color and temporarily makes it follow nothing.
This is all done within the bounds defined at the top of ``main.c``.

### Inside ``init_balls_random()``

This function calls the ``init_ball_random()`` function a number of times equal to ``BALL_COUNT`` in order to initialize that amount of balls. It then makes each ball follow another ball other than itself.