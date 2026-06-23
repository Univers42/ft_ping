/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:24:11 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:03:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WCTYPE_H
# define FT_WCTYPE_H

# include <wchar.h>

# define FT_LC_ALL		0
# define FT_LC_COLLATE	1
# define FT_LC_CTYPE		2
# define FT_LC_MONETARY	3
# define FT_LC_NUMERIC	4
# define FT_LC_TIME		5
# define FT_LC_MESSAGES	6
# define FT_CAT_COUNT	7

typedef enum e_wctype
{
	FT_WCTYPE_ALNUM,
	FT_WCTYPE_ALPHA,
	FT_WCTYPE_BLANK,
	FT_WCTYPE_CNTRL,
	FT_WCTYPE_DIGIT,
	FT_WCTYPE_GRAPH,
	FT_WCTYPE_LOWER,
	FT_WCTYPE_PRINT,
	FT_WCTYPE_PUNCT,
	FT_WCTYPE_SPACE,
	FT_WCTYPE_UPPER,
	FT_WCTYPE_XDIGIT,
	FT_WCTYPE_NONE
}	t_wctype;

typedef struct s_locale_data
{
	char	*locales[FT_CAT_COUNT];
}	t_locale_data;

/* classification prototypes */
int			ft_iswalnum(wint_t wc);
int			ft_iswalpha(wint_t wc);
int			ft_iswblank(wint_t wc);
int			ft_iswcntrl(wint_t wc);
int			ft_iswdigit(wint_t wc);
int			ft_iswgraph(wint_t wc);
int			ft_iswlower(wint_t wc);
int			ft_iswprint(wint_t wc);
int			ft_iswpunct(wint_t wc);
int			ft_iswspace(wint_t wc);
int			ft_iswupper(wint_t wc);
int			ft_iswxdigit(wint_t wc);

/* generic helpers */
int			ft_towlower(wint_t wc);
int			ft_towupper(wint_t wc);

/* meta helpers */
int			ft_iswctype(wint_t wc, t_wctype desc);
t_wctype	ft_wctype(const wchar_t *name);
size_t		ft_mbrtowc(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps);
void		ft_locale_cleanup(void);
char		*ft_setlocale(int category, const char *locale);
size_t		ft_mb_cur_max(void);
int			ft_wcwidth(wchar_t wc);

#endif
