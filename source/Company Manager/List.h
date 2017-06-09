#pragma once

#include <stdbool.h>

#define LIST_INIT_CAPACITY 2

typedef struct _List
{
	int Capacity;
	int MemCapacity;
	int ItemSize;
	int Count;
	void *Item;
	void(*Add)(struct _List *, void *);
	bool(*Replace)(struct _List *, int, void *);
	bool(*RemoveAt)(struct _List *, int);
	void(*Clear)(struct _List *);
	void*(*Get)(struct _List *, int);
	void(*Dispose)(struct _List *);
} List;

List *NewList(int);

void _ListAdd(List *, void *);
bool _ListReplace(List *, int, void *);
bool _ListRemoveAt(List *, int);
void _ListClear(List *);
void *_ListGet(List *, int);
void _ListDispose(List *);