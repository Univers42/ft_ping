/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stddef.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:56:07 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:15:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDDEF_H
# define FT_STDDEF_H
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>

typedef void*				t_addr;
typedef void*				t_ptr;
typedef int					(*t_ctype)(int);
typedef long				t_ssize;
typedef unsigned long int	t_size;
// maps
typedef unsigned char		t_uint8;
// used for inter-thread or signal communication
typedef volatile int		t_sig_atomic;
typedef int*				t_array;
// Good name for char** typedef:
typedef float				t_weight;
typedef double				t_prec;
typedef int					t_qty;
typedef int					t_flag;
typedef uint64_t			t_time;

# define CHAR_SIZE 1
# define STDOUT_FILENO 1
# define STDERR_FILENO 2
# define STDIN_FILENO 0
// # define INT_MAX 2147483647
// # define INT_MIN (-2147483648)
// # define NULL ((void *)0)
# define SUCCESS 0
# define FAILURE 1
# define ERROR 1
# define OK 0
# define BYTE 8
/***************************
 * WRAPPED MESSAGES SHORTCUT
 ***************************/

# define NULLSTR ""
# define SPC_STR " "
# define SPACE_CHAR 32

/* common escape characters */
# define ESC_N '\n'	 /* newline */
# define ESC_T '\t'	 /* tab */
# define ESC_R '\r'	 /* carriage return */
# define ESC_B '\b'	 /* backspace */
# define ESC_A '\a'	 /* bell/alert */
# define ESC_E '\e'	 /* escape (same as \x1B) */
# define ESC_F '\f'	 /* form feed */
# define ESC_V '\v'	 /* vertical tab */
# define ESC_BS '\\'	 /* backslash */
# define ESC_NUL '\0' /* NUL byte */

# define SYMBOL_UNICODE_BAR "┃"
# define SYMBOL_UNICODE_HEADER_TOP_LEFT "┏"
# define SYMBOL_UNICODE_HEADER_TOP_RIGHT "┓"
# define SYMBOL_UNICODE_HEADER_BOTTOM_LEFT "┗"
# define SYMBOL_UNICODE_HEADER_BOTTOM_RIGHT "┛"
# define SYMBOL_UNICODE_HEADER_T_JOINT "┳"
# define SYMBOL_UNICODE_FOOTER_T_JOINT "┻"
# define SYMBOL_UNICODE_HEADER_CROSS "╋"
# define SYMBOL_UNICODE_HEADER_HORIZONTAL_LINE "━"
# define SYMBOL_UNICODE_VERTICAL_T_LEFT "┣"
# define SYMBOL_UNICODE_VERTICAL_T_RIGHT "┫"

# define INITIAL_CAPACITY 10
# define GROWTH_FACTOR 2
# define MAX_LINE_LENGTH 4096

# define SNL_FMT "%s\n"
# define ILL_NUM "Illegal number: %s"
# define HOME_STR "HOME"
# define DOT_DIR "."

# define COMMAND_NOT_FOUND 127
# define EXE_PERM_DENIED 126
# define EXE_BASE_ERROR 125
# define CANCELED 130
# define SYNTAX_ERR 2
# define AMBIGUOUS_REDIRECT 1

# ifndef PROMPT
#  define PROMPT "\001❯ \002"
# endif

# ifndef HIST_FILE
#  define HIST_FILE ".minishell_history"
# endif

# ifndef RL_SPACER_1
#  define RL_SPACER_1 "\x03"
# endif
# define ANSI_RED "\001\033[31m\002"
# define ANSI_GREEN "\001\033[32m\002"
# define ANSI_RESET "\001\033[0m\002"

# define LEXER_SQUOTE_PROMPT "squote> "
# define LEXER_DQUOTE_PROMPT "dquote> "
# define LEXER_BQUOTE_PROMPT "bquote> "
/**************************
 * ENUMS
 **************************/
typedef enum s_severity
{
	SEV_INFO = 150,
	SEV_WARNING = 200,
	SEV_ERROR = 300
}	t_severity;

typedef enum e_state
{
	ST_FILE_NOT_FOUND = -2,
	ST_ERR,
	ST_FILE_ERR_FATAL_MEMORY,
	ST_OK = 0,
	ST_DONE = 0,
	ST_DEFAULT = 0,
	ST_INIT = 0,
	ST_NORMAL = 0, // Default state
	ST_USE = 1,
	ST_FOUND_NL = 1,
	ST_IN_MEMORY = 1,
	ST_DEAD,
	ST_INFO_BASE = SEV_INFO,
	ST_MATCH_ANY,
	ST_MATCH_BEG,
	ST_MATCH_END,
	ST_MATCH_GLOBREP,
	ST_MATCH_QUOTED,
	ST_MATCH_LITERAL,
	ST_MATCH_ASSIGNRHS,
	ST_MATCH_VARSUB,
	ST_MATCH_CMDSUB,
	ST_MATCH_ARITH,
	ST_MATCH_PATHNAME,
	ST_MATCH_WORDBOUND,
	ST_MATCH_EXTGLOB,
	ST_MATCH_ERRBASE,
	ST_MATCH_EXPREP,
	ST_MATCH_ESCAPED,
	ST_BIN_FILE,
	ST_IN_SQUOTE,	// Inside single quotes
	ST_IN_DQUOTE,	// Inside double quotes
	ST_IN_BQUOTE,	// Inside backticks
	ST_IN_SUBSHELL, // Inside $()
	ST_IN_ARITH,	// Inside $(())
	ST_IN_PARAM,	// Inside ${}
	ST_SLASH,
	ST_ASTERISK,
	ST_HEREDOC,		// Reading heredoc content
	ST_IN_COMMENT,	// Reading comment
	ST_MORE_INPUT,
	ST_IN_WORD,
	ST_ESCAPE_NEXT, // next char is escaped
	ST_WHITESPACE,	// Reading whitespace
	ST_SIGN,
	ST_BASE_PREFIX,
	ST_DIGITS,
	ST_FILLED,
	ST_SCANNING,
	ST_RESET_ALLOC,
	ST_RESET_PTR,
	ST_EOF,
	ST_WARNING_BASE = SEV_WARNING,
	ST_OVERFLOW,
	ST_ERR_BASE = SEV_ERROR,
	ST_EXECUTION_FAILURE,
	ST_EX_BADUSAGE,
	ST_EX_MISCERROR,
	ST_RETRYFAIL,
	ST_WEXPCOMBSUB,
	ST_EX_NOEXEC,
	ST_EX_NOINPUT,
	ST_EX_NOTFOUND,
	ST_EX_ERRBASE,
	ST_EX_BADSYNTAX,
	ST_EX_USAGE,
	ST_EX_REDIRFAIL,
	ST_EX_BADASSIGN,
	ST_EXPRFAIL,
	ST_EX_DISKFALLBACK,
	ST_EX_UTILERROR,
	ST_ERR_ALLOC,
	ST_ERR_FATAL
}	t_state;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_order
{
	ASCENDING,
	DESCENDING
}	t_order;

typedef enum e_sign
{
	NEGATIVE = -1,
	ZERO = 0,
	POSITIVE = 1
}	t_sign;

typedef enum e_side
{
	LEFT,
	RIGHT
}	t_side;

typedef enum e_parity
{
	EVEN,
	ODD
}	t_parity;

typedef enum e_overflow
{
	NO_OVERFLOW,
	OVERFLOW,
	UNDERFLOW
}	t_overflow;

typedef enum e_endianness
{
	FT_LITTLE_ENDIAN,
	FT_BIG_ENDIAN
}	t_endianness;

typedef enum e_mode
{
	MODE_READ,
	MODE_WRITE,
	MODE_APPEND
}	t_mode;

typedef enum e_type
{
	TYPE_UCHAR,
	TYPE_CHAR,
	TYPE_USHORT,
	TYPE_SHORT,
	TYPE_UINT,
	TYPE_INT,
	TYPE_ULONG,
	TYPE_LONG,
	TYPE_LLONG,
	TYPE_ULLONG,
	TYPE_UINT8,
	TYPE_INT8,
	TYPE_UINT16,
	TYPE_INT16,
	TYPE_UINT32,
	TYPE_INT32,
	TYPE_UINT64,
	TYPE_INT64,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_BOOL,
	TYPE_DOUBLE,
	TYPE_VOID,
	TYPE_HEX,
	TYPE_PTR,
	TYPE_FLOAT_PTR,
	TYPE_DOUBLE_PTR
}	t_type;

typedef enum e_align
{
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_CENTER
}	t_align;

typedef enum e_direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
}	t_direction;

typedef struct s_type_info
{
	unsigned long long	max_val;
	long long			min_val;
	bool				is_signed;
}	t_type_info;

typedef enum e_resize
{
	RESIZE_INCREASE,
	RESIZE_DECREASE,
	RESIZE_MAINTAIN
}	t_resize;

typedef enum e_filter
{
	FILTER_NONE,
	FILTER_LOW_PASS,
	FILTER_HIGH_PASS,
	FILTER_BAND_PASS,
	FILTER_BAND_STOP
}	t_filter;

typedef enum e_sort_algorithm
{
	SORT_BUBBLE,
	SORT_SELECTION,
	SORT_INSERTION,
	SORT_MERGE,
	SORT_QUICK,
	SORT_HEAP
}	t_sort_algorithm;

typedef enum e_search_algorithm
{
	SEARCH_LINEAR,
	SEARCH_BINARY,
	SEARCH_JUMP,
	SEARCH_INTERPOLATION
}	t_search_algorithm;

typedef struct s_fnctx
{
	void	(*fn)(void *arg);
	void	*arg;
}	t_fnctx;

#endif
