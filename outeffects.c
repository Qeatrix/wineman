#include <stdio.h>
#include "outeffects.h"
#include "ansi_color_codes.h"

#define MAX_STRING_SIZE 1024

void print_color_close(enum OutColors action, char *string) {
  char color_default[MAX_STRING_SIZE] = "\e[0m";
  
  switch(action) {
    case BLACK: {
      char buffer[MAX_STRING_SIZE];
      char color_black[MAX_STRING_SIZE] = "\x1b[32m";
      snprintf(buffer, sizeof(buffer), "%s%s%s", color_black, string, color_default);
      
      printf("%s", buffer);
      break;
    }
    case RED: {
      char buffer[MAX_STRING_SIZE];
      char color_red[MAX_STRING_SIZE] = "\x1b[31m";
      snprintf(buffer, sizeof(buffer), "%s%s%s", color_red, string, color_default);
      
      printf("%s", buffer);
      break;
    }
    case GREEN: {
      char buffer[MAX_STRING_SIZE];
      char color_green[MAX_STRING_SIZE] = "\x1b[32m";
      snprintf(buffer, sizeof(buffer), "%s%s%s", color_green, string, color_default);
      
      printf("%s", buffer);
      break;
    }
    case YELLOW: {
      char buffer[MAX_STRING_SIZE];
      char color_yellow[MAX_STRING_SIZE] = "\e[0;33m";
      snprintf(buffer, sizeof(buffer), "%s%s%s", YEL, string, COLOR_RESET);
      
      printf("%s", buffer);
      break;
    }
    case DEFAULT: {
      break;
    }
  }
}

void print_color(enum OutColors action) {
  switch(action) {
    case DEFAULT: {
      printf("\x1b[0m");
      break;
    }
    case BLACK: {
      printf("BLACK");
      break;
    }
    case RED: {
      printf("\x1b[31m");
      break;
    }
    case GREEN: {
      printf("\x1b[32m");
      break;
    }
    case YELLOW: {
      printf(YEL);
      break;
    }
  }
}

void print_mode(enum Modes action) {
  switch(action) {
    case PREFIX_CREATE: {
      print_color(GREEN);
      printf("╭─────────────────╮\n");
      printf("│ Prefix Creation │\n");
      printf("╰─────────────────╯\n\n");
      print_color(DEFAULT);

      break;
    }
    case PREFIX_DELETE: {    
      print_color(RED);
      printf("╭────────────────╮\n");
      printf("│ Prefix Removal │\n");
      printf("╰────────────────╯\n\n");
      print_color(DEFAULT);

      break;
    }
    case PREFIX_NOTFOUND: {
      print_color(YELLOW);
      printf("╭─────────────────────────╮\n");
      printf("│ No Saved Prefixes Found │\n");
      printf("╰─────────────────────────╯\n\n");
      print_color(DEFAULT);
    }
  }
}
