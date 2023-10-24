#include <stdio.h>

#include <clamda/private/parser.h>

int clamda_parser_readline(struct clamda_parser* const p)
{
	if (fgets(p->line, strlen(p->line), p->input) == NULL) {
		return -1;
	}
	p->pos_line += 1;
	p->pos_col = 0;
	p->line_type = clamda_parser__get_line_type(p);
	return 0;
}

