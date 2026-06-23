/* ************************************************************************** */
/*   test_wctype.c — pure ASCII-range tests for ft_wctype functions           */
/*                                                                            */
/*   All implementations in srcs/wctype/ are pure ASCII-range: they make no  */
/*   allocations, hold no state, and do not depend on locale. We therefore    */
/*   test the full ASCII range (0..127) for each classification function and  */
/*   verify the conversion functions, plus the ft_wctype/ft_iswctype helpers. */
/*   ft_setlocale, ft_mbrtowc, ft_wcwidth are locale/IO-bound and are skipped.*/
/* ************************************************************************** */

#include "libft_test.h"
#include <wctype.h>   /* iswalpha, etc. — oracle for ASCII range only */

/* ---- ASCII-range sweeps -------------------------------------------------- */

static void	test_iswdigit(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		/* oracle: digit iff '0'..'9' */
		int exp = (wc >= L'0' && wc <= L'9');
		if (!ft_iswdigit(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswdigit_ascii", pass);
	t_check_int("iswdigit_0", ft_iswdigit(L'0') != 0, 1);
	t_check_int("iswdigit_9", ft_iswdigit(L'9') != 0, 1);
	t_check_int("iswdigit_a", ft_iswdigit(L'a'), 0);
	t_check_int("iswdigit_sp", ft_iswdigit(L' '), 0);
}

static void	test_iswalpha(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = ((wc >= L'A' && wc <= L'Z') || (wc >= L'a' && wc <= L'z'));
		if (!ft_iswalpha(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswalpha_ascii", pass);
	t_check_int("iswalpha_A", ft_iswalpha(L'A') != 0, 1);
	t_check_int("iswalpha_z", ft_iswalpha(L'z') != 0, 1);
	t_check_int("iswalpha_0", ft_iswalpha(L'0'), 0);
}

static void	test_iswalnum(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = ft_iswalpha(wc) || ft_iswdigit(wc);
		if (!ft_iswalnum(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswalnum_ascii", pass);
	t_check_int("iswalnum_A", ft_iswalnum(L'A') != 0, 1);
	t_check_int("iswalnum_7", ft_iswalnum(L'7') != 0, 1);
	t_check_int("iswalnum_sp", ft_iswalnum(L' '), 0);
}

static void	test_iswupper(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = (wc >= L'A' && wc <= L'Z');
		if (!ft_iswupper(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswupper_ascii", pass);
	t_check_int("iswupper_A", ft_iswupper(L'A') != 0, 1);
	t_check_int("iswupper_Z", ft_iswupper(L'Z') != 0, 1);
	t_check_int("iswupper_a", ft_iswupper(L'a'), 0);
}

static void	test_iswlower(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = (wc >= L'a' && wc <= L'z');
		if (!ft_iswlower(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswlower_ascii", pass);
	t_check_int("iswlower_a", ft_iswlower(L'a') != 0, 1);
	t_check_int("iswlower_z", ft_iswlower(L'z') != 0, 1);
	t_check_int("iswlower_A", ft_iswlower(L'A'), 0);
}

static void	test_iswspace(void)
{
	t_check_int("iswspace_sp", ft_iswspace(L' ') != 0, 1);
	t_check_int("iswspace_tab", ft_iswspace(L'\t') != 0, 1);
	t_check_int("iswspace_nl", ft_iswspace(L'\n') != 0, 1);
	t_check_int("iswspace_cr", ft_iswspace(L'\r') != 0, 1);
	t_check_int("iswspace_vt", ft_iswspace(L'\v') != 0, 1);
	t_check_int("iswspace_ff", ft_iswspace(L'\f') != 0, 1);
	t_check_int("iswspace_A", ft_iswspace(L'A'), 0);
	t_check_int("iswspace_0", ft_iswspace(L'0'), 0);
}

static void	test_iswblank(void)
{
	t_check_int("iswblank_sp", ft_iswblank(L' ') != 0, 1);
	t_check_int("iswblank_tab", ft_iswblank(L'\t') != 0, 1);
	t_check_int("iswblank_nl", ft_iswblank(L'\n'), 0);
	t_check_int("iswblank_A", ft_iswblank(L'A'), 0);
}

static void	test_iswcntrl(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = (wc <= 0x1F || wc == 0x7F);
		if (!ft_iswcntrl(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswcntrl_ascii", pass);
	t_check_int("iswcntrl_nul", ft_iswcntrl(0) != 0, 1);
	t_check_int("iswcntrl_del", ft_iswcntrl(0x7F) != 0, 1);
	t_check_int("iswcntrl_sp", ft_iswcntrl(L' '), 0);
}

static void	test_iswgraph(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		/* implementation: wc > ' ' && wc <= '~' */
		int exp = (wc > L' ' && wc <= L'~');
		if (!ft_iswgraph(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswgraph_ascii", pass);
	t_check_int("iswgraph_sp", ft_iswgraph(L' '), 0);
	t_check_int("iswgraph_bang", ft_iswgraph(L'!') != 0, 1);
	t_check_int("iswgraph_tilde", ft_iswgraph(L'~') != 0, 1);
}

static void	test_iswprint(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		/* implementation: wc >= ' ' && wc <= '~' */
		int exp = (wc >= L' ' && wc <= L'~');
		if (!ft_iswprint(wc) != !exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("iswprint_ascii", pass);
	t_check_int("iswprint_sp", ft_iswprint(L' ') != 0, 1);
	t_check_int("iswprint_del", ft_iswprint(0x7F), 0);
}

static void	test_iswpunct(void)
{
	t_check_int("iswpunct_bang", ft_iswpunct(L'!') != 0, 1);
	t_check_int("iswpunct_at", ft_iswpunct(L'@') != 0, 1);
	t_check_int("iswpunct_A", ft_iswpunct(L'A'), 0);
	t_check_int("iswpunct_7", ft_iswpunct(L'7'), 0);
	t_check_int("iswpunct_sp", ft_iswpunct(L' '), 0);
	t_check_int("iswpunct_tilde", ft_iswpunct(L'~') != 0, 1);
}

static void	test_iswxdigit(void)
{
	t_check_int("iswxdigit_0", ft_iswxdigit(L'0') != 0, 1);
	t_check_int("iswxdigit_9", ft_iswxdigit(L'9') != 0, 1);
	t_check_int("iswxdigit_A", ft_iswxdigit(L'A') != 0, 1);
	t_check_int("iswxdigit_F", ft_iswxdigit(L'F') != 0, 1);
	t_check_int("iswxdigit_a", ft_iswxdigit(L'a') != 0, 1);
	t_check_int("iswxdigit_f", ft_iswxdigit(L'f') != 0, 1);
	t_check_int("iswxdigit_G", ft_iswxdigit(L'G'), 0);
	t_check_int("iswxdigit_g", ft_iswxdigit(L'g'), 0);
	t_check_int("iswxdigit_sp", ft_iswxdigit(L' '), 0);
}

/* ---- conversion ---------------------------------------------------------- */

static void	test_towlower(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = ft_iswupper(wc) ? (int)(wc + 32) : (int)wc;
		if (ft_towlower(wc) != exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("towlower_ascii", pass);
	t_check_int("towlower_A", ft_towlower(L'A'), L'a');
	t_check_int("towlower_Z", ft_towlower(L'Z'), L'z');
	t_check_int("towlower_a", ft_towlower(L'a'), L'a');
	t_check_int("towlower_5", ft_towlower(L'5'), L'5');
}

static void	test_towupper(void)
{
	wint_t	wc;
	int		pass;

	pass = 1;
	wc = 0;
	while (wc <= 127)
	{
		int exp = ft_iswlower(wc) ? (int)(wc - 32) : (int)wc;
		if (ft_towupper(wc) != exp)
		{
			pass = 0;
			break ;
		}
		wc++;
	}
	t_check("towupper_ascii", pass);
	t_check_int("towupper_a", ft_towupper(L'a'), L'A');
	t_check_int("towupper_z", ft_towupper(L'z'), L'Z');
	t_check_int("towupper_A", ft_towupper(L'A'), L'A');
	t_check_int("towupper_5", ft_towupper(L'5'), L'5');
}

/* ---- ft_wctype (name lookup) and ft_iswctype ----------------------------- */

static void	test_wctype_lookup(void)
{
	t_check_int("wctype_alnum", (int)ft_wctype(L"alnum"), (int)FT_WCTYPE_ALNUM);
	t_check_int("wctype_alpha", (int)ft_wctype(L"alpha"), (int)FT_WCTYPE_ALPHA);
	t_check_int("wctype_digit", (int)ft_wctype(L"digit"), (int)FT_WCTYPE_DIGIT);
	t_check_int("wctype_upper", (int)ft_wctype(L"upper"), (int)FT_WCTYPE_UPPER);
	t_check_int("wctype_lower", (int)ft_wctype(L"lower"), (int)FT_WCTYPE_LOWER);
	t_check_int("wctype_space", (int)ft_wctype(L"space"), (int)FT_WCTYPE_SPACE);
	t_check_int("wctype_blank", (int)ft_wctype(L"blank"), (int)FT_WCTYPE_BLANK);
	t_check_int("wctype_cntrl", (int)ft_wctype(L"cntrl"), (int)FT_WCTYPE_CNTRL);
	t_check_int("wctype_graph", (int)ft_wctype(L"graph"), (int)FT_WCTYPE_GRAPH);
	t_check_int("wctype_print", (int)ft_wctype(L"print"), (int)FT_WCTYPE_PRINT);
	t_check_int("wctype_punct", (int)ft_wctype(L"punct"), (int)FT_WCTYPE_PUNCT);
	t_check_int("wctype_xdigit", (int)ft_wctype(L"xdigit"), (int)FT_WCTYPE_XDIGIT);
	t_check_int("wctype_unknown", (int)ft_wctype(L"bogus"), (int)FT_WCTYPE_NONE);
}

static void	test_iswctype(void)
{
	t_check_int("iswctype_digit_5",
		ft_iswctype(L'5', FT_WCTYPE_DIGIT) != 0, 1);
	t_check_int("iswctype_digit_a",
		ft_iswctype(L'a', FT_WCTYPE_DIGIT), 0);
	t_check_int("iswctype_alpha_A",
		ft_iswctype(L'A', FT_WCTYPE_ALPHA) != 0, 1);
	t_check_int("iswctype_upper_A",
		ft_iswctype(L'A', FT_WCTYPE_UPPER) != 0, 1);
	t_check_int("iswctype_lower_a",
		ft_iswctype(L'a', FT_WCTYPE_LOWER) != 0, 1);
	t_check_int("iswctype_space_tab",
		ft_iswctype(L'\t', FT_WCTYPE_SPACE) != 0, 1);
	t_check_int("iswctype_blank_sp",
		ft_iswctype(L' ', FT_WCTYPE_BLANK) != 0, 1);
	t_check_int("iswctype_cntrl_nul",
		ft_iswctype(0, FT_WCTYPE_CNTRL) != 0, 1);
	t_check_int("iswctype_graph_bang",
		ft_iswctype(L'!', FT_WCTYPE_GRAPH) != 0, 1);
	t_check_int("iswctype_print_sp",
		ft_iswctype(L' ', FT_WCTYPE_PRINT) != 0, 1);
	t_check_int("iswctype_punct_at",
		ft_iswctype(L'@', FT_WCTYPE_PUNCT) != 0, 1);
	t_check_int("iswctype_xdigit_f",
		ft_iswctype(L'f', FT_WCTYPE_XDIGIT) != 0, 1);
	t_check_int("iswctype_none",
		ft_iswctype(L'a', FT_WCTYPE_NONE), 0);
}

/* ---- small alloc churn so the ft leak path is exercised ------------------ */

static void	test_alloc_churn(void)
{
	int		i;
	long	total;
	char	*p;

	t_reseed(0xFEEDFACE);
	total = 0;
	i = 0;
	while (i < 1000)
	{
		p = (char *)fn_malloc(8);
		if (p)
		{
			p[0] = (char)((t_rand() % 26) + 'a');
			total += ft_iswlower((wint_t)(unsigned char)p[0]) ? 1 : 0;
			fn_free(p);
		}
		i++;
	}
	/* all allocations freed; total must be 1000 (all chars are a-z) */
	t_check_int("alloc_churn_all_lower", total, 1000);
}

int	main(void)
{
	t_begin("wctype");
	t_reseed(0xBEEF);

	test_iswdigit();
	test_iswalpha();
	test_iswalnum();
	test_iswupper();
	test_iswlower();
	test_iswspace();
	test_iswblank();
	test_iswcntrl();
	test_iswgraph();
	test_iswprint();
	test_iswpunct();
	test_iswxdigit();
	test_towlower();
	test_towupper();
	test_wctype_lookup();
	test_iswctype();
	test_alloc_churn();

	return (t_end());
}
