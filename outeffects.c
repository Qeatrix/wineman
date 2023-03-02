#include <stdio.h>
#include "outeffects.h"

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
      printf("\x1b[33m");
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
