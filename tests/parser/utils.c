#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include <clamda/clamda.h>
#include <clamda/private/parser.h>

enum clamda_line_type
example_element_advance_line(struct clamda_parser* p)
{
	p->pos_line += 1;

	// Line definitions are extracted from C data file
	if (p->pos_line <= 2) {
		return CLAMDA_LINE_NAME;
	} else if (p->pos_line <= 4) {
		return CLAMDA_LINE_WEIGHT;
	} else if (p->pos_line <= 6) {
		p->nlev = 3;
		return CLAMDA_LINE_NLEV;
	} else if (p->pos_line <= 10) {
		return CLAMDA_LINE_ENLEV;
	} else if (p->pos_line <= 12) {
		p->nlin = 3;
		return CLAMDA_LINE_NLIN;
	} else if (p->pos_line <= 16) {
		return CLAMDA_LINE_LINE;
	} else if (p->pos_line <= 18) {
		p->npart = 6;
		return CLAMDA_LINE_NPART;
	} else if (p->pos_line <= 20) {
		p->colparts |= CLAMDA_HI_FLAG;
		p->cur_colpart_flag = CLAMDA_HI_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 22) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_HI_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 24) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 26) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 30) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else if (p->pos_line <= 32) {
		p->colparts |= CLAMDA_ELECTRONS_FLAG;
		p->cur_colpart_flag = CLAMDA_ELECTRONS_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 34) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_ELECTRONS_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 36) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 38) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 42) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else if (p->pos_line <= 44) {
		p->colparts |= CLAMDA_HII_FLAG;
		p->cur_colpart_flag = CLAMDA_HII_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 46) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_HII_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 48) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 50) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 54) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else if (p->pos_line <= 56) {
		p->colparts |= CLAMDA_HELIUM_FLAG;
		p->cur_colpart_flag = CLAMDA_HELIUM_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 58) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_HELIUM_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 60) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 62) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 66) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else if (p->pos_line <= 68) {
		p->colparts |= CLAMDA_PARA_H2_FLAG;
		p->cur_colpart_flag = CLAMDA_PARA_H2_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 70) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_PARA_H2_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 72) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 74) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 78) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else if (p->pos_line <= 80) {
		p->colparts |= CLAMDA_ORTHO_H2_FLAG;
		p->cur_colpart_flag = CLAMDA_ORTHO_H2_FLAG;
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= 82) {
		p->ncol[clamda_parser_get_colpart_id_from_flag(CLAMDA_ORTHO_H2_FLAG)]
			= 3;
		return CLAMDA_LINE_COLPART_NCOL;
	} else if (p->pos_line <= 84) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= 86) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= 90) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else {
		return CLAMDA_LINE_EXTRA;
	}
}

void
line_type_gets_extracted_correctly_test(void** state)
{
	(void)state;

	struct clamda_parser parser = {
		.cur_colpart_flag = 0,
		.pos_line = 0,
		.pos_col = 0,
		.nlev = 0,
		.nlin = 0,
		.npart = 0
	};

	for (size_t i = 0; i <= 95; ++i) {
		enum clamda_line_type expected =
			example_element_advance_line(&parser);
		enum clamda_line_type result =
			clamda_parser_get_line_type(&parser);

		if (expected != result) {
			fail_msg(
				"On file line %d -- %d (%s) != %d (%s)",
				parser.pos_line, expected,
				clamda_parser_line_type_name(expected),
				result,
				clamda_parser_line_type_name(result)
			);
		}
	}
}

/*
void
molecule_name_parse_test(void** state)
{
	char name[BUFSIZ];
	char descr[BUFSIZ];
	struct clamda_parser p = {
		.line = "MOLECULE",
	};

	clamda_parse_name(&p, name, BUFSIZ, descr, BUFSIZ);
	assert_string_equal("MOLECULE", name);
}
*/

int main(void)
{
	const struct CMUnitTest parser_util_test[] = {
		cmocka_unit_test(line_type_gets_extracted_correctly_test),
//		cmocka_unit_test(molecule_name_parse_test),
	};

	int res;
	res = cmocka_run_group_tests(parser_util_test, NULL, NULL);
	return res;
}

