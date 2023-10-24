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

struct clamda_colrates {
	uint32_t transition;
	uint32_t up;
	uint32_t low;
	double* rates;
};

typedef struct {
	enum clamda_colpart_id name;
	char* information;
	double* temperatures;

} clamda_colpart_data;

#ifdef __cplusplus
}
#endif

#endif  // _CLAMDA_H
