#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include "List.h"
#include "Byte.h"

#pragma warning(disable:4996)

List *NewList(int itemSize)
{
	List *list = (List *)malloc(sizeof(List));
	list->Capacity = LIST_INIT_CAPACITY;
	list->ItemSize = itemSize;
	list->Count = 0;
	list->MemCapacity = list->Capacity * list->ItemSize;
	list->Item = malloc(list->MemCapacity);
	list->Add = _ListAdd;
	list->Replace = _ListReplace;
	list->RemoveAt = _ListRemoveAt;
	list->Clear = _ListClear;
	list->Get = _ListGet;
	list->Dispose = _ListDispose;
	return list;
}

void _ListAdd(List *list, void *value)
{
	if (list->Capacity <= list->Count)
	{
		int newCapacity = list->Capacity * 2;
		int newMemCapacity = newCapacity * list->ItemSize;
		void *newItem = malloc(newMemCapacity);
		memcpy_s(newItem, newMemCapacity, list->Item, list->MemCapacity);
		free(list->Item);
		list->Item = newItem;
		list->Capacity = newCapacity;
		list->MemCapacity = newMemCapacity;
	}

	memcpy((byte *)(list->Item) + (list->Count * list->ItemSize), value, list->ItemSize);
	++(list->Count);
}

bool _ListReplace(List *list, int index, void *value)
{
	if (list->Count > index && 0 <= index)
	{
		memcpy((byte *)(list->Item) + (index * list->ItemSize), value, list->ItemSize);
		return true;
	}
	else
		return false;
}

bool _ListRemoveAt(List *list, int index)
{
	if (list->Count > index && 0 <= index)
	{
		byte *item = (byte *)(list->Item);
		int deletePos = index * list->ItemSize;
		memmove(item + deletePos, item + deletePos + list->ItemSize, list->MemCapacity - (deletePos + list->ItemSize));

		--(list->Count);
		return true;
	}
	else
		return false;
}

void _ListClear(List *list)
{
	list->Count = 0;
}

void *_ListGet(List *list, int index)
{
	if (list->Count > index && 0 <= index)
		return (byte *)(list->Item) + (index * list->ItemSize);
	else
		return NULL;
}

void _ListDispose(List *list)
{
	free(list->Item);
	free(list);
}