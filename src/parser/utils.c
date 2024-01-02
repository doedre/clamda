#include <stdbool.h>
#include <errno.h>

#include <clamda/clamda.h>
#include <clamda/private/parser.h>
#include <clamda/private/string.h>

enum clamda_colpart_id
clamda_parser_get_colpart_id_from_flag(enum clamda_colpart_id_flag flag)
{
	switch (flag) {
	case CLAMDA_H2_FLAG:		return CLAMDA_H2;
	case CLAMDA_PARA_H2_FLAG:	return CLAMDA_PARA_H2;
	case CLAMDA_ORTHO_H2_FLAG:	return CLAMDA_ORTHO_H2;
	case CLAMDA_ELECTRONS_FLAG:	return CLAMDA_ELECTRONS;
	case CLAMDA_HI_FLAG:		return CLAMDA_HI;
	case CLAMDA_HELIUM_FLAG:	return CLAMDA_HELIUM;
	case CLAMDA_HII_FLAG:		return CLAMDA_HII;
	default:			return CLAMDA_H2;
	}
}

enum clamda_line_type
clamda_parser_get_line_type(const struct clamda_parser* const p)
{

	#define NLEV (p->nlev)
	#define NLIN (p->nlin)
	#define NCOL \
		(p->ncol[clamda_parser_get_colpart_id_from_flag(p->cur_colpart_flag)])

	#define COLPART_NCOL(cpflag) \
		(p->ncol[clamda_parser_get_colpart_id_from_flag(p->colparts & cpflag)])

	#define COLPART_LINES(cpflag) \
		((COLPART_NCOL(cpflag) && (p->cur_colpart_flag != cpflag)) ? \
		COLPART_NCOL(cpflag) + 9 : 0)

	#define NPART 	\
		(COLPART_LINES(CLAMDA_H2_FLAG) +	\
		COLPART_LINES(CLAMDA_PARA_H2_FLAG) +	\
		COLPART_LINES(CLAMDA_ORTHO_H2_FLAG) +	\
		COLPART_LINES(CLAMDA_ELECTRONS_FLAG) +	\
		COLPART_LINES(CLAMDA_HI_FLAG) +		\
		COLPART_LINES(CLAMDA_HELIUM_FLAG) +	\
		COLPART_LINES(CLAMDA_HII_FLAG))

	if (p->pos_line <= 2) {
		return CLAMDA_LINE_NAME;
	} else if (p->pos_line <= 4) {
		return CLAMDA_LINE_WEIGHT;
	} else if (p->pos_line <= 6) {
		return CLAMDA_LINE_NLEV;
	} else if (p->pos_line <= (7 + NLEV)) {
		return CLAMDA_LINE_ENLEV;
	} else if (p->pos_line <= (9 + NLEV)) {
		return CLAMDA_LINE_NLIN;
	} else if (p->pos_line <= (10 + NLEV + NLIN)) {
		return CLAMDA_LINE_LINE;
	} else if (p->pos_line <= (12 + NLEV + NLIN)) {
		return CLAMDA_LINE_NPART;
	} else if (p->pos_line <= (14 + NLEV + NLIN + NPART)) {
		return CLAMDA_LINE_COLPART_NAME;
	} else if (p->pos_line <= (16 + NLEV + NLIN + NPART)) {
		return CLAMDA_LINE_COLPART_NCOL;;
	} else if (p->pos_line <= (18 + NLEV + NLIN + NPART)) {
		return CLAMDA_LINE_COLPART_NTEMP;
	} else if (p->pos_line <= (20 + NLEV + NLIN + NPART)) {
		return CLAMDA_LINE_COLPART_TEMP;
	} else if (p->pos_line <= (21 + NLEV + NLIN + NPART + NCOL)) {
		return CLAMDA_LINE_COLPART_COLTRANS;
	} else {
		return CLAMDA_LINE_EXTRA;
	}

	#undef NLEV
	#undef NLIN
	#undef NCOL
	#undef COLPART_NCOL
	#undef COLPART_LINES
	#undef NPART
}

const char*
clamda_parser_line_type_name(enum clamda_line_type type)
{
	static const char* const
	clamda_line_type_names[CLAMDA_LINE_EXTRA + 1] = {
		"Element name",
		"Molecular weight",
		"Number of energy levels",
		"Energy level",
		"Number of radiative transitions",
		"Radiative transition",
		"Number of collision partners",
		"Collision partner name",
		"Number of collisional transitions",
		"Number of temperatures for which collisional data exist",
		"Temperatures for which collisional data exists",
		"Collisional transition",
		"Extra information"
	};

	if ((type < 0) || (type > CLAMDA_LINE_EXTRA)) {
		return "Unknown";
	} else {
		return clamda_line_type_names[type];
	}
}

int
clamda_parse_name(struct clamda_parser* p,
		char* name_buf, size_t name_buf_size,
		char* descr_buf, size_t descr_buf_size)
{
	bool comment = false;
	size_t inb = 0, idb = 0;
	name_buf[0] = '\0';
	descr_buf[0] = '\0';
	for (int i = 0, c = p->line[i];
			c != '\n' && c != '\0'; ++i, c = p->line[i]) {
		p->pos_col = i;
		if (c == '!') {
			comment = true;
			continue;
		}

		if (!comment) {
			if (inb < name_buf_size) {
				name_buf[inb] = (char)c;
				++inb;
			} else {
				return ENOBUFS;
			}
		} else {
			if (idb < descr_buf_size) {
				descr_buf[idb] = (char)c;
				++idb;
			} else {
				return ENOBUFS;
			}
		}
	}

	clamda_string_trim(name_buf, ' ');
	clamda_string_trim(descr_buf, ' ');

	return 0;
}

int
clamda_parse_molecular_weight(struct clamda_parser* p, float* weight)
{
	errno = 0;
	*weight = strtof(p->line, NULL);
	if (errno != 0) {
		const int e = errno;
		errno = 0;
		return e;
	}

	return 0;
}

