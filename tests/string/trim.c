#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include <clamda/private/string.h>

void
basic_trim_front_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "TTest";
	clamda_string_trim_front(str, 'T');
	assert_string_equal("est", str);

	clamda_string_trim_front(str, 'e');
	assert_string_equal("st", str);

	clamda_string_trim_front(str, 's');
	assert_string_equal("t", str);
}

void
basic_trim_tail_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "Testt";
	clamda_string_trim_tail(str, 't');
	assert_string_equal("Tes", str);

	clamda_string_trim_tail(str, 's');
	assert_string_equal("Te", str);

	clamda_string_trim_tail(str, 'e');
	assert_string_equal("T", str);
}

void
basic_trim_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "test";
	clamda_string_trim(str, 't');
	assert_string_equal("es", str);

	clamda_string_trim(str, 's');
	assert_string_equal("e", str);
}

void
nothing_to_trim_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "Test";
	clamda_string_trim_front(str, 'e');
	assert_string_equal("Test", str);

	clamda_string_trim_tail(str, 'e');
	assert_string_equal("Test", str);
}

void
trim_empty_string_does_nothing_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "";
	clamda_string_trim_front(str, ' ');
	assert_string_equal("", str);

	clamda_string_trim_tail(str, ' ');
	assert_string_equal("", str);
}

void
trim_last_character_returns_empty_string_test(void** state)
{
	(void)state;

	char str[BUFSIZ] = "jjj";
	clamda_string_trim_front(str, 'j');
	assert_string_equal("", str);

	strcpy(str, "jjj");
	clamda_string_trim_tail(str, 'j');
	assert_string_equal("", str);
}

int main(void)
{
	const struct CMUnitTest string_trim_test[] = {
		cmocka_unit_test(basic_trim_front_test),
		cmocka_unit_test(basic_trim_tail_test),
		cmocka_unit_test(basic_trim_test),
		cmocka_unit_test(nothing_to_trim_test),
		cmocka_unit_test(trim_empty_string_does_nothing_test),
		cmocka_unit_test(trim_last_character_returns_empty_string_test),
	};

	return cmocka_run_group_tests(string_trim_test, NULL, NULL);
}

