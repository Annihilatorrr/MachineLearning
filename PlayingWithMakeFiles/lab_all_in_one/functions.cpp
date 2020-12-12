#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "functions.h"

void mutableToUpper(char* text)
{
	int i;
	int k = strlen(text);
	for (i = 0; i < k; i++)
	{
		text[i] = toupper(text[i]);
	}
}

void mutableToLower(char* text)
{
	int i;
	int k = strlen(text);
	for (i = 0; i < k; i++)
	{
		text[i] = tolower(text[i]);
	}
}

void mutableFilter(char* text)
{
	int len = strlen(text);
	int delta = 0;
	bool shiftMode = false;

	for (int k = 0; k < len - delta; k++)
	{
		if ((text[k] < 48) || ((text[k] > 57) && (text[k] < 65)) || ((text[k] > 90) && (text[k] < 97)) || (text[k] > 122) || (shiftMode == true))
		{
			if ((text[k] < 48) || ((text[k] > 57) && (text[k] < 65)) || ((text[k] > 90) && (text[k] < 97)) || (text[k] > 122))
			{
				delta++;
			}
			shiftMode = true;
			text[k] = text[k + delta];
		}
	}
	text[len - delta] = '\0';
}

void mutableDeleteSpace(char* text)
{
	int len = strlen(text);
	int delta = 0;
	bool shiftMode = false;

	for (int k = 0; k < len - delta; k++)
	{
		if ((text[k] == 32) || (shiftMode == true))
		{
			if (text[k] == 32)
			{
				delta++;
			}
			shiftMode = true;
			text[k] = text[k + delta];
		}
	}
	text[len - delta] = '\0';
}

bool isNumber(char* text)
{
	int i = strlen(text);
	for (int k = 0; k < i; k++)
	{
		if ((text[k] < 48) || (text[k] > 57))
		{
			return false;
		}
	}
	return true;
}

bool isLetter(char* text)
{
	int i = strlen(text);
	for (int k = 0; k < i; k++)
	{
		if ((text[k] < 65) || ((text[k] > 90) && (text[k] < 97)) || (text[k] > 122))
		{
			return false;
		}
	}
	return true;
}

void mutableEncoderCesar(char* text, int step)
{
	for (unsigned int i = 0; i < strlen(text); i++)
	{
		text[i] = text[i] + step;
	}
}

void mutableDecoderCesar(char* text, int step)
{
	for (unsigned int i = 0; i < strlen(text); i++)
	{
		text[i] = text[i] - step;
	}
}

void mutableEncoderXor(char* text, char* key)
{
	int len = strlen(key);
	for (unsigned int i = 0; text[i]; i++)
	{
		int keyindex = i % len;
		text[i] ^= key[keyindex];
	}
}

void mutableDecoderXor(char* text, char* key)
{
	int len = strlen(key);
	for (unsigned int i = 0; text[i]; i++)
	{
		int keyindex = i % len;
		text[i] ^= key[keyindex];
	}
}
