#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "StringExt.h"

String *NewString(char *text)
{
	int length = (int)strlen(text);
	char *newText = (char *)malloc(sizeof(char) * (length + 1));
	strcpy_s(newText, length + 1, text);

	String *str = (String *)malloc(sizeof(String));
	str->Length = length;
	str->Text = newText;
	str->Get = _StringGet;
	str->Dispose = _StringDispose;

	return str;
}

char *_StringGet(String *str)
{
	return str->Text;
}

void _StringDispose(String *str)
{
	free(str->Text);
	free(str);
}

bool IsOnlyInteger(char *text)
{
	int i = (text[0] == '+' || text[0] == '-') ? 1 : 0;
	int len = (int)strlen(text);
	bool result = true;
	for (; i < len; i++)
	{
		if (text[i] < '0' || text[i] > '9')
		{
			result = false;
			break;
		}
	}
	return result;
}

bool IsOnlyUpper(char *text)
{
	int len = (int)strlen(text);
	bool result = true;
	for (int i = 0; i < len; i++)
	{
		if (text[i] < 'A' || text[i] > 'Z')
		{
			result = false;
			break;
		}
	}
	return result;
}

bool IsOnlyLower(char *text)
{
	int len = (int)strlen(text);
	bool result = true;
	for (int i = 0; i < len; i++)
	{
		if (text[i] < 'a' || text[i] > 'z')
		{
			result = false;
			break;
		}
	}
	return result;
}