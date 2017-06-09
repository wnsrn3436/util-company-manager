#pragma once

#include <stdbool.h>

typedef struct _String
{
	char *Text;
	int Length;
	char *(*Get)(struct _String *);
	void(*Dispose)(struct _String *);
} String;

String *NewString(char *);

char *_StringGet(String *);
void _StringDispose(String *);

bool IsOnlyInteger(char *);
bool IsOnlyUpper(char *);
bool IsOnlyLower(char *);