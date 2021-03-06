#define WIDTH 640
#define HEIGHT 480

#define VIDEOWIDTH 320
#define VIDEOHEIGHT 240
#include <SDL/SDL.h>
extern "C" {
 struct ctx
{
    SDL_Surface *surf;
    SDL_mutex *mutex;
};

struct ctx ctx;

static void *lock(void *data, void **p_pixels);
static void unlock(void *data, void *id, void *const *p_pixels);
static void display(void *data, void *id);
void Display();
void CleanUP();
};
