#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "Menu.h"
#include "Dictionary.h"
#include "StringExt.h"

Menu *NewMenu(char *text)
{
	Menu *menu = (Menu *)malloc(sizeof(Menu));
	menu->Text = NewString(text);
	menu->CommandMap = NewDictionary(sizeof(PackedFunc));
	menu->SetText = _MenuSetText;
	menu->GetText = _MenuGetText;
	menu->AddCommand = _MenuAddCommand;
	menu->RemoveCommand = _MenuRemoveCommand;
	menu->ClearCommand = _MenuClearCommand;
	menu->Command = _MenuCommand;
	menu->Dispose = _MenuDispose;
	return menu;
}

void _MenuSetText(Menu *menu, char *text)
{
	menu->Text->Dispose(menu->Text);
	menu->Text = NewString(text);
}

char *_MenuGetText(Menu *menu)
{
	return menu->Text->Get(menu->Text);
}

bool _MenuAddCommand(Menu *menu, char *command, void *func)
{
	PackedFunc pack;
	pack.Func = func;
	return menu->CommandMap->Add(menu->CommandMap, command, &pack);
}

bool _MenuRemoveCommand(Menu *menu, char *command)
{
	return menu->CommandMap->Remove(menu->CommandMap, command);
}

void _MenuClearCommand(Menu *menu)
{
	menu->CommandMap->Clear(menu->CommandMap);
}

void *_MenuCommand(Menu *menu, char *command)
{
	PackedFunc *pack = (PackedFunc *)(menu->CommandMap->GetValue(menu->CommandMap, command));
	if (pack != NULL)
		return pack->Func;
	else
		return NULL;
}

void _MenuDispose(Menu *menu)
{
	menu->Text->Dispose(menu->Text);
	menu->CommandMap->Dispose(menu->CommandMap);
	free(menu);
}