#ifndef _CLAMDA_H
#define _CLAMDA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum clamda_colpart_id {
	CLAMDA_H2 = 1,
	CLAMDA_PARA_H2 = 2,
	CLAMDA_ORTHO_H2 = 3,
	CLAMDA_ELECTRONS = 4,
	CLAMDA_HI = 5,
	CLAMDA_HELIUM = 6,
	CLAMDA_HII = 7
};

inline const char*
clamda_colpart_name(enum clamda_colpart_id id)
{
	static const char* const names[CLAMDA_HII] = {
		"H2",
		"para-H2",
		"ortho-H2",
		"electrons",
		"HI",
		"Helium",
		"HII"
	};
	
	return names[id - 1];
}

// Possible LAMDA values:
// * integer
// * float
// * string
// * arrays of those
enum clamda_value_type {
	CLAMDA_VALUE_TYPE_INTEGER,
	CLAMDA_VALUE_TYPE_FLOAT,
	CLAMDA_VALUE_TYPE_STRING,
	CLAMDA_VALUE_TYPE_ARRAY
};

struct clamda_value {
	int type;
	char* value;
};

enum clamda_error_code {
	CLAMDA_OK = 0,
};

struct clamda_parser_error {
	enum clamda_error_code error_code;
	uint32_t nline, ncol;
	char* descr;
};

#ifdef __cplusplus
}
#endif

#endif  // _CLAMDA_H
