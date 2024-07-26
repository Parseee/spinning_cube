#pragma once

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// rendering
typedef struct {
    float x;
    float y;
} Point2D;

typedef struct {
    Point2D *array;
    int size;
    int capacity;
} P2d_vector;

typedef struct {
    float x;
    float y;
    float z;
} Vec3D;

typedef struct {
    int from;
    int to;
} Connection;

extern void scc(int code);
extern void* scp(void* ptr);

void P2d_alloc(P2d_vector *vector);
void P2d_push_back(P2d_vector *vector, Point2D point);
void P2d_clear(P2d_vector *vector);

void line(P2d_vector *points, float x1, float y1, float x2, float y2);
int update(SDL_Renderer **renderer, Vec3D (*shape)[8]);

void rotate(Vec3D *vec, float x, float y, float z);