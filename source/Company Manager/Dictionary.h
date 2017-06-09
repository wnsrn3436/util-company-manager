#pragma once

#include <stdbool.h>
#include "List.h"
#include "StringExt.h"

typedef struct _KeyValuePair
{
	String *Key;
	void *Value;
	void(*Dispose)(struct _KeyValuePair *);
} KeyValuePair;

KeyValuePair NewKeyValuePair(char *, void *, int);

void _KeyValuePairDispose(KeyValuePair *);

typedef struct _Dictionary
{
	int Count;
	int ValueSize;
	List *KeyValue;
	bool(*Add)(struct _Dictionary *, char *, void *);
	bool(*Remove)(struct _Dictionary *, char *);
	void(*Clear)(struct _Dictionary *);
	void *(*GetValue)(struct _Dictionary *, char *);
	void(*Dispose)(struct _Dictionary *);
} Dictionary;

Dictionary *NewDictionary(int);

bool _DictionaryAdd(Dictionary *, char *, void *);
bool _DictionaryRemove(Dictionary *, char *);
void _DictionaryClear(Dictionary *);
void *_DictionaryGetValue(Dictionary *, char *);
void _DictionaryDispose(Dictionary *);