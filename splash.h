#ifndef SPLASH_H
#define SPLASH_H
#include <stdint.h>
#include <stdlib.h>

#define SPLASH_fprintf fprintf
#define SPLASH_fflush fflush

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define SPLASH_PREFIX "\033"
#define SPLASH_PREFIX_CHAR '\033'
#include <windows.h>
extern CONSOLE_SCREEN_BUFFER_INFO _splash_csbi;
/* Example usage: 
 *	#include <windows.h>
 *	//...
 *	
 *	splash_size size;
 *	splash_getsize((&size));
 *	printf("SizeX: %d\n", size.x);
 *	printf("SizeY: %d\n", size.y);
 *
*/
#define splash_getsize(size_obj) { GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_splash_csbi); size_obj->x = _splash_csbi.srWindow.Right - _splash_csbi.srWindow.Left + 1; size_obj->y = _splash_csbi.srWindow.Bottom - _splash_csbi.srWindow.Top + 1;
#endif
#if defined __linux__ || __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#define SPLASH_PREFIX "\x1b"
#define SPLASH_PREFIX_CHAR '\x1b'
extern struct winsize _splash_winsize;
/* Example usage: 
 *	#include <sys/ioctl.h>
 *	#include <unistd.h>
 *	//...
 *	
 *	splash_size size;
 *	splash_getsize((&size));
 *	printf("SizeX: %d\n", size.x);
 *	printf("SizeY: %d\n", size.y);
 *
*/
#define splash_getsize(size_obj) { ioctl(STDOUT_FILENO, TIOCGWINSZ, &_splash_winsize); size_obj->x = _splash_winsize.ws_col; size_obj->y = _splash_winsize.ws_row; }
#define CTRL_KEYPRESS(k) ((k)  & 0x1f)
#endif
#define color24(r,g,b) SPLASH_PREFIX"[38;2;" #r ";" #g ";" #b "m"
#define color8(n) SPLASH_PREFIX"[38;5;" #n "m"
#define color3_4(n) SPLASH_PREFIX"[" #n "m"
#define bg24(r,g,b) SPLASH_PREFIX"[48;2;" #r ";" #g ";" #b "m"
#define bg8(n) SPLASH_PREFIX"[48;5;" #n "m"
#define bg3_4(n) color3_4(n)
#define color24_var(r,g,b) SPLASH_PREFIX"[38;2;" r ";" g ";" b "m"
#define color8_var(n) SPLASH_PREFIX"[38;5;" n "m"
#define color3_4_var(n) SPLASH_PREFIX"[" n "m"
#define bg24_var(r,g,b) SPLASH_PREFIX"[48;2;" r ";" g ";" b "m"
#define bg8_var(n) SPLASH_PREFIX"[48;5;" n "m"
#define bg3_4_var(n) color3_4_var(n)
#define color0 SPLASH_PREFIX"[0m"

#define colorize(str, col) color0 col str color0

#define SPLASH_COLOR_BLACK "30"
#define SPLASH_COLOR_RED "31"
#define SPLASH_COLOR_GREEN "32"
#define SPLASH_COLOR_YELLOW "33"
#define SPLASH_COLOR_BLUE "34"
#define SPLASH_COLOR_MAGENTA "35"
#define SPLASH_COLOR_CYAN "36"
#define SPLASH_COLOR_WHITE "37"

#define SPLASH_BRIGHT(x) x+70
#define SPLASH_BG(x) x+10

#define SPLASH_BOLD SPLASH_PREFIX"[1m"
#define SPLASH_DIM SPLASH_PREFIX"[2m"
#define SPLASH_ITALIC SPLASH_PREFIX"[3m"
#define SPLASH_UNDERLINE SPLASH_PREFIX"[4m"
#define SPLASH_BLINKING SPLASH_PREFIX"[5m"
#define SPLASH_STRIKETHROUGH SPLASH_PREFIX"[9m"

#define SPLASH_BOLD_DISABLE SPLASH_PREFIX"[22m"
#define SPLASH_DIM_DISABLE SPLASH_PREFIX"[22m"
#define SPLASH_ITALIC_DISABLE SPLASH_PREFIX"[23m"
#define SPLASH_UNDERLINE_DISABLE SPLASH_PREFIX"[24m"

#define SPLASH_UNDERLINE_V052 SPLASH_PREFIX"[4:1m"
#define SPLASH_UNDERLINE_V052_DISABLE SPLASH_PREFIX"[4:0m"

#define SPLASH_DOUBLE_UNDERLINE SPLASH_PREFIX"[21m"
#define SPLASH_DOUBLE_UNDERLINE_DISABLE SPLASH_PREFIX"[24m"
#define SPLASH_DOUBLE_UNDERLINE_2 SPLASH_PREFIX"[4:2m"
#define SPLASH_DOUBLE_UNDERLINE_2_DISABLE SPLASH_PREFIX"[4:0m"

#define SPLASH_CURLY_UNDERLINE SPLASH_PREFIX"[4:3m"
#define SPLASH_CURLY_UNDERLINE_DISABLE SPLASH_PREFIX"[4:0m"

#define SPLASH_DOTTED_UNDERLINE SPLASH_PREFIX"[4:4m"
#define SPLASH_DOTTED_UNDERLINE_DISABLE SPLASH_PREFIX"[4:0m"

#define SPLASH_DASHED_UNDERLINE SPLASH_PREFIX"[4:5m"
#define SPLASH_DASHED_UNDERLINE_DISABLE SPLASH_PREFIX"[4:0m"

#define SPLASH_BLINKING_DISABLE SPLASH_PREFIX"[25m"

#define SPLASH_REVERSE SPLASH_PREFIX"[7m"
#define SPLASH_REVERSE_DISABLE SPLASH_PREFIX"[27m"

#define SPLASH_INVISIBLE SPLASH_PREFIX"[8m"
#define SPLASH_INVISIBLE_DISABLE SPLASH_PREFIX"[28m"

#define SPLASH_STRIKETHROUGH_DISABLE SPLASH_PREFIX"[29m"

#define SPLASH_OVERLINE SPLASH_PREFIX"[53m"
#define SPLASH_OVERLINE_DISABLE SPLASH_PREFIX"[55m"

#define SPLASH_COLOR_DISABLE SPLASH_PREFIX"[39m"
#define SPLASH_BG_DISABLE SPLASH_PREFIX"[49m"

// FIRST YOU SHOULD ENABLE UNDERLINE
#define color8_underline(n) SPLASH_PREFIX"[58;5;" #n "m"
#define SPLASH_COLOR_UNDERLINE_DISABLE SPLASH_PREFIX"[59m"

// FIRST YOU SHOULD ENABLE UNDERLINE
#define color24_underline(r,g,b) SPLASH_PREFIX"[58;2;" #r ";" #g ";" #b "m"

typedef struct splash_color {
	uint8_t r,g,b;
} splash_color;

typedef struct splash_color_f {
	double r,g,b;
} splash_color_f;

typedef struct splash_size {
	size_t x;
	size_t y;
} splash_size;
#define splash_color_to_rgb(x) x->r, x->g, x->b

splash_color splash_hex_to_rgb(uint32_t hex);
splash_color_f splash_hex_to_rgbf(uint32_t hex);
uint32_t splash_rgb_to_hex(uint8_t r, uint8_t g, uint8_t b);

#ifdef SPLASH_NCURSES

unsigned int splash_max();

#endif

char* splash_getfile(char* filename);

#define back_line_start "\r"
// Clear whole line
#define clear_line SPLASH_PREFIX"[2K"
// Clear line to the left of the cursor
#define clear_line_left SPLASH_PREFIX"[1K"
// Clear line to the right of the cursor
#define clear_line_right SPLASH_PREFIX"[0K"

#define clear_screen_right SPLASH_PREFIX"[0J"
#define clear_screen_left SPLASH_PREFIX"[1J"
#define clear_screen SPLASH_PREFIX"[2J"
#define start_altscreen SPLASH_PREFIX"[?1049h"
#define stop_altscreen SPLASH_PREFIX"[?1049l\n"
#define to_homepos SPLASH_PREFIX"[H"
#define hide_cursor SPLASH_PREFIX"[?25l"
#define show_cursor SPLASH_PREFIX"[?25h"
#define stdio_move_cursor_to(stream, x, y) fprintf(stream, SPLASH_PREFIX"[%d;%dH", y, x)

int splash_iLen (int n);
char* splash_itoa(int i);
#define move_cursor_to(x, y) { sbuf_add(SPLASH_PREFIX"[", sizeof(SPLASH_PREFIX)); uint32_t _splash_len_cur = splash_iLen(y); char* _splash_str_cur = splash_itoa(y); sbuf_add(_splash_str_cur, _splash_len_cur); free(_splash_str_cur); abAppendc(&_splash_buf, ';'); _splash_str_cur = splash_itoa(x); _splash_len_cur = splash_iLen(x); sbuf_add(_splash_str_cur, _splash_len_cur); free(_splash_str_cur); sbuf_addc('H'); }
void move_cursor_to_fn(int x, int y);
#define mvaddch(x, y, ch) move_cursor_to_fn(x, y); sbuf_addc(ch);
#define mvaddch_nfn(x, y, ch) move_cursor_to(x, y); sbuf_addc(ch);

#define mvadd(x, y, str, len) move_cursor_to_fn(x, y); sbuf_add(str, len);
#define mvadd_nfn(x, y, str, len) move_cursor_to(x, y); sbuf_add(str, len);

// FIRST ARG IS Y, SECOND IS X


// ...
#define move_cursor_to_str SPLASH_PREFIX"[%d;%dH" 
#define move_cursor_up(n) SPLASH_PREFIX"[" #n "A"
#define move_cursor_up_str SPLASH_PREFIX"[%dA"
#define move_cursor_down(n) SPLASH_PREFIX"[" #n "B"
#define move_cursor_down_str SPLASH_PREFIX"[%dB"
#define move_cursor_right(n) SPLASH_PREFIX"[" #n "C"
#define move_cursor_right_str SPLASH_PREFIX"[%dD"
#define move_cursor_left(n) SPLASH_PREFIX"[" #n "D"
#define move_cursor_left_str SPLASH_PREFIX"[%dD"
#define move_cursor_up_one SPLASH_PREFIX"M"

#define rewrite_line(stream, ...) { SPLASH_fprintf(stream, clear_line __VA_ARGS__); SPLASH_fflush(stream); }


#define ABUF_INIT {NULL, 0}
typedef struct abuf {
  char *b;
  int len;
} abuf;

extern struct abuf _splash_buf;
#define sbuf_init _splash_buf = (struct abuf)ABUF_INIT;
// Length is without \0 character
#define sbuf_add(str, len) abAppend(&_splash_buf, str, len);
#define sbuf_addc(ch) abAppendc(&_splash_buf, ch);
void sbuf_redraw();
#define sbuf_free abFree(&_splash_buf);

void disableRawMode(); 
void enableRawMode();

void abAppend(struct abuf *ab, const char *s, int len);
void abAppendc(struct abuf *ab, char c); 
void abAppendOneBefore(struct abuf *ab, const char *s, int len);
void abInsert(struct abuf *ab, const char *s, int len, size_t pos);
void abRemove(struct abuf* ab, int len);
void abFree(struct abuf *ab);
size_t splash_ceil(long double num); 

typedef struct splash_element {
	abuf text;
	void (*update_ptr)(abuf*);
} splash_element;
typedef struct {
	splash_size size;
} splash_pager;

#define SPLASH_POSITION_TOP 0
#define SPLASH_POSITION_BOTTOM 1
// Color #494d64
#define SPLASH_STATUSBAR_COLOR bg24(73, 77, 100)
typedef struct {
	uint8_t position;
	uint8_t paddingFromPos;
	splash_element** elements;
	uint16_t elementsNum;
	abuf text;
} splash_statusbar;
typedef struct {
	uint8_t top : 1;
	uint8_t bottom : 1;
	uint8_t left : 1;
	uint8_t right: 1;
	uint8_t center: 1;
	uint8_t info: 3;
} splash_align;
typedef struct {
	abuf* rows;
	size_t numRows;
	size_t max_width;
	splash_align align;
} splash_table_column;
typedef struct {
	splash_size size;
	splash_table_column* cols;
	size_t numCols;
} splash_table;
typedef struct {
	abuf* cols;
	size_t* max_widths;
	splash_align* aligns;
} splash_table_row;
typedef struct {
	splash_size size;
	splash_table_row* rows;
	size_t numCols;
	size_t numRows;
} splash_table_rowed;
#endif
