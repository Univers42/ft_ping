/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <errno.h>
# include <getopt.h>
# include <limits.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include "libft.h"

# define PING_PAYLOAD	56
# define PING_TTL	64
# define PING_INTERVAL	1000000LL
# define PING_RECV_WAIT	1000000LL
# define PING_NAMESZ	256
# define PING_PATMAX	16
# define PING_SIZEMAX	65399
# define OPT_TTL	256
# define OPT_IPTS	257

enum e_args
{
	ARGS_OK,
	ARGS_HELP,
	ARGS_ERR
};

typedef struct s_stats
{
	long long	sent;
	long long	recv;
	long long	errors;
	long long	min_us;
	long long	max_us;
	long long	sum_us;
	long long	sum_sq;
}	t_stats;

typedef struct s_ping
{
	const char			*host;
	char				dst_str[INET_ADDRSTRLEN];
	struct sockaddr_in	dst;
	int					sock;
	uint16_t			id;
	int					seq;
	int					verbose;
	int					numeric;
	int					flood;
	int					dontroute;
	int					ip_ts;
	int					ttl;
	int					tos;
	int					preload;
	int					payload_size;
	long long			count;
	long long			interval_us;
	long long			recv_wait_us;
	long long			deadline_us;
	long long			start_us;
	unsigned char		pattern[PING_PATMAX];
	int					pattern_len;
	unsigned char		*pkt;
	unsigned char		*rbuf;
	size_t				rbuf_sz;
	t_stats				st;
}	t_ping;

/* args.c */
int			parse_args(int ac, char **av, t_ping *pg);
/* args2.c */
int			dispatch_opt(t_ping *pg, int c, char *arg);
/* usage.c */
void		print_usage(int fd);
/* dns.c */
int			resolve_target(t_ping *pg);
/* net.c */
int			open_socket(t_ping *pg);
void		close_socket(t_ping *pg);
int			set_ttl(int fd, int ttl);
/* sockopt.c */
int			apply_sockopts(t_ping *pg);
/* ipts.c */
void		print_ip_ts(const struct iphdr *ip);
/* checksum.c */
uint16_t	icmp_checksum(const void *buf, size_t len);
/* send.c */
int			send_echo(t_ping *pg);
/* recv.c */
int			wait_readable(int fd, long long deadline_us);
int			recv_one(t_ping *pg);
/* loop.c */
int			ping_loop(t_ping *pg);
/* flood.c */
int			flood_loop(t_ping *pg);
/* pattern.c */
int			parse_pattern(t_ping *pg, const char *s);
void		fill_pattern(const t_ping *pg, unsigned char *data);
/* print.c */
void		print_header(const t_ping *pg);
void		print_reply(const t_ping *pg, int seq, int ttl, long long us);
void		print_error(const char *from_ip, int bytes, const char *reason);
/* stats.c */
void		stats_add(t_stats *st, long long us);
void		print_stats(const t_ping *pg);
long long	isqrt_ll(long long n);
/* signal.c */
void		install_sigint(void);
int			ping_stopped(void);
/* util.c */
long long	now_us(void);
long long	tv_to_us(const struct timeval *tv);
int			error_msg(const char *what, const char *why);

#endif
