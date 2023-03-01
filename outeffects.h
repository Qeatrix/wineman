#ifndef OUTEFFECTS_H
#define OUTEFFECTS_H

enum OutColors { DEFAULT, BLACK, RED, GREEN, YELLOW };
enum Modes { PREFIX_CREATE, PREFIX_DELETE };

void print_color(enum OutColors action);
void print_mode(enum Modes action);

#endif
