/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:33:14 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:52:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>
# include "ft_stddef.h"
# include "ds.h"

# ifndef DEFAULT_WHITE
#  define DEFAULT_WHITE 0xFFFFFF
# endif
# define SKIP_TRIM_CHARS 0x01
# define SKIP_TRIM_SUBSTR 0x02
# define SKIP_TRIM_WORDS 0x04

typedef struct s_bsearch_ctx
{
	const void	*base;
	size_t		nmemb;
	size_t		size;
}	t_bsearch_ctx;

/**
 * Compute the length of a NUL-terminated string.
 *
 * @param s Pointer to the NUL-terminated string.
 * @return Number of characters preceding the terminating NUL.
 */
t_size				ft_strlen(const char *s);

/**
 * Copy up to dsize - 1 characters from src to dst, NUL-terminate dst,
 * and return the length of src. Matches the semantics of BSD strlcpy.
 *
 * @param dst Destination buffer.
 * @param src Source NUL-terminated string.
 * @param dsize Size of the destination buffer (bytes).
 * @return Total length of src (strlen(src)).
 * If return >= dsize, truncation occurred.
 */
t_size				ft_strlcpy(char *dst, const char *src, t_size dsize);

/**
 * Appends the string `src` to the end of
 * the string `dst`, ensuring that the total length
 * of the resulting string does not exceed
 * `dsize`. The function returns the total length
 * of the string it tried to create
 * (i.e., the length of `src` + the length of `dst`).
 *
 * @param dst The destination string to which `src` will be appended.
 * @param src The source string to append to `dst`.
 * @param dsize The size of the destination buffer `dst`.
 * @return
 * The total length of the string that
 * would have been created if `dsize` was large enough.
 *
 * @note
 * The function appends at most `dsize - 1`
 * characters from `src` to `dst` and ensures that
 * `dst` is null-terminated. If `dsize` is less than
 * or equal to the length of `dst`, no characters
 * are appended, and the function returns the length of `src` + `dsize`.
 */
t_size				ft_strlcat(char *dst, const char *src, t_size dsize);

/**
 * Locate first occurrence of c in s.
 * @param s NUL-terminated string.
 * @param c character to search for (interpreted as unsigned char).
 * @return pointer to character or NULL if not found.
 */
char				*ft_strchr(const char *s, int c);

/**
 * Locate last occurrence of c in s.
 * @param s NUL-terminated string.
 * @param c character to search for.
 * @return pointer to character or NULL if not found.
 */
char				*ft_strrchr(const char *s, int c);

/**
 * Find first occurrence of needle in haystack.
 * @param haystack NUL-terminated string to search.
 * @param needle NUL-terminated substring to find.
 * @return pointer to first occurrence or NULL.
 */
char				*ft_strstr(const char *haystack, const char *needle);

/**
 * Find first occurrence of needle in haystack within len bytes.
 * @param haystack buffer to search.
 * @param needle substring to find.
 * @param len max bytes of haystack to consider.
 * @return pointer to first occurrence or NULL.
 */
char				*ft_strnstr(const char *haystack,
						const char *needle, t_size len);

/**
 * Allocate and return a new string which is the concatenation of s1 and s2.
 * @return newly allocated NUL-terminated string or NULL on allocation failure.
 */
char				*ft_strjoin(const char *s1, const char *s2);

/**
 * Return a newly allocated substring of s starting at start of length len.
 * @param s source string.
 * @param start starting index.
 * @param len maximum length of substring.
 * @return newly allocated substring or NULL on failure.
 */
char				*ft_substr(const char *s, unsigned int start, t_size len);

/**
 * Trim characters in set from both ends of s1.
 * @param s1 input string.
 * @param set characters to remove.
 * @return newly allocated trimmed string or NULL on failure.
 */
char				*ft_strtrim(const char *s1, const char *set);

/**
 * Split s by delimiter c. Returns a NULL-terminated array of strings.
 * @param s input string.
 * @param c delimiter character.
 * @return allocated array of strings or NULL on failure.
 */
char				**ft_split(const char *s, char c);

/**
 * Apply function f to each character of s to create a new string.
 * @param s input string.
 * @param f mapping function (index, char) -> char.
 * @return newly allocated mapped string or NULL on failure.
 */
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/**
 * Iterate string s and call f(index, &char).
 * @param s modifiable string.
 * @param f callback.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * Compare up to n bytes of s1 and s2.
 * @return <0, 0, >0 like memcmp.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * Find character c within the first n bytes of ptr.
 * @return pointer to found char or NULL.
 */
char				*ft_strnchr(char *ptr, int c, size_t n);

/**
 * Locates the first occurrence of
 * the substring `needle` in the string `haystack`,
 * within the first `n` characters.
 *
 * @param haystack The string in which to search for the substring `needle`.
 * @param needle The substring to search for in `haystack`.
 * @param n The maximum number of characters to search in `haystack`.
 * @return
 * A pointer to the beginning of the first
 * occurrence of `needle` in `haystack`,
 * or NULL if `needle` is not found within the first `n` characters.
 *
 * @note
 * If `needle` is an empty string, the function returns `haystack`.
 * The search is case-sensitive,
 * and the function stops searching after `n` characters,
 * ensuring that it doesn't search past the
 * specified length.
 */
char				*ft_strnstr(const char *big,
						const char *little, t_size len);

/**
 * Duplicate the given string.
 * @return newly allocated copy or NULL on failure.
 */
char				*ft_strdup(const char *s);

/**
 * Length of string up to and including first occurrence of c (or ft_strlen).
 * @return number of bytes.
 */
t_size				ft_strclen(const char *s, int c);

/**
 * Duplicate at most n bytes from s into a new NUL-terminated string.
 * @return newly allocated string or NULL.
 */
char				*ft_strndup(const char *s, t_size n);

/**
 * Compare two NUL-terminated strings.
 * @return <0, 0, >0 like strcmp.
 */
int					ft_strcmp(const char *s1, const char *s2);

/**
 * Count words in s separated by limiter.
 * @return number of words.
 */
int					ft_countwords(const char *s1, const char limiter);
/**
 * Count words separated by whitespace.
 * @return number of words.
 */
int					ft_countwords_space(const char *s1);

/**
 * Convert NUL-terminated decimal string to long.
 * @return parsed value (no errno handling).
 */
long				ft_atol(const char *str);

/**
 * Join multiple strings. Variadic; first is format or first piece.
 * @return newly allocated string or NULL.
 */
char				*ft_strnjoin(const char *first, ...);

/**
 * Copy at most n bytes from src to dest, always NUL-terminate if space.
 * @return dest.
 */
char				*ft_strncpy(char *dest, const char *src, size_t n);

/**
 * Locate the first occurrence of the substring `needle` in `haystack`.
 *
 * @param haystack NUL-terminated string to search.
 * @param needle   NUL-terminated substring to find.
 * @return pointer to the first byte of the first occurrence of `needle` in
 *         `haystack`, or NULL if `needle` is not found. If `needle` is an
 *         empty string, returns (char *)haystack.
 */
char				*ft_strstr(const char *haystack, const char *needle);

/**
 * Tokenize string with delim (reentrant like strtok).
 * @return pointer to next token or NULL.
 */
char				*ft_strtok(char *str, const char *delim);

/**
 * strchr but returns pointer to NUL if c == '\0' and not found.
 */
char				*ft_strchrnul(const char *s, int c);

/**
 * Copy src into dst and return pointer to NUL terminator in dst.
 * @return pointer to end of dst after copy.
 */
char				*strpcpy(char *dst, const char *src);

/**
 * Allocate and return a saved copy of s (convenience wrapper).
 */
char				*save_str(const char *s);

/**
 * Return length of initial segment of s containing no characters from reject.
 */
size_t				ft_strcspn(const char *s, const char *reject);

/**
 * Return length of initial segment of s containing only characters from accept.
 */
size_t				ft_strspn(const char *s, const char *accept);

/**
 * Print common characters of str1 and str2 once each (writes to stdout).
 */
void				inter(const char *str1, const char *str2);

/**
 * Print union of characters from str1 then str2 (each printed once).
 */
void				ft_union(const char *str1, const char *str2);

/*
 * Copy n bytes from src to dst. Handles overlapping regions and
 * attempts word-sized copies when alignment allows.
 * Signature follows the traditional bcopy(src, dst, n).
 */
void				bcopy(const void *src, void *dst, size_t n);

/**
 * Find the end of a name token in a NUL-terminated string.
 *
 * @param {const char *} name
 *   Pointer to the string where a name token may start. The function expects
 *   a valid, NUL-terminated string; passing NULL is undefined behavior.
 *
 * @returns {char *}
 *   Pointer to the first character that is not part of the name token.
 *   If the first character is not a valid name character (is_name_char()),
 *   the original pointer is returned. Otherwise the returned pointer points
 *   at the character that terminated the name (or the terminating NUL).
 *
 * @description
 *   A "name" is determined by the project-specific helpers is_name_char()
 *   (for the first character) and is_in_name() (for subsequent characters).
 *   The function does not modify the input string.
 *
 * @example
 *   input: "foo=bar" => returns pointer to '=' (end of "foo")
 *   char *end = end_of_name("foo=bar");
 */
char				*end_of_name(const char *name);
int					str_lastsame(const char *old, const char *newstr);

/**
 * Remove all leading whitespace from STRING. This includes
 * newlines. STRING should be terminated with zero
 */
void				strip_leading(char *string);
char				*strsub(const char *string, const char *pat,
						const char *rep, bool glob);
/**
 * Remove all trailing whitespaces from STRING. This includes
 * newlines. if newlines only is non-zero, only trainlinng newline
 * are removed. STRING should be terminated with a zero
 */
void				strip_trailing(char *string, int len, bool nl_only);
char				*str_prefix(const char *string, const char *pfx);
char				*single_quote(const char *s);
const char *const	*find_string(const char *s,
						const char *const *array, size_t nmemb);
int					pstrcmp(const void *a, const void *b);
void				*ft_bsearch(const void *key, const t_bsearch_ctx *ctx,
						int (*cmp)(const void *, const void *));
void				bsearch_ctx_init(t_bsearch_ctx *ctx,
						const void *base, size_t nmemb, size_t size);
char				*ft_sstrdup(const char *p);
char				*prefix(const char *string, const char *pfx);
size_t				ft_strnlen(const char *s, size_t maxlen);
char				*ft_strcpy(char *dest, const char *src);
int					max_munch(char *haystack,
						void *needles, size_t offset, size_t size);
int					ft_strcasecmp(const char *s1, const char *s2);
int					ft_strncasecmp(const char *s1, const char *s2, size_t n);
bool				str_slice_eq_str(char *s, size_t len, char *s2);
int					num_blocks(const char *str, char *sep);
int					find_block(int *end, const char *str, const char *sep);
char				**ft_split_str(char *str, char *sep);
void				trim_newline(char *s);

/* Remove trailing characters/substrings from LINE according to PATTERN.
 * - default skip_trailing() uses SKIP_TRIM_CHARS behavior.
 * - skip_trailing_flags() allows selecting modes above via flags.
 *
 * Returns the original buffer pointer (modified in-place). */
char				*skip_trailing(char *line, const char *pattern_to_skip);
char				*skip_trailing_flags(char *line,
						const char *pattern_to_skip, int flags);

#endif
