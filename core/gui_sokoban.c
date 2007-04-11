#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_mbox.h"
#include "gui_sokoban.h"

//-------------------------------------------------------------------
#define FIELD_WIDTH             15
#define FIELD_HEIGHT            15

#define SCREEN_COLOR            0xDB
#define WALL_COLOR_1            COLOR_GREY
#define WALL_COLOR_2            COLOR_BLACK
#define BOX_COLOR_1             0x26
#define BOX_COLOR_2             COLOR_BLACK
#define BOX_COLOR_3             0x66
#define PLACE_COLOR_1           0x99
#define PLACE_COLOR_2           COLOR_BLACK
#define PLAYER_COLOR_1          COLOR_GREEN
#define PLAYER_COLOR_2          COLOR_BLACK

#define MARKER_WALL             '#'
#define MARKER_BOX              '$'
#define MARKER_PLACE            '.'
#define MARKER_BOX_PLACE        '*'
#define MARKER_PLAYER           '@'
#define MARKER_PLAYER_PLACE     '+'
#define MARKER_EMPTY            ' '

//-------------------------------------------------------------------
#include "gui_sokoban_levels.h"
#define NUM_LEVELS (sizeof(fields)/sizeof(fields[0]))

static int need_redraw;
static int  moves;
static char field[FIELD_HEIGHT][FIELD_WIDTH];

static int cell_size;
static int xPl, yPl;

//-------------------------------------------------------------------
static void sokoban_set_level(int lvl) {
    int x=0, y, w=0, h=0;
    const char *p=fields[lvl];

    // determine dimensions
    while (*p) {
      if (*p=='|') {
          ++h;
          if (x>w) w=x;
          x=0;
      } else {
          ++x;
      }
      ++p;
    }
    if (x>w) w=x;

    // clear field
    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            field[y][x]=MARKER_EMPTY;
    
    // place maze at the center
    p=fields[lvl];
    for (y=(FIELD_HEIGHT-h)/2; y<FIELD_HEIGHT; ++y, ++p) {
        for (x=(FIELD_WIDTH-w)/2; x<FIELD_WIDTH && *p && *p!='|'; ++x, ++p) {
            field[y][x]=*p;
            if (field[y][x] == MARKER_PLAYER) {
              xPl = x; yPl = y;
            }
        }
        if (!*p) break;
    }

    conf.sokoban_level = lvl;
    moves = 0;
}

//-------------------------------------------------------------------
static int sokoban_finished() {
    int x, y;

    for (y=0; y<FIELD_HEIGHT; ++y)
        for (x=0; x<FIELD_WIDTH; ++x)
            if (field[y][x]==MARKER_BOX) 
                return 0;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_next_level() {
    if (++conf.sokoban_level >= NUM_LEVELS) conf.sokoban_level = 0;
    sokoban_set_level(conf.sokoban_level);
    need_redraw = 1;
}

//-------------------------------------------------------------------
static int sokoban_move(int dx, int dy) {
    switch (field[yPl+dy][xPl+dx]) {
        case MARKER_WALL:
            return 0;
            break;
        case MARKER_BOX:
        case MARKER_BOX_PLACE:
            if (field[yPl+dy*2][xPl+dx*2]==MARKER_WALL || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX || field[yPl+dy*2][xPl+dx*2]==MARKER_BOX_PLACE)
                return 0;
            break;
        case MARKER_PLACE:
        case MARKER_EMPTY:
            break;
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLAYER_PLACE)?MARKER_PLACE:MARKER_EMPTY;
    xPl+=dx; yPl+=dy;
    if (field[yPl][xPl]==MARKER_BOX || field[yPl][xPl]==MARKER_BOX_PLACE) {
        field[yPl][xPl]=(field[yPl][xPl]==MARKER_BOX_PLACE)?MARKER_PLACE:MARKER_EMPTY;
        field[yPl+dy][xPl+dx]=(field[yPl+dy][xPl+dx]==MARKER_PLACE)?MARKER_BOX_PLACE:MARKER_BOX;
    }
    field[yPl][xPl]=(field[yPl][xPl]==MARKER_PLACE)?MARKER_PLAYER_PLACE:MARKER_PLAYER;
    return 1;
}

//-------------------------------------------------------------------
static void sokoban_draw_box(int x, int y, color cl) {
    draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+2, y*cell_size, x*cell_size+2, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+cell_size-1-2, y*cell_size, x*cell_size+cell_size-1-2, y*cell_size+cell_size-1, cl);
    draw_line(x*cell_size+2, y*cell_size+2, x*cell_size+cell_size-1-2, y*cell_size+2, cl);
    draw_line(x*cell_size+2, y*cell_size+cell_size-1-2, x*cell_size+cell_size-1-2, y*cell_size+cell_size-1-2, cl);
}

//-------------------------------------------------------------------
void gui_sokoban_init() {
    cell_size = screen_height/FIELD_HEIGHT;
    sokoban_set_level(conf.sokoban_level);
    need_redraw = 1;
}

//-------------------------------------------------------------------
void gui_sokoban_kbd_process() {
    switch (kbd_get_clicked_key()) {
        case KEY_UP:
            moves+=sokoban_move(0, -1);
            need_redraw = 1;
            break;
        case KEY_DOWN:
            moves+=sokoban_move(0, +1);
            need_redraw = 1;
            break;
        case KEY_LEFT:
            moves+=sokoban_move(-1, 0);
            need_redraw = 1;
            break;
        case KEY_RIGHT:
            moves+=sokoban_move(+1, 0);
            need_redraw = 1;
            break;
        case KEY_SET:
            if (moves == 0) {
                sokoban_next_level();
            }
            break;
        case KEY_ERASE:
            sokoban_set_level(conf.sokoban_level);
            need_redraw = 1;
            break;
        case KEY_DISPLAY:
            gui_mbox_init("*** About ***", "SOKOBAN\n(c) GrAnd, 2007", MBOX_TEXT_CENTER, NULL);
            need_redraw = 1;
            break;
    }
}

//-------------------------------------------------------------------
void gui_sokoban_draw() {
    int y, x;
    static char str[16];

    if (need_redraw) {
        need_redraw = 0;
        for (y=0; y<FIELD_HEIGHT; ++y) {
            for (x=0; x<FIELD_WIDTH; ++x) {
                switch (field[y][x]) {
                    case MARKER_WALL:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(WALL_COLOR_1, WALL_COLOR_2));
                        break;
                    case MARKER_BOX:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_1, BOX_COLOR_2));
                        break;
                    case MARKER_PLACE:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_rect(x*cell_size+4, y*cell_size+4, x*cell_size+cell_size-1-4, y*cell_size+cell_size-1-4, MAKE_COLOR(PLACE_COLOR_1, PLACE_COLOR_2));
                        break;
                    case MARKER_BOX_PLACE:
                        sokoban_draw_box(x, y, MAKE_COLOR(BOX_COLOR_3, BOX_COLOR_2));
                        break;
                    case MARKER_PLAYER:
                    case MARKER_PLAYER_PLACE:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        draw_filled_ellipse(x*cell_size+(cell_size>>1)-1, y*cell_size+(cell_size>>1)-1, (cell_size>>1)-3, (cell_size>>1)-3, MAKE_COLOR(PLAYER_COLOR_1, PLAYER_COLOR_2));
                        break;
                    case MARKER_EMPTY:
                    default:
                        draw_filled_rect(x*cell_size, y*cell_size, x*cell_size+cell_size-1, y*cell_size+cell_size-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));
                        break;
                }
            }
        }

        draw_line(cell_size*FIELD_WIDTH, 0, cell_size*FIELD_WIDTH, screen_height-1, COLOR_WHITE);
        draw_line(cell_size*FIELD_WIDTH+1, 0, cell_size*FIELD_WIDTH+1, screen_height-1, COLOR_BLACK);

        draw_filled_rect(cell_size*FIELD_WIDTH+2, 0, screen_width-1, 7, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        sprintf(str, "  Level: %-6d", conf.sokoban_level+1);
        draw_string(cell_size*FIELD_WIDTH+2, 8, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));
        sprintf(str, "  Moves: %-6d", moves);
        draw_string(cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT, str, MAKE_COLOR(SCREEN_COLOR, COLOR_WHITE));

        draw_filled_rect(cell_size*FIELD_WIDTH+2, 8+FONT_HEIGHT*2, screen_width-1, screen_height-1, MAKE_COLOR(SCREEN_COLOR, SCREEN_COLOR));

        if (sokoban_finished()) {
            gui_mbox_init("*** Finished ***", "YES!\n  You did it!  ", MBOX_TEXT_CENTER, NULL);
            sokoban_next_level();
        }
    }
}

