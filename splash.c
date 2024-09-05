#include "splash.h"
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int splash_iLen (int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}
char* splash_itoa(int i){
	uint8_t temp = splash_iLen(i);
	char* ret = malloc(temp--);
	//ret[temp--] = '\0';
	while(i){
		ret[temp--] = (i%10)+'0';
		i /= 10;
	}
	return ret;
}
void move_cursor_to_fn(int x, int y){
	sbuf_add(SPLASH_PREFIX"[", sizeof(SPLASH_PREFIX)); 
	uint32_t _splash_len_cur = splash_iLen(y); 
	char* _splash_str_cur = splash_itoa(y); 
	//puts(_splash_str_cur);
	sbuf_add(_splash_str_cur, _splash_len_cur); 
	free(_splash_str_cur);
	abAppendc(&_splash_buf, ';');
	_splash_str_cur = splash_itoa(x); 
	_splash_len_cur = splash_iLen(x); 
	sbuf_add(_splash_str_cur, _splash_len_cur); 
	free(_splash_str_cur); 
	abAppendc(&_splash_buf, 'H');

}
void abAppend(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);
  if (new == NULL) return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}
void abAppendc(struct abuf *ab, char c) {
  char *new = realloc(ab->b, ab->len + 1);
  if (new == NULL) return;
  new[ab->len] = c;
  ab->b = new;
  ab->len++;
}
void abAppendOneBefore(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);
  if (new == NULL || ab->len == 0) return;
  memmove(&new[ab->len-1], s, len);
  ab->b = new;
  ab->len += len;
}
void abInsert(struct abuf *ab, const char *s, int len, size_t pos){
	char* new = realloc(ab->b, ab->len + len);
	if(new == NULL) return;
	memmove(&new[pos+len], &new[pos], ab->len - pos);
	memcpy(&new[pos], s, len);
	ab->b = new;
	ab->len+=len;
}
void abRemove(struct abuf* ab, int len){
	ab->len -= len;
	char* new = realloc(ab->b, ab->len);
	if(new == NULL) return;
	ab->b = new;
}
void abFree(struct abuf *ab) {
	ab->len = 0;
	free(ab->b);
	ab->b=NULL;
}
size_t splash_ceil(long double num) {
    size_t inum = (size_t)num;
    if (num == (long double)inum) {
        return inum;
    }
    return inum + 1;
}




struct abuf _splash_buf;

void sbuf_redraw(){
	write(STDOUT_FILENO, _splash_buf.b, _splash_buf.len);
	abFree(&_splash_buf);
}

splash_color splash_hex_to_rgb(uint32_t hex)
{
  splash_color ret = {
	.r = (((hex >> 16) & 0xFF) / 255),
	.g = (((hex >> 8) & 0xFF) / 255),
	.b = ((hex & 0xFF) / 255)
  };
  return ret;
}
splash_color_f splash_hex_to_rgbf(uint32_t hex)
{
  splash_color_f ret = {
	.r = (((hex >> 16) & 0xFF) / 255.0),
	.g = (((hex >> 8) & 0xFF) / 255.0),
	.b = ((hex & 0xFF) / 255.0)
  };
  return ret;
}
uint32_t splash_rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
char* splash_getfile(char* filename){
	char * buffer = 0;
	long length;
	FILE * f = fopen (filename, "rb");
	
	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = malloc (length);
	  if (buffer)
	  {
	    fread (buffer, 1, length, f);
	  }
	  fclose (f);
	}
	return buffer;
}
struct termios orig_termios;
void disableRawMode() {
	puts(show_cursor stop_altscreen"\n");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	struct termios raw = orig_termios;
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
CONSOLE_SCREEN_BUFFER_INFO _splash_csbi;

#endif
#if defined __linux__ || __unix__
#include <sys/ioctl.h>
struct winsize _splash_winsize;
#endif
#ifdef SPLASH_NCURSES
#if defined __linux__ || __unix__
#include <curses.h>
uint32_t splash_term_bg(){
	chtype c = inch();
	C
}
unsigned int splash_max(){
	FILE *fp;
	char path[10];
	unsigned int ret = 0;
	/* Open the command for reading. */
  	fp = popen("tput colors", "r");
  	if (fp == NULL) {
  	  printf("Failed to run command\n" );
  	  exit(1);
  	}

  	/* Read the output a line at a time - output it. */
  	while (fgets(path, sizeof(path), fp) != NULL) {
  	  ret = atoi(path);
  	}

  	/* close */
  	pclose(fp);

	return ret;
}

#endif

#endif
