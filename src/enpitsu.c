#include <raylib.h>
#include <stdio.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

#define ENPITSU_TITLE_LEN (1024)
static char enpitsu_title[ENPITSU_TITLE_LEN];

typedef struct {
    uint8_t r, g, b, a;
} Enpitsu_Color;

// Color defines copied from RayLib.
#define ENPITSU_LIGHTGRAY  (Enpitsu_Color){ 200, 200, 200, 255 }   // Light Gray
#define ENPITSU_GRAY       (Enpitsu_Color){ 130, 130, 130, 255 }   // Gray
#define ENPITSU_DARKGRAY   (Enpitsu_Color){ 80, 80, 80, 255 }      // Dark Gray
#define ENPITSU_YELLOW     (Enpitsu_Color){ 253, 249, 0, 255 }     // Yellow
#define ENPITSU_GOLD       (Enpitsu_Color){ 255, 203, 0, 255 }     // Gold
#define ENPITSU_ORANGE     (Enpitsu_Color){ 255, 161, 0, 255 }     // Orange
#define ENPITSU_PINK       (Enpitsu_Color){ 255, 109, 194, 255 }   // Pink
#define ENPITSU_RED        (Enpitsu_Color){ 230, 41, 55, 255 }     // Red
#define ENPITSU_MAROON     (Enpitsu_Color){ 190, 33, 55, 255 }     // Maroon
#define ENPITSU_GREEN      (Enpitsu_Color){ 0, 228, 48, 255 }      // Green
#define ENPITSU_LIME       (Enpitsu_Color){ 0, 158, 47, 255 }      // Lime
#define ENPITSU_DARKGREEN  (Enpitsu_Color){ 0, 117, 44, 255 }      // Dark Green
#define ENPITSU_SKYBLUE    (Enpitsu_Color){ 102, 191, 255, 255 }   // Sky Blue
#define ENPITSU_BLUE       (Enpitsu_Color){ 0, 121, 241, 255 }     // Blue
#define ENPITSU_DARKBLUE   (Enpitsu_Color){ 0, 82, 172, 255 }      // Dark Blue
#define ENPITSU_PURPLE     (Enpitsu_Color){ 200, 122, 255, 255 }   // Purple
#define ENPITSU_VIOLET     (Enpitsu_Color){ 135, 60, 190, 255 }    // Violet
#define ENPITSU_DARKPURPLE (Enpitsu_Color){ 112, 31, 126, 255 }    // Dark Purple
#define ENPITSU_BEIGE      (Enpitsu_Color){ 211, 176, 131, 255 }   // Beige
#define ENPITSU_BROWN      (Enpitsu_Color){ 127, 106, 79, 255 }    // Brown
#define ENPITSU_DARKBROWN  (Enpitsu_Color){ 76, 63, 47, 255 }      // Dark Brown

#define ENPITSU_WHITE      (Enpitsu_Color){ 255, 255, 255, 255 }   // White
#define ENPITSU_BLACK      (Enpitsu_Color){ 0, 0, 0, 255 }         // Black
#define ENPITSU_BLANK      (Enpitsu_Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define ENPITSU_MAGENTA    (Enpitsu_Color){ 255, 0, 255, 255 }     // Magenta
#define ENPITSU_RAYWHITE   (Enpitsu_Color){ 245, 245, 245, 255 }   // My own White (raylib logo)

typedef struct {
    float x, y;
} Enpitsu_Vector2;

static Enpitsu_Vector2 enpitsu_pencil;
#define ENPITSU_PENCIL_DEFAULT_COLOR ENPITSU_WHITE
static Enpitsu_Color enpitsu_pencil_color = ENPITSU_PENCIL_DEFAULT_COLOR;
static Enpitsu_Color enpitsu_bg_color;
static bool enpitsu_pencil_down;

// NOTE: To disable raylib logging
static void dummy_log(int msgType, const char *text, va_list args) { (void)msgType; (void)args; (void)text; return; }

void enpitsu_init_window(int width, int height, const char* title) {
    stbsp_sprintf(enpitsu_title, "Enpitsu | %s", title);
    SetTraceLogCallback(dummy_log);
    InitWindow(width, height, enpitsu_title);
}

bool enpitsu_window_should_close(void) {
    return WindowShouldClose();
}

// NOTE: Could just reinterpret as Color using pointer magic...
static Color enpitsu_color_to_raylib_color(Enpitsu_Color color) {
    return (Color) {color.r, color.g, color.b, color.a};
}

void enpitsu_pre_draw(void) {
    BeginDrawing();
    ClearBackground(enpitsu_color_to_raylib_color(enpitsu_bg_color));
    enpitsu_pencil.x = 0; enpitsu_pencil.y = 0;
    enpitsu_pencil_color = ENPITSU_PENCIL_DEFAULT_COLOR;
}

void enpitsu_post_draw(void) {
    EndDrawing();
}

void enpitsu_up(void) {
    enpitsu_pencil_down = false;
}

void enpitsu_down(void) {
    enpitsu_pencil_down = true;
}

void enpitsu_color(Enpitsu_Color color) {
    enpitsu_pencil_color = color;
}

void enpitsu_move(int dx, int dy) {
    int px = enpitsu_pencil.x; int py = enpitsu_pencil.y;
    enpitsu_pencil.x += dx; enpitsu_pencil.y += dy;
    int nx = enpitsu_pencil.x; int ny = enpitsu_pencil.y;

    if (enpitsu_pencil_down) {
        DrawLine(px, py, nx, ny, enpitsu_color_to_raylib_color(enpitsu_pencil_color));
    }
}

void enpitsu_close_window(void) {
    CloseWindow();
}

int main(void) {
    enpitsu_init_window(800, 600, "Test");

    while (!enpitsu_window_should_close()) {
        enpitsu_pre_draw();

        enpitsu_down();
        enpitsu_color(ENPITSU_RED);
        enpitsu_move(100, 100);
        enpitsu_move(100, 0);
        enpitsu_color(ENPITSU_YELLOW);
        enpitsu_move(0, 100);
        enpitsu_move(100, 0);
        enpitsu_move(0, 100);
        /* log_info("enpitsu_points_count: %s", enpitsu_points_count ? "true" : "false"); */

        enpitsu_post_draw();
    }
    enpitsu_close_window();
    return 0;
}
