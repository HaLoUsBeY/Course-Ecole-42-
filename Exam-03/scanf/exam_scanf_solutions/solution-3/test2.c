#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>

int scan_int(FILE *f, va_list ap)
{
	int c = fgetc(f);

	if (c == EOF)
	{
		if (ferror(f))
			return -1;
		return 0;
	}

	int sign = 1;
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
	}
	else
		ungetc(c, f);

	int value = 0;
	int digit_read = 0;
	while ((c = fgetc(f)) != EOF)
	{
		if (isdigit(c))
		{
			value = value * 10 + (c - '0');
			digit_read++;
		}
		else
		{
			ungetc(c, f);
			break;
		}
	}
	if (ferror(f))
		return -1;
		
	if (digit_read == 0)
		return 0;

	int *num_ptr = va_arg(ap, int *);
	*num_ptr = value * sign;
	return 1;
}



int main(void)
{	
    int value = 0;
	int digit_read = 0;

    char *c = "";

    while (*c)
	{
	    value = value * 10 + (*c - '0');
		c++;
	}


    printf ("Value: %d\n", value);

    return 0;
}
