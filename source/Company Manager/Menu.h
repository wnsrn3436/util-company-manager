#pragma once

#include <stdbool.h>
#include "Dictionary.h"
#include "StringExt.h"

typedef struct
{
	void *Func;
} PackedFunc;

typedef struct _Menu
{
	String *Text;
	Dictionary *CommandMap;
	void (*SetText)(struct _Menu *, char *);
	char *(*GetText)(struct _Menu *);
	bool(*AddCommand)(struct _Menu *, char *, void *);
	bool (*RemoveCommand)(struct _Menu *, char *);
	void (*ClearCommand)(struct _Menu *);
	void *(*Command)(struct _Menu *, char *);
	void(*Dispose)(struct _Menu *);
} Menu;

Menu *NewMenu(char *);

void _MenuSetText(Menu *, char *);
char *_MenuGetText(Menu *);
bool _MenuAddCommand(Menu *, char *, void *);
bool _MenuRemoveCommand(Menu *, char *);
void _MenuClearCommand(Menu *);
void *_MenuCommand(Menu *, char *);
void _MenuDispose(Menu *);