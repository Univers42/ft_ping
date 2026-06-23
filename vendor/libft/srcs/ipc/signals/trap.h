/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:16:02 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAP_H
# define TRAP_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef _BSD_SOURCE
#  define _BSD_SOURCE
# endif

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include "../../../include/ft_string.h"

typedef enum e_sigs
{
	SIG_INHERITED = 0x0,
	SIG_TRAPPED = 0x1,
	SIG_HARD_IGNORE = 0x2,
	SIG_SPECIAL = 0x4,
	SIG_NO_TRAP = 0x8,
	SIG_INPROGRESS = 0x10,
	SIG_CHANGED = 0x20,
	SIG_IGNORED = 0x40,
	SIG_ASYNCSIG = 0x80
}	t_sigs;

# define IMPOSSIBLE_TRAP_HANDLER -1
# define TRAP_IMPOSSIBLE "IMPOSSIBLE_TRAP_HANDLER"
# define BASH_NSIG 64
# define DSIG_SIGPREFIX 0x01
# define DSIG_NOCASE 0x02
# define NO_SIG -1
# define DEBUG_TRAP BASH_NSIG
# define ERROR_TRAP 65
# define RETURN_TRAP 66
# define EXIT_TRAP 0

/* Use object sentinels for trap_list bookkeeping to avoid casting function
   pointers to void* in many places (reduces -Wpedantic noise). */
# define DEFAULT_SIG "<DEFAULT_SIG>"
# define IGNORE_SIG "<IGNORE_SIG>"
# define BASH_NSIG_TOTAL 67

# ifndef NSIG
#  define NSIG BASH_NSIG_TOTAL
# endif

/* Standard signal handler types */
typedef void				(*t_sig_handler)(int);
typedef unsigned int		t_sigset;
typedef struct sigaction	t_sigaction;

static inline int	spec_trap(int s)
{
	return ((s == EXIT_TRAP) || (s == DEBUG_TRAP)
		|| (s == ERROR_TRAP) || (s == RETURN_TRAP));
}

static inline int	recursive_sig(int s)
{
	return (spec_trap(s) == 0);
}

/* Global signal state structure */
typedef struct s_glob_sig
{
	int				sigmodes[BASH_NSIG_TOTAL];
	volatile int	from_return_trap;
	volatile int	sigwinch_received;
	volatile int	intpending;
	volatile int	sigterm_received;
	int				interrupt_immediately;
	int				terminate_immediately;
	int				builtin_catch_sigpipe;
	int				waiting_for_child;
	t_sig_handler	original_signals[NSIG];
	char			*trap_list[BASH_NSIG_TOTAL];
	int				pending_traps[NSIG];
	int				running_traps;
	int				trap_return_ctx;
	int				trap_saved_exit_value;
	int				wait_signal_received;
	int				trapped_signal_received;
	int				suppress_debug_trap_verbose;
	int				catch_flag;
	int				function_trace_mode;
	int				error_trace_mode;
	int				reset_signal;
	char			*signal_name[NSIG];
	int				interactive;
	int				should_unwind;
}	t_glob_sig;

/* Signal Management Functions */
void				change_signal(int sig, char *value);
int					any_signals_trapped(void);
void				check_signals(void);
void				clear_pending_traps(void);
int					decode_signal(const char *string, int flags);
int					first_pending_trap(void);
void				init_chld_signal(void);
void				init_int_signal(void);
void				free_trap_command(int sig);
void				free_trap_string(int sig);
void				free_trap_strings(void);
void				get_all_original_signals(void);
void				get_orig_sig(int sig);
void				get_original_signal(int sig);
int					last_signal(void);
void				reset_sigterm(void);
void				ignore_signal(int sig);
void				init_quit_signal(void);
void				initialize_traps(void);
void				initialize_signames(void);
void				get_original_tty_job_signals(void);
void				initialize_terminating_signals(void);
int					maybe_call_trap_handler(int sig);
int					next_pending_trap(int start);
/* Custom Signal Set API */
unsigned int		ft_sigmask(int x);
void				ft_sigemptyset(t_sigset *set);
int					ft_sigismember(const t_sigset *set, int sig);
int					ft_sigblock(int mask);
void				ft_sigfillset(t_sigset *set);
void				ft_sigaddset(t_sigset *set, int sig);
void				ft_sigdelset(t_sigset *set, int sig);
/* Reset and Restore Functions */
void				check_sigterm(void);
void				zreset_if_needed(void);
void				zreset(void);
void				reinit_trap(int sig);
void				reset_signal_handlers(void);
void				reset_or_restore_signal_handlers(void (*func)(int));
void				reset_signal(int sig);
void				restore_bash_trapsig(char *oldval);
void				restore_default_signal(int sig);
void				restore_original_signals(void);
void				restore_signal(int sig);
char				*save_bash_trapsig(void);
void				set_bash_trapsig(int sig);
void				set_debug_trap(const char *command);
void				set_error_trap(const char *command);
void				set_orig_sig(int sig, t_sig_handler handler);
void				set_original_signal(int sig, t_sig_handler handler);
void				set_return_trap(const char *command);
t_sig_handler		set_sigint_handler(void);
void				set_signal_async_ignored(int sig);
void				set_signal_hard_ignored(int sig);
void				set_signal_ignored(int sig);
void				set_signal(int sig, const char *string);
void				set_trap_state(int sig);
/* Signal Action Wrappers */
int					ft_sigpause(int mask);
t_sig_handler		set_signal_handler(int sig, t_sig_handler handler);
int					ft_sigprocmask(int opt, t_sigset *newset, t_sigset *oldset);
int					ft_sigsuspend(const t_sigset *set);
/* Signal Query Functions */
int					signal_in_progress(int sig);
int					signal_is_async_ignored(int sig);
int					signal_is_hard_ignored(int sig);
int					signal_is_ignored(int sig);
int					signal_is_pending(int sig);
int					signal_is_special(int sig);
int					signal_is_trapped(int sig);
char				*signal_name(int sig);
/* Trap Logic */
void				trap_if_untrapped(int sig, const char *command);
t_sig_handler		trap_to_sighandler(int sig);
void				uw_maybe_set_return_trap(void *command);
void				uw_maybe_set_debug_trap(void *command);
void				uw_maybe_set_error_trap(void *command);
void				uw_set_error_trap(void *command);
/* Signal Handler Functions */
void				trap_handler(int sig);
void				termsig_sighandler(int sig);
/* External variable management stubs */
void				unbind_variable_noref(const char *name);
void				bind_variable(const char *name, const char *val, int flags);
void				bind_var_to_int(const char *name, int value, int flags);
char				*get_string_value(const char *name);
int					valid_number(const char *s, intmax_t *out);
/* Global Accessors */
t_glob_sig			*get_g_sig(void);
void				block_signal(int sig, t_sigset *set, t_sigset *oset);
void				unblock_signal(const t_sigset *oset);
void				sigint_sighandler(int sig);
void				set_wind(int sig);
void				mask_dfl_sigact(void (*handler)(int),
						int sa_flags, int ig_quits);
void				set_unwind_sig(void);
void				set_unwind_sig_norestart(void);
void				bg_signals(void);

static inline char	*savestring(const char *s)
{
	return (save_str(s));
}

#endif /* TRAP_H */
