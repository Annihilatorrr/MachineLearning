#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "functions.h"

int main()
{
	char str[100];
	int stepforcesar, keyforxor;
	scanf("%s", str);
	scanf("%d", &stepforcesar);
	mutableEncoderCesar(str, stepforcesar);
	printf("%s \n", str);

	mutableDecoderCesar(str, stepforcesar);
	printf("%s \n", str);

	mutableToUpper(str);
	printf("%s \n", str);

	mutableToLower(str);
	printf("%s \n", str);

	if (isNumber(str))
	{
		printf(" this is number \n");
	}
	else
	{
		printf(" this is not number \n");
	}

	if (isLetter(str))
	{
		printf(" there are only letters \n");
	}
	else
	{
		printf(" there are not only letters \n");
	}

	mutableFilter(str);
	printf("%s", str);

	return 0;
}
