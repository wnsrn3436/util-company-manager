#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>
#include <string.h>
#include "Dictionary.h"
#include "List.h"
#include "StringExt.h"

KeyValuePair NewKeyValuePair(char *key, void *value, int valueSize)
{
	KeyValuePair pair;
	pair.Key = NewString(key);
	pair.Value = malloc(valueSize);
	pair.Dispose = _KeyValuePairDispose;

	memcpy_s(pair.Value, valueSize, value, valueSize);
	return pair;
}

void _KeyValuePairDispose(KeyValuePair *pair)
{
	pair->Key->Dispose(pair->Key);
	free(pair->Value);
}

Dictionary *NewDictionary(int valueSize)
{
	Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
	dict->Count = 0;
	dict->ValueSize = valueSize;
	dict->KeyValue = NewList(sizeof(KeyValuePair));
	dict->Add = _DictionaryAdd;
	dict->Remove = _DictionaryRemove;
	dict->Clear = _DictionaryClear;
	dict->GetValue = _DictionaryGetValue;
	dict->Dispose = _DictionaryDispose;
	return dict;
}

bool _DictionaryAdd(Dictionary *dict, char *key, void *value)
{
	if (_DictionaryGetValue(dict, key) == NULL)
	{
		KeyValuePair pair = NewKeyValuePair(key, value, dict->ValueSize);
		dict->KeyValue->Add(dict->KeyValue, &pair);
		++(dict->Count);
		return true;
	}
	else
		return false;
}

bool _DictionaryRemove(Dictionary *dict, char *key)
{
	for (int i = 0; i < dict->Count; i++)
	{
		KeyValuePair *pair = (KeyValuePair *)(dict->KeyValue->Get(dict->KeyValue, i));
		if (strcmp(pair->Key->Get(pair->Key), key) == 0)
		{
			pair->Dispose(pair);
			dict->KeyValue->RemoveAt(dict->KeyValue, i);
			--(dict->Count);
			return true;
		}
	}
	return false;
}

void _DictionaryClear(Dictionary *dict)
{
	for (int i = 0; i < dict->Count; i++)
	{
		KeyValuePair *pair = (KeyValuePair *)(dict->KeyValue->Get(dict->KeyValue, i));
		pair->Dispose(pair);
	}
	dict->KeyValue->Clear(dict->KeyValue);
	dict->Count = 0;
}

void *_DictionaryGetValue(Dictionary *dict, char *key)
{
	for (int i = 0; i < dict->Count; i++)
	{
		KeyValuePair *pair = (KeyValuePair *)(dict->KeyValue->Get(dict->KeyValue, i));
		if (strcmp(pair->Key->Get(pair->Key), key) == 0)
			return pair->Value;
	}
	return NULL;
}

void _DictionaryDispose(Dictionary *dict)
{
	_DictionaryClear(dict);
	dict->KeyValue->Dispose(dict->KeyValue);
	free(dict);
}