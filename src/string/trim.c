#include <string.h>

#include <clamda/private/string.h>

void
clamda_string_trim_front(char* str, char c)
{
	size_t i = 0;
	for (; i < strlen(str); ++i) {
		if (str[i] != c) {
			break;
		}
	}

	memmove(&str[0], &str[i], strlen(str) - i + 1);
}

void
clamda_string_trim_tail(char* str, char c)
{
	size_t i = strlen(str) - 1;
	for (; i >= 0; --i) {
		if (str[i] != c) {
			break;
		}
	}

	str[++i] = '\0';
}

void
clamda_string_trim(char* str, char c)
{
	clamda_string_trim_front(str, c);
	clamda_string_trim_tail(str, c);
}

