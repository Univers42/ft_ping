/* ************************************************************************** */
/*   test_pipe.c — pipe_create + read_line_arena now on the fn_* heap.         */
/*   Proves the whole subsystem allocates/free with fn_* (no arena, no leak).  */
/* ************************************************************************** */

#include "libft_test.h"

int	main(void)
{
	t_pipe_fds	*p;
	char		*l;

	t_begin("pipe");
	p = pipe_create();
	t_check_nonnull("pipe_create", p);
	if (!p)
		return (t_end());
	write_all(p->w, "hello\nworld\nlast", 16);
	pipe_close_end(p, 1);
	l = read_line_arena(p->r);
	t_check_str("line1", l, "hello\n");
	fn_free(l);
	l = read_line_arena(p->r);
	t_check_str("line2", l, "world\n");
	fn_free(l);
	l = read_line_arena(p->r);
	t_check_str("line3", l, "last");
	fn_free(l);
	l = read_line_arena(p->r);
	t_check("line_eof", l == NULL);
	pipe_close_pair(p);
	fn_free(p);
	return (t_end());
}
