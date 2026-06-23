/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:56:46 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:32:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // added for intptr_t
#include <stdbool.h>

// /* Add macros and prototypes so they're visible before use */
// #define VSTR_FIXED 0x01
// #define VUNSET 0x02

// void *set_vareq(const char *name, void *arg2, int flags);
// void *some_func(void);

/* Single universal ternary function using void pointers */

/* For function execution: ternary(cond, fn1, fn2) */
void	*ternary(bool cond, void *true_val, void *false_val)
{
	if (cond)
		return (true_val);
	else
		return (false_val);
}
