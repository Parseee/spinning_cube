#include "tools.h"
#include "shapes.h"

int main(void) {
    scc(SDL_Init(SDL_INIT_EVERYTHING));

    SDL_Window* window = scp(SDL_CreateWindow("Dicer", SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH, WINDOW_HEIGHT, 0));

    SDL_Renderer* renderer =
        scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    // Vec3D shape[8] = {(Vec3D){100, 100, 100}, (Vec3D){200, 100, 100},
    //                   (Vec3D){200, 200, 100}, (Vec3D){100, 200, 100},

    //                   (Vec3D){100, 100, 200}, (Vec3D){200, 100, 200},
    //                   (Vec3D){200, 200, 200}, (Vec3D){100, 200, 200}};

    // Vec3D *(shape)[8] = &cube;
    // Vec3D(*shape_ptr)[8] = &cube;
    Vec3D shape[8];
    for (int i = 0; i < 8; ++i) {
        shape[i] = cube[i];
    }

    Connection cons[12] = {
        (Connection){0, 4}, (Connection){1, 5},
        (Connection){2, 6}, (Connection){3, 7},

        (Connection){0, 1}, (Connection){1, 2},
        (Connection){2, 3}, (Connection){3, 0},

        (Connection){4, 5}, (Connection){5, 6},
        (Connection){6, 7}, (Connection){7, 4},
    };

    bool quit = false;
    while (!quit) {
        SDL_Event event = {0};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;
            }
        }

        // renderer crashes when forwarded to another file
        // renderer should be forwarded as **renderer for some reason
        // update(renderer, shape_ptr);
        Vec3D centroid = (Vec3D){.x = 0, .y = 0, .z = 0};
        for (int i = 0; i < 8; ++i) {
            centroid.x += shape[i].x;
            centroid.y += shape[i].y;
            centroid.z += shape[i].z;
        }
        centroid.x /= 8;
        centroid.y /= 8;
        centroid.z /= 8;

        for (int i = 0; i < 8; ++i) {
            shape[i].x -= centroid.x;
            shape[i].y -= centroid.y;
            shape[i].z -= centroid.z;
            rotate(&shape[i], 0.002, 0.001, 0.004);
            shape[i].x += centroid.x;
            shape[i].y += centroid.y;
            shape[i].z += centroid.z;
        }

        // clear window
        scc(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0));
        scc(SDL_RenderClear(renderer));

        // actually draw
        scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));

        // render
        P2d_vector points;
        P2d_alloc(&points);

        // for (int i = 0; i < 8; ++i) {
        //     P2d_push_back(&points, (Point2D){shape[i].x, shape[i].y});
        // }

        for (int i = 0; i < 12; ++i) {
            line(&points, shape[cons[i].from].x, shape[cons[i].from].y,
                 shape[cons[i].to].x, shape[cons[i].to].y);
        }

        for (int i = 0; i < points.size; ++i) {
            SDL_RenderDrawPointF(renderer, points.array[i].x,
                                 points.array[i].y);
        }

        P2d_clear(&points);

        SDL_RenderPresent(renderer);
        // SDL_Delay(30);
    }

    SDL_Quit();
    return 0;
}