#pragma once
#include "canvas.h"

typedef struct command Command;
struct command{
    char *str;
    size_t bufsize;
    Command *next;
};


typedef struct
{
    Command *begin;
    size_t bufsize; // [*] : この方が効率的ですね。一部の方から指摘ありました。
} History;


// enum for interpret_command results
typedef enum res{ EXIT, LINE, UNDO, SAVE, UNKNOWN, ERRNONINT, ERRLACKARGS, NOCOMMAND} Result;
// Result 型に応じて出力するメッセージを返す
char *strresult(Result res);

int max(const int a, const int b);
void draw_line(Canvas *c, const int x0, const int y0, const int x1, const int y1);
Result interpret_command(const char *command, History *his, Canvas *c);
void save_history(const char *filename, History *his);

// [*] list.c のpush_backと同じ
Command *push_command(History *his, const char *str);
