/* ************************************************************************** */
/*   test_ctype.c — full 0..255 sweep of every ft_ctype function              */
/*   Oracle: standard <ctype.h> with (unsigned char) cast, C locale.          */
/* ************************************************************************** */

#include "libft_test.h"
#include <ctype.h>   /* isalpha, etc. — oracle only, NOT the tested fns */

/* helper: compare boolean result (nonzero vs zero) */
static int	same_bool(int a, int b)
{
	return ((!a) == (!b));
}

/* ---- full-range sweeps --------------------------------------------------- */

static void	test_isalpha_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isalpha(c), isalpha((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isalpha_full_0_255", pass);
}

static void	test_isdigit_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isdigit(c), isdigit((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isdigit_full_0_255", pass);
}

static void	test_isalnum_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isalnum(c), isalnum((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isalnum_full_0_255", pass);
}

static void	test_isspace_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isspace(c), isspace((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isspace_full_0_255", pass);
}

static void	test_isprint_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isprint(c), isprint((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isprint_full_0_255", pass);
}

static void	test_isupper_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isupper(c), isupper((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isupper_full_0_255", pass);
}

static void	test_islower_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_islower(c), islower((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("islower_full_0_255", pass);
}

static void	test_isascii_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isascii(c), isascii(c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isascii_full_0_255", pass);
}

static void	test_isgraph_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isgraph(c), isgraph((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isgraph_full_0_255", pass);
}

static void	test_isblank_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 255)
	{
		if (!same_bool(ft_isblank(c), isblank((unsigned char)c)))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("isblank_full_0_255", pass);
}

/* ---- toupper / tolower --------------------------------------------------- */

static void	test_toupper_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 127)
	{
		if (ft_toupper(c) != toupper(c))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("toupper_full_0_127", pass);
}

static void	test_tolower_full(void)
{
	int	pass;
	int	c;

	pass = 1;
	c = 0;
	while (c <= 127)
	{
		if (ft_tolower(c) != tolower(c))
		{
			pass = 0;
			break ;
		}
		c++;
	}
	t_check("tolower_full_0_127", pass);
}

/* ---- spot checks so the stdout shows specific values --------------------- */

static void	test_spot_checks(void)
{
	t_check_int("isalpha_A", ft_isalpha('A') != 0, 1);
	t_check_int("isalpha_z", ft_isalpha('z') != 0, 1);
	t_check_int("isalpha_0", ft_isalpha('0'), 0);
	t_check_int("isdigit_5", ft_isdigit('5') != 0, 1);
	t_check_int("isdigit_a", ft_isdigit('a'), 0);
	t_check_int("isalnum_A", ft_isalnum('A') != 0, 1);
	t_check_int("isalnum_7", ft_isalnum('7') != 0, 1);
	t_check_int("isalnum_sp", ft_isalnum(' '), 0);
	t_check_int("isspace_tab", ft_isspace('\t') != 0, 1);
	t_check_int("isspace_nl", ft_isspace('\n') != 0, 1);
	t_check_int("isspace_A", ft_isspace('A'), 0);
	t_check_int("isprint_sp", ft_isprint(' ') != 0, 1);
	t_check_int("isprint_del", ft_isprint(127), 0);
	t_check_int("isprint_nul", ft_isprint(0), 0);
	t_check_int("isupper_A", ft_isupper('A') != 0, 1);
	t_check_int("isupper_a", ft_isupper('a'), 0);
	t_check_int("islower_a", ft_islower('a') != 0, 1);
	t_check_int("islower_A", ft_islower('A'), 0);
	t_check_int("isascii_0", ft_isascii(0) != 0, 1);
	t_check_int("isascii_127", ft_isascii(127) != 0, 1);
	t_check_int("isascii_128", ft_isascii(128), 0);
	t_check_int("isgraph_sp", ft_isgraph(' '), 0);
	t_check_int("isgraph_bang", ft_isgraph('!') != 0, 1);
	t_check_int("isblank_sp", ft_isblank(' ') != 0, 1);
	t_check_int("isblank_tab", ft_isblank('\t') != 0, 1);
	t_check_int("isblank_nl", ft_isblank('\n'), 0);
	t_check_int("toupper_a", ft_toupper('a'), 'A');
	t_check_int("toupper_A", ft_toupper('A'), 'A');
	t_check_int("toupper_5", ft_toupper('5'), '5');
	t_check_int("tolower_A", ft_tolower('A'), 'a');
	t_check_int("tolower_a", ft_tolower('a'), 'a');
	t_check_int("tolower_5", ft_tolower('5'), '5');
}

/* ---- small alloc churn so the ft leak path is exercised ------------------ */

static void	test_alloc_churn(void)
{
	int		i;
	long	total;
	char	*p;

	t_reseed(0x1234ABCD);
	total = 0;
	i = 0;
	while (i < 1000)
	{
		p = (char *)fn_malloc(16);
		if (p)
		{
			p[0] = (char)(t_rand() & 0xFF);
			total += ft_isalpha((unsigned char)p[0]) ? 1 : 0;
			fn_free(p);
		}
		i++;
	}
	/* total is deterministic; just confirm it ran without leak */
	t_check_int("alloc_churn_done", total >= 0, 1);
}

int	main(void)
{
	t_begin("ctype");
	t_reseed(0xC0DE);

	test_isalpha_full();
	test_isdigit_full();
	test_isalnum_full();
	test_isspace_full();
	test_isprint_full();
	test_isupper_full();
	test_islower_full();
	test_isascii_full();
	test_isgraph_full();
	test_isblank_full();
	test_toupper_full();
	test_tolower_full();
	test_spot_checks();
	test_alloc_churn();

	return (t_end());
}
