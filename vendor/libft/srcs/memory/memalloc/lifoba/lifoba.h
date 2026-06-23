/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifoba.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:34:44 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * TODO:
 * - start_stack_str(ep); list_vars.c
 * - stack_str_end(); list_vars.c
 */
/* libmemalloc — LIFO (stack) arena allocator
 *
 * Purpose
 *   Small, efficient LIFO bump allocator intended for short-lived
 *   allocations (parse trees, temporary strings, token buffers) where
 *   allocation is frequent but deallocation is always in stack order.
 *
 * Design highlights
 *   - Arena is implemented as a llist of blocks (bump allocator per block).
 *   - Fast O(1) alloc by pointer bumping; dealloc is O(1) by pointer rewind.
 *   - Stack marks (push/set/pop) allow saving and restoring arena state.
 *   - Provides string-building helpers that grow the cur-block.
 *
 * When to use
 *   - Use for lifetime-scoped temporary data that follows LIFO semantics.
 *   - Great for parsers, lexers, command ASTs and temporary buffers.
 *   - Not appropriate for long-lived alloc that require individual free().
 *
 * Quick usage example
 *   t_stack_mark mark;
 *   set_stack_mark(&mark);
 *   char *p = start_stack_str();
 *   p = st_puts("hello", p);
 *   p = stack_str_nul(p);
 *   // use stack_block() (string lives until pop_stack_mark)
 *   pop_stack_mark(&mark); // discards allocations since the mark
 *
 * Notes
 *   - The ctx is a process-global returned by arena_ctx().
 *   - The allocato shall do its memalloc for block management.
 *   - st_alloc/st_unalloc are generic : st_alloc returns raw bytes.
 *   - All allocation sizes are aligned to machine word size for correctness.
 *
 * Implementation detail reminders
 *   - ARENA_MINSIZE defines the minimal usable payload per block.
 *   - The t_stack_block struct stores prev link and raw byte buffer.
 *
 * Keep the rest of this header as the declarations and typedefs used by the
 * implementation and callers (types, macros, and function prototypes).
 */
/* ************************************************************************** */

#ifndef LIFOBA_H
# define LIFOBA_H

# include <stddef.h>
# include <stdlib.h>

# define ARENA_MINSIZE 504

/**
 * SYNTAX:
 * * Mblock: marked block
 * * Mtime: marked time
 * * freeB: free byte
 * * nfreeB: number of free byte
 * * cblock: current blockç
 * * pel: pointer to the end limit
 * * nxfree: next free byte
 */
typedef struct s_stack_block
{
	struct s_stack_block	*prev;
	char					space[ARENA_MINSIZE];
}	t_stack_block;

typedef struct s_stack_mark
{
	t_stack_block	*stackp;
	char			*stacknxt;	// pointer to next freeB in the Mblock
	size_t			stacknleft;	// nfreeb remaining in that block at Mtime
}	t_stack_mark;

typedef struct s_garena
{
	t_stack_block	stack_base; // inlined initial block
	t_stack_block	*stackp;	// where allocations happen
	char			*stack_next;// pointer to the nxfreeB in the cblock
	size_t			stack_nleft;// remaining free bytes in the cblock
	char			*sstrend;	// pel of the cblock
}	t_garena;

typedef struct s_dynall
{
	size_t			aligned;	// requested size aligned
	size_t			block_size;	// usable bytes
	size_t			len;		// bytes to malloc
	t_stack_block	*p;			// tmp ptr to new alloc or exp_block
}	t_dynall;

/* ctx */
/**
 * @brief  Return the singleton arena ctx.
 *
 * The library uses a process-global singleton t_garena. This function
 * returns a pointer to that ctx. The ctx is initialized on
 * first call. The implementation is not thread-safe.
 *
 * @return Pointer to the arena ctx (t_garena*).
 *
 * @note Many API functions (allocation, growth, marks) depend on this
 *       ctx being available; callers normally do not need to call
 *       this directly except for diagnostics or tests.
 */
t_garena	*arena_ctx(void);

/**
 * @brief  Free all dynamic blocks and reset the arena to initial state.
 *
 * Frees any blocks allocated beyond the inlined base block and resets the
 * arena pointers so the ctx becomes as if freshly initialized.
 *
 * @note After calling this, any pointers previously returned by st_alloc()
 *       are invalid.
 */
void		arena_cleanup(void);

/* Core allocator (generic, not only strings) */
/**
 * @brief  Allocate nbytes from the current arena (LIFO bump allocator).
 *
 * Allocates and returns a pointer to nbytes of storage within the arena.
 * Allocation is aligned to machine word size. If the current block does
 * not have enough space the arena will grow (allocate a new block or
 * expand the current one) transparently.
 *
 * @param  nbytes Number of bytes requested.
 * @return Pointer to allocated memory (non-NULL). Returned memory is not
 *         zero-initialized.
 *
 * @note Use st_unalloc to rewind; individual free() of returned pointers is
 *       not supported.
 */
void		*st_alloc(size_t nbytes);

/**
 * @brief  Rewind the arena to the supplied pointer (LIFO unallocation).
 *
 * If p points into the current top block and is no newer than the most
 * recent allocation, this will move the stack pointer back to p making
 * the subsequent space available for reuse. If p is NULL or outside the
 * current valid range this is a no-op.
 *
 * @param  p Pointer previously returned by st_alloc or a pointer inside the
 *           current allocation region.
 */
void		st_unalloc(void *p);

/* Growing the active stack block/string */
/**
 * @brief  Ensure a block with at least 'min' free bytes is available.
 *
 * If the current block cannot satisfy 'min', this routine will either
 * expand the top block (when allowed) or allocate a new block and move
 * the active data if necessary.
 *
 * @param  min Minimum required free bytes.
 * @return Pointer to the base of the (possibly new) free region where
 *         allocations may start (equivalent to stack_block()).
 */
char		*grow_stack_block(size_t min);

/**
 * @brief  Grow area for string building and return pointer for next char.
 *
 * Convenience used by character-oriented helpers (st_putc). Ensures there
 * is at least one byte available for storing the next character and
 * returns the pointer where the character should be written.
 *
 * @return Pointer to the position to store the next character.
 */
void		*grow_stack_str(void);

/**
 * @brief  Ensure current block has at least len free bytes available.
 *
 * If the remaining space in the current block is less than len this will
 * grow the arena appropriately (allocate/expand/move) and return the start
 * of the free region.
 *
 * @param  len Minimum free bytes required.
 * @return Pointer to the start of a region with at least len bytes free.
 */
char		*grow_stack_to(size_t len);

/**
 * @brief  Ensure 'newlen' bytes are available for a string that begins at p.
 *
 * When building or extending strings this helper computes the offset of p
 * from the start of the current string region, ensures 'newlen' bytes are
 * available (growing the arena if required) and returns the new base pointer
 * adjusted for the original offset.
 *
 * @param  newlen Required total length for the string region.
 * @param  p      Current pointer within the current string region.
 * @return Pointer to the start of the string region (possibly moved).
 */
char		*make_str_space(size_t newlen, char *p);

/**
 * @brief  Reserve len bytes in the arena (alias to st_alloc used from helpers).
 *
 * A convenience wrapper used internally by mark helpers to reserve block
 * space. Calls st_alloc(len) and discards the returned pointer.
 *
 * @param  len Number of bytes to reserve.
 */
void		grab_stack_block(size_t len);

/* Stack mark helpers */
/**
 * @brief  Push a mark that also reserves len bytes in the arena.
 *
 * Stores the current arena state in the supplied t_stack_mark structure
 * and reserves 'len' bytes so subsequent code can write intermediate data.
 *
 * @param  mark Pointer to a t_stack_mark structure to populate.
 * @param  len  Number of bytes to reserve immediately after saving the mark.
 *
 * @see set_stack_mark() for saving state without reservation.
 */
void		push_stack_mark(t_stack_mark *mark, size_t len);

/**
 * @brief  Save the current arena state into mark (no reservation).
 *
 * Records the current top-of-stack block, the next pointer and the number
 * of free bytes so the arena can later be restored with pop_stack_mark().
 *
 * @param  mark Pointer to a t_stack_mark object to initialize.
 */
void		set_stack_mark(t_stack_mark *mark);

/**
 * @brief  Restore arena state to the given mark and free newer blocks.
 *
 * Restores the arena to the state captured by a previous set_stack_mark()
 * or push_stack_mark(). Any blocks allocated after the mark are freed and
 * the stack pointer and free count are restored.
 *
 * @param  mark Pointer to the mark to restore. If mark is NULL this is a no-op.
 */
void		pop_stack_mark(t_stack_mark *mark);

/* String helpers on top of arena */
/**
 * @brief  Return pointer to the start/base of the current string region.
 *
 * This is the pointer to the first byte of the current active string being
 * built (the region that start_stack_str() and grab_stack_str()/stack_str_nul()
 * operate on).
 *
 * @return Pointer to current string base.
 */
char		*stack_block(void);

/**
 * @brief  Return number of free bytes left in the current block.
 *
 * Useful to decide whether a grow operation is required before writing.
 *
 * @return Number of bytes available in the active block.
 */
size_t		stack_block_size(void);

/**
 * @brief  Return pointer to start a new string in the current block.
 *
 * Alias to stack_block() provided for API compatibility with old memalloc
 * semantics.
 *
 * @return Pointer to the first byte where string building should start.
 */
char		*start_stack_str(void);

/**
 * @brief  Write a terminating NUL at the current string pointer.
 *
 * If the provided pointer equals the block end this function will grow the
 * block first. Returns the pointer to the NUL byte (i.e. p where '\0' was
 * stored).
 *
 * @param  p Pointer to the byte where NUL should be stored (typically the
 *           pointer returned after successive st_putc/st_nputs calls).
 * @return Pointer to the stored NUL character.
 */
char		*stack_str_nul(char *p);

/**
 * @brief  Append up to n bytes from s to the string at p.
 *
 * Ensures space for n bytes (using make_str_space) and copies the bytes.
 *
 * @param  s Source buffer (may be NULL when n==0).
 * @param  n Count of bytes to append.
 * @param  p Current insertion pointer inside the active string region.
 * @return New insertion pointer (p + n).
 */
char		*st_nputs(const char *s, size_t n, char *p);

/**
 * @brief  Append a NUL-terminated string s to the string at p.
 *
 * @param  s Source NUL-terminated string.
 * @param  p Current insertion pointer.
 * @return New insertion pointer (advanced by ft_strlen(s)).
 */
char		*st_puts(const char *s, char *p);

/**
 * @brief  Append a single character c to the string at p.
 *
 * Automatically grows the string area if needed.
 *
 * @param  c Character to append (stored as a char).
 * @param  p Current insertion pointer.
 * @return New insertion pointer (one past the written character).
 */
char		*st_putc(int c, char *p);
/**
 * @brief  Undo the last put (move insertion pointer one byte back).
 *
 * @param  p Current insertion pointer.
 * @return Pointer decremented by one (or same if p is NULL).
 */
char		*st_unputc(char *p);

/**
 * @brief  Return the last written character at p.
 *
 * Reads the character located just before p (i.e. p[-1]) as unsigned char.
 *
 * @param  p Current insertion pointer.
 * @return Last character written.
 */
int			st_topc(char *p);

/**
 * @brief  Adjust a pointer by amount bytes.
 *
 * Convenience helper to move a pointer relative to its current position.
 *
 * @param  amount Signed number of bytes to move the pointer.
 * @param  p      Original pointer.
 * @return Adjusted pointer (p + amount).
 */
char		*st_adjust(ptrdiff_t amount, char *p);

/**
 * @brief  Rewind/unallocate a previously grabbed string region.
 *
 * Wrapper around st_unalloc for string-grab semantics.
 *
 * @param  s Pointer previously used with grab_stack_str()
 * or returned by st_alloc().
 */
void		ungrab_stack_str(void *s);

/**
 * @brief  Commit the bytes written into a string region.
 *
 * If p points within the current string region, this reserves the used
 * bytes by calling st_alloc(offset) so subsequent allocations cannot
 * overwrite the committed data.
 *
 * @param  p Pointer to the insertion position to commit (one past last used).
 */
char		**grab_stack_str(char *p);

/* Generic helpers */
/**
 * @brief  Align nbytes to machine word size (sizeof(void *)).
 *
 * @param  nbytes Unaligned size.
 * @return Aligned size (multiple of sizeof(void *)).
 */
size_t		arena_align(size_t nbytes);

/**
 * @brief  Return minimal block payload size for the arena (aligned).
 *
 * Typically used to decide minimal block allocation/request size.
 *
 * @param  nbytes Requested size.
 * @return Aligned minimal size to use for blocks or allocations.
 */
size_t		min_size(size_t nbytes);

/**
 * @brief  Duplicate a C string using libc malloc.
 *
 * @param  s Source NUL-terminated string.
 * @return Newly allocated copy (must be freed with arena_free or free()).
 */
char		*str_save(const char *s);

/**
 * @brief  Wrapper around malloc for arena implementation.
 *
 * Centralized to allow checking and potential customization of allocation
 * strategy used for arena block management.
 *
 * @param  nbytes Number of bytes to allocate.
 * @return Pointer to allocated memory (non-NULL on success).
 */
void		*arena_malloc(size_t nbytes);

/**
 * @brief  Wrapper around realloc for arena implementation.
 *
 * Used when expanding the current top block in-place.
 *
 * @param  p      Pointer previously returned by arena_malloc/arena_realloc.
 * @param  nbytes New requested size.
 * @return Pointer to reallocated memory (non-NULL on success).
 */
void		*arena_realloc(void *p, size_t nbytes);

/**
 * @brief  Wrapper around free for arena-allocated blocks.
 *
 * @param  p Pointer returned by arena_malloc/arena_realloc.
 */
void		arena_free(void *p);

/**
 * @brief  Compute a new payload length to use when growing a block.
 *
 * Uses current arena metrics to pick an expanded size that reduces
 * future reallocations. Returns a payload length (usable bytes).
 *
 * @param  min Minimum required payload bytes.
 * @param  g   Pointer to arena ctx used for heuristics.
 * @return Chosen payload length in bytes.
 */
size_t		compute_new_len(size_t min, t_garena *g);

char		*stack_str_end(void);

#endif
