#include "tools.h"

const int WINDOW_WIDTH = 320 * 2;
const int WINDOW_HEIGHT = 240 * 2;

void scc(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void *scp(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void P2d_alloc(P2d_vector *vector) {
    vector->size = vector->capacity = 0;

    vector->array = malloc(sizeof(Point2D) * (WINDOW_HEIGHT + WINDOW_WIDTH));
    vector->capacity = WINDOW_HEIGHT + WINDOW_WIDTH;
    return;
}

void P2d_push_back(P2d_vector *vector, Point2D point) {
    if (vector->size + 1 > vector->capacity) {
        // Point2D *new_vec = malloc((vector->capacity * 1.5) * sizeof(Point2D));
        // vector->capacity *= 1.5;
        // for (int i = 0; i < vector->size; ++i) {
        //     new_vec[i] = vector->array[i];
        // }
        // free(vector->array);
        // vector->array = new_vec;
        vector->array = realloc(vector->array, vector->capacity * 1.5);
        vector->capacity *= 1.5;
    }
    vector->array[vector->size + 1] = point;
    vector->size += 1;
}

void P2d_clear(P2d_vector *vector) {
    if (vector->array == NULL || vector == NULL) {
        return;
    }
    free(vector->array);
    vector->array = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

void rotate(Vec3D *vec, float x, float y, float z) {
    float rad = 0;

    rad = x;
    vec->y = cos(rad) * vec->y - sin(rad) * vec->z;
    vec->z = sin(rad) * vec->y + cos(rad) * vec->z;

    rad = y;
    vec->x = cos(rad) * vec->x + sin(rad) * vec->z;
    vec->z = -sin(rad) * vec->x + cos(rad) * vec->z;

    rad = z;
    vec->x = cos(rad) * vec->x - sin(rad) * vec->y;
    vec->y = sin(rad) * vec->x + cos(rad) * vec->y;
}

void line(P2d_vector *points, float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float lenth = sqrt(dx * dx + dy * dy);
    float angle = atan2(dy, dx);

    for (float i = 0; i < lenth; ++i) {
        P2d_push_back(points, (Point2D){.x = x1 + cos(angle) * i,
                                        .y = y1 + sin(angle) * i});
    }
}

int update(SDL_Renderer **renderer, Vec3D (*shape)[8]) {
    // compute the rotation

    return 0;
}
