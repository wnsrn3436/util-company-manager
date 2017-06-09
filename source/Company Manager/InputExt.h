#pragma once

#define INPUT_STRBUF 256
#define INTEGER_ERROR "> 입력된 값이 숫자로 구성되지 않았습니다. 다시 입력해주세요 : "
#define CHAR_ERROR "> 입력된 값이 문자 한 개가 아닙니다. 다시 입력해주세요 : "
#define UPPER_ERROR "> 입력된 값이 대문자로 구성되지 않았습니다. 다시 입력해주세요 : "
#define LOWER_ERROR "> 입력된 값이 소문자로 구성되지 않았습니다. 다시 입력해주세요 : "
#define RANGE_ERROR "> 입력된 값의 범위가 너무 크거나 작습니다. 다시 입력해주세요 : "
#define LENGTH_ERROR "> 입력된 문자열이 너무 길거나 짧습니다. 다시 입력해주세요 : "

void WaitForInput();
int GetOnlyInteger();
char GetOnlyChar();
void GetOnlyUpper(char *);
void GetOnlyLower(char *);
int GetLimitedInteger(int, int);
char GetLimitedChar(char, char);
void GetLimitedString(char *, int, int);