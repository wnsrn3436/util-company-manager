#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputExt.h"
#include "StringExt.h"

#pragma warning(disable:4996)

void WaitForInput()
{
	char input[INPUT_STRBUF];
	gets_s(input, INPUT_STRBUF);
}

int GetOnlyInteger()
{
	char input[INPUT_STRBUF];

	gets_s(input, INPUT_STRBUF);
	while (!IsOnlyInteger(input))
	{
		printf(INTEGER_ERROR);
		gets_s(input, INPUT_STRBUF);
	}

	return atoi(input);
}

char GetOnlyChar()
{
	char input[INPUT_STRBUF];

	gets_s(input, INPUT_STRBUF);
	while (strlen(input) != 1)
	{
		printf(CHAR_ERROR);
		gets_s(input, INPUT_STRBUF);
	}

	return input[0];
}

void GetOnlyUpper(char *text)
{
	char input[INPUT_STRBUF];

	gets_s(input, INPUT_STRBUF);
	while (!IsOnlyUpper(input))
	{
		printf(UPPER_ERROR);
		gets_s(input, INPUT_STRBUF);
	}

	strcpy(text, input);
}

void GetOnlyLower(char *text)
{
	char input[INPUT_STRBUF];

	gets_s(input, INPUT_STRBUF);
	while (!IsOnlyLower(input))
	{
		printf(LOWER_ERROR);
		gets_s(input, INPUT_STRBUF);
	}

	strcpy(text, input);
}

int GetLimitedInteger(int min, int max)
{
	int value = GetOnlyInteger();

	if (value < min || value > max)
	{
		printf(RANGE_ERROR);
		return GetLimitedInteger(min, max);
	}
	else
		return value;
}

char GetLimitedChar(char min, char max)
{
	int value = GetOnlyChar();

	if (value < min || value > max)
	{
		printf(RANGE_ERROR);
		return GetLimitedChar(min, max);
	}
	else
		return value;
}

void GetLimitedString(char *text, int minLen, int maxLen)
{
	char input[INPUT_STRBUF];

	gets_s(input, INPUT_STRBUF);
	while (strlen(input) < minLen || strlen(input) > maxLen)
	{
		printf(LENGTH_ERROR);
		gets_s(input, INPUT_STRBUF);
	}

	strcpy(text, input);
}