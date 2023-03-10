#ifndef OUTEFFECTS_H
#define OUTEFFECTS_H

enum OutColors { DEFAULT, BLACK, RED, GREEN, YELLOW };
enum Modes { PREFIX_CREATE, PREFIX_DELETE, PREFIX_NOTFOUND };

void print_color_close(enum OutColors action, char *string);
void print_color(enum OutColors action);
void print_mode(enum Modes action);

#endif
