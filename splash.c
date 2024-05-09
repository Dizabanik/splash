#include "splash.h"
#include <stdint.h>





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
