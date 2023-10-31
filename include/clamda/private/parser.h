#ifndef _CLAMDA_PARSER_H
#define _CLAMDA_PARSER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
	CLAMDA_BUFSIZ = 512,
	CLAMDA_MAX_COLPART = 7,
	CLAMDA_MAX_COLPART_TEMPS = 64
};

enum clamda_colpart_id_flag {
	CLAMDA_H2_FLAG = 1,
	CLAMDA_PARA_H2_FLAG = 2,
	CLAMDA_ORTHO_H2_FLAG = 4,
	CLAMDA_ELECTRONS_FLAG = 8,
	CLAMDA_HI_FLAG = 16,
	CLAMDA_HELIUM_FLAG = 32,
	CLAMDA_HII_FLAG = 64
};

enum clamda_colpart_id
clamda_parser_get_colpart_id_from_flag(enum clamda_colpart_id_flag flag);

enum clamda_line_type {
	CLAMDA_LINE_NAME,
	CLAMDA_LINE_WEIGHT,
	CLAMDA_LINE_NLEV,
	CLAMDA_LINE_ENLEV,
	CLAMDA_LINE_NLIN,
	CLAMDA_LINE_LINE,
	CLAMDA_LINE_NPART,
	CLAMDA_LINE_COLPART_NAME,
	CLAMDA_LINE_COLPART_NCOL,
	CLAMDA_LINE_COLPART_NTEMP,
	CLAMDA_LINE_COLPART_TEMP,
	CLAMDA_LINE_COLPART_COLTRANS,
	CLAMDA_LINE_EXTRA
};

struct clamda_parser_error {
	int errc;
	uint32_t nline, ncol;
	char* descr;
};

struct clamda_parser {
	FILE* input;
	uint32_t pos_line, pos_col;
	enum clamda_line_type line_type;
	uint32_t nlev, nlin, npart;
	union {
		struct {
			uint16_t cur_colpart_flag;
			uint16_t colparts;
		};
		uint32_t ncol[CLAMDA_MAX_COLPART + 1];
	};
	uint32_t ntemp[CLAMDA_MAX_COLPART + 1];
	char line[CLAMDA_BUFSIZ];
};

enum clamda_line_type
clamda_parser_get_line_type(const struct clamda_parser* const);

const char*
clamda_parser_line_type_name(enum clamda_line_type type);

int
clamda_parser_readline(struct clamda_parser*);

int
clamda_parse_name(struct clamda_parser* p,
		char* name_buf, size_t name_buf_size,
		char* descr_buf, size_t descr_buf_size);

#endif
