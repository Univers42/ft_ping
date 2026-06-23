/* ************************************************************************** */
/*   test_dynstr.c — full lifecycle test for t_dyn_str (dyn_string).          */
/*   Tests init, push/pushstr/pushnstr, pop, clear, free, growth churn.       */
/*   All memory freed; t_end() must report 0 live bytes.                      */
/* ************************************************************************** */

#include "libft_test.h"
#include "srcs/ds/dyn_string/dyn_string.h"

/* ------------------------------------------------------------------ tests  */

/* 1. Basic init and single-char push */
static void	test_basic_push(void)
{
	t_dyn_str	s;

	dyn_str_init(&s);
	t_check_int("init_len", (long)s.len, 0);
	t_check_int("init_cap", (long)s.cap, 0);

	dyn_str_push(&s, 'A');
	t_check_int("push1_len", (long)s.len, 1);
	t_check("push1_nonnull", s.buff != NULL);
	t_check("push1_val", s.buff[0] == 'A');
	t_check("push1_nul", s.buff[1] == '\0');

	dyn_str_free(&s);
	t_check("push1_freed", s.buff == NULL);
}

/* 2. pushstr builds a string correctly */
static void	test_pushstr(void)
{
	t_dyn_str	s;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "hello");
	t_check_int("pushstr_len", (long)s.len, 5);
	t_check_str("pushstr_val", s.buff, "hello");
	t_check_nonnull("pushstr_nonnull", s.buff);

	dyn_str_pushstr(&s, " world");
	t_check_int("pushstr2_len", (long)s.len, 11);
	t_check_str("pushstr2_val", s.buff, "hello world");
	/* verify memory content */
	t_check_mem("pushstr2_mem", s.buff, "hello world", 11);

	dyn_str_free(&s);
}

/* 3. pushnstr appends exactly n bytes */
static void	test_pushnstr(void)
{
	t_dyn_str	s;

	dyn_str_init(&s);
	/* push only "hel" from "hello" */
	dyn_str_pushnstr(&s, "hello", 3);
	t_check_int("pushnstr_len", (long)s.len, 3);
	t_check_str("pushnstr_val", s.buff, "hel");

	dyn_str_pushnstr(&s, "world_extra", 5);
	t_check_int("pushnstr2_len", (long)s.len, 8);
	t_check_str("pushnstr2_val", s.buff, "helworld");

	dyn_str_free(&s);
}

/* 4. Build a long string by appending 2000 single chars via pushstr */
static void	test_long_string_build(void)
{
	t_dyn_str	s;
	int			i;
	int			ok;

	t_reseed(0xFEED01);
	dyn_str_init(&s);
	i = 0;
	while (i < 2000)
	{
		dyn_str_push(&s, (char)('a' + (t_rand() % 26)));
		i++;
	}
	t_check_int("long_len", (long)s.len, 2000);
	t_check("long_nonnull", s.buff != NULL);
	/* NUL-terminated */
	ok = (s.buff[s.len] == '\0');
	t_check("long_nul", ok);

	dyn_str_free(&s);
}

/* 5. pop reduces length and returns correct char */
static void	test_pop(void)
{
	t_dyn_str	s;
	char		c;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "abc");
	c = dyn_str_pop(&s);
	t_check("pop_val_c", c == 'c');
	t_check_int("pop_len", (long)s.len, 2);
	t_check_str("pop_remain", s.buff, "ab");

	c = dyn_str_pop(&s);
	t_check("pop_val_b", c == 'b');
	c = dyn_str_pop(&s);
	t_check("pop_val_a", c == 'a');
	t_check_int("pop_empty", (long)s.len, 0);

	dyn_str_free(&s);
}

/* 6. clear resets len but keeps buffer allocation */
static void	test_clear_reuse(void)
{
	t_dyn_str	s;
	size_t		cap_before;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "some content here");
	cap_before = s.cap;
	t_check("cap_nonzero", cap_before > 0);

	dyn_str_clear(&s);
	t_check_int("clear_len", (long)s.len, 0);
	t_check("clear_buf_kept", s.buff != NULL);
	t_check("clear_nul", s.buff[0] == '\0');

	/* re-use after clear */
	dyn_str_pushstr(&s, "reuse");
	t_check_int("reuse_len", (long)s.len, 5);
	t_check_str("reuse_val", s.buff, "reuse");

	dyn_str_free(&s);
}

/* 7. Multiple reallocations via repeated pushstr (growth churn) */
static void	test_growth_churn(void)
{
	t_dyn_str	s;
	int			i;
	long		total;

	t_reseed(0x42BEEF);
	dyn_str_init(&s);
	total = 0;
	i = 0;
	while (i < 500)
	{
		dyn_str_pushstr(&s, "abcdef");
		total += 6;
		i++;
	}
	t_check_int("churn_len", (long)s.len, total);
	t_check("churn_nul", s.buff[s.len] == '\0');

	dyn_str_clear(&s);
	t_check_int("churn_clear_len", (long)s.len, 0);

	/* second fill */
	i = 0;
	while (i < 300)
	{
		dyn_str_push(&s, (char)('A' + (i % 26)));
		i++;
	}
	t_check_int("churn2_len", (long)s.len, 300);

	dyn_str_free(&s);
}

/* 8. dyn_str_idx returns char value at position */
static void	test_idx(void)
{
	t_dyn_str	s;
	int			i;
	int			ok;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "Hello42");
	/* dyn_str_idx returns (int)buff[idx] */
	ok = (dyn_str_idx(&s, 0) == (int)'H');
	t_check("idx_0", ok);
	ok = (dyn_str_idx(&s, 5) == (int)'4');
	t_check("idx_5", ok);
	ok = (dyn_str_idx(&s, 6) == (int)'2');
	t_check("idx_6", ok);
	t_check_int("idx_len", (long)s.len, 7);
	(void)i;

	dyn_str_free(&s);
}

/* 9. ends_with_str check */
static void	test_ends_with(void)
{
	t_dyn_str	s;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "hello world");
	t_check("ends_world", dyn_str_ends_with_str(&s, "world") != 0);
	t_check("not_ends_hello", dyn_str_ends_with_str(&s, "hello") == 0);
	dyn_str_free(&s);
}

/* 10. Double-alloc stress: 1000 push/pop cycles */
static void	test_push_pop_cycle(void)
{
	t_dyn_str	s;
	int			i;
	long		sum;
	char		c;

	t_reseed(0xC0DE99);
	dyn_str_init(&s);
	sum = 0;
	i = 0;
	while (i < 1000)
	{
		c = (char)('a' + (t_rand() % 26));
		dyn_str_push(&s, c);
		sum += c;
		i++;
	}
	t_check_int("cycle_len", (long)s.len, 1000);

	/* pop everything, accumulate chars */
	i = 0;
	while (s.len > 0)
	{
		dyn_str_pop(&s);
		i++;
	}
	t_check_int("cycle_pop_count", (long)i, 1000);
	t_check_int("cycle_empty", (long)s.len, 0);

	dyn_str_free(&s);
}

/* 11. pushnstr with n=0 is a no-op */
static void	test_pushnstr_zero(void)
{
	t_dyn_str	s;

	dyn_str_init(&s);
	dyn_str_pushstr(&s, "abc");
	dyn_str_pushnstr(&s, "xyz", 0);
	t_check_int("pushnstr0_len", (long)s.len, 3);
	t_check_str("pushnstr0_val", s.buff, "abc");
	dyn_str_free(&s);
}

/* ------------------------------------------------------------------ main   */

int	main(void)
{
	t_begin("dynstr");
	t_reseed(0x12345678);
	test_basic_push();
	test_pushstr();
	test_pushnstr();
	test_long_string_build();
	test_pop();
	test_clear_reuse();
	test_growth_churn();
	test_idx();
	test_ends_with();
	test_push_pop_cycle();
	test_pushnstr_zero();
	return (t_end());
}
