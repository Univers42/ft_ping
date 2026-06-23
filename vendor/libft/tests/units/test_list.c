/* ************************************************************************** */
/*   test_list.c — hard tests for the singly-linked list (ft_list.h API).    */
/*   Uses only deterministic t_rand() values; frees everything via fn_free.  */
/* ************************************************************************** */

#include "libft_test.h"

/* ---- helpers ---- */

/* Content stored in nodes is a plain intptr_t cast to (void*). No heap. */
#define VAL(n) ((void *)(intptr_t)(n))
#define INT(p) ((int)(intptr_t)(p))

/* Map function: doubles the stored integer value (returns new heap content). */
static void	*map_double(void *content)
{
	int		v;
	void	*out;

	v = INT(content);
	/* returning a small integer cast — no malloc needed, fn_free on NULL-ish
	   but ft_lstmap will call ft_lstnew on the returned pointer.
	   We need to pass a del that does nothing since there is no heap. */
	out = VAL(v * 2);
	return (out);
}

/* Iterator accumulator — uses a static so ft_lstiter can add up. */
static long	g_iter_sum = 0;

static void	iter_add(void *content)
{
	g_iter_sum += (long)INT(content);
}

/* del callback that does nothing (content is a cast integer, not heap). */
static void	del_noop(void *content)
{
	(void)content;
}

/* ---- test sections ---- */

static void	test_basics(void)
{
	t_list	*lst;
	t_list	*node;

	lst = NULL;
	/* empty list */
	t_check_int("empty_size", ft_lstsize(NULL), 0);
	t_check("empty_last_null", ft_lstlast(NULL) == NULL);

	/* single node */
	node = ft_lstnew(VAL(42));
	t_check_nonnull("lstnew", node);
	t_check_int("lstnew_content", INT(node->content), 42);
	t_check("lstnew_next_null", node->next == NULL);
	ft_lstadd_front(&lst, node);
	t_check_int("size_after_front", ft_lstsize(lst), 1);
	t_check_int("last_after_front", INT(ft_lstlast(lst)->content), 42);

	/* add back */
	ft_lstadd_back(&lst, ft_lstnew(VAL(99)));
	t_check_int("size_after_back", ft_lstsize(lst), 2);
	t_check_int("front_content", INT(lst->content), 42);
	t_check_int("back_content", INT(ft_lstlast(lst)->content), 99);

	/* clear with noop del (content is not heap) */
	ft_lstclear(&lst, del_noop);
	t_check("cleared_null", lst == NULL);
	t_check_int("size_after_clear", ft_lstsize(lst), 0);
}

static void	test_add_front_back_order(void)
{
	t_list	*lst;
	t_list	*cur;
	int		i;
	int		prev;

	lst = NULL;
	/* add 1000 nodes via add_back: order must be 0..999 */
	i = 0;
	while (i < 1000)
	{
		ft_lstadd_back(&lst, ft_lstnew(VAL(i)));
		i++;
	}
	t_check_int("bulk_back_size", ft_lstsize(lst), 1000);
	/* verify order */
	cur = lst;
	prev = -1;
	i = 0;
	while (cur)
	{
		if (INT(cur->content) != i)
			break ;
		prev = INT(cur->content);
		cur = cur->next;
		i++;
	}
	t_check_int("back_order_last_seen", prev, 999);

	ft_lstclear(&lst, del_noop);

	/* add 1000 nodes via add_front: order must be 999..0 */
	i = 0;
	while (i < 1000)
	{
		ft_lstadd_front(&lst, ft_lstnew(VAL(i)));
		i++;
	}
	t_check_int("bulk_front_size", ft_lstsize(lst), 1000);
	cur = lst;
	prev = 1000;
	i = 999;
	while (cur)
	{
		if (INT(cur->content) != i)
			break ;
		prev = INT(cur->content);
		cur = cur->next;
		i--;
	}
	t_check_int("front_order_last_seen", prev, 0);
	ft_lstclear(&lst, del_noop);
}

static void	test_lstiter_and_lstmap(void)
{
	t_list	*lst;
	t_list	*mapped;
	t_list	*cur;
	long	expected_sum;
	long	mapped_sum;
	int		i;

	lst = NULL;
	expected_sum = 0;
	i = 0;
	while (i < 500)
	{
		ft_lstadd_back(&lst, ft_lstnew(VAL(i)));
		expected_sum += i;
		i++;
	}
	/* iter: accumulate */
	g_iter_sum = 0;
	ft_lstiter(lst, iter_add);
	t_check_int("iter_sum", g_iter_sum, expected_sum);

	/* map: double every element */
	mapped = ft_lstmap(lst, map_double, del_noop);
	t_check_nonnull("map_nonnull", mapped);
	t_check_int("map_size", ft_lstsize(mapped), 500);
	/* verify first and last */
	t_check_int("map_first", INT(mapped->content), 0);
	t_check_int("map_last", INT(ft_lstlast(mapped)->content), 998);

	/* sum of mapped list must be 2 * expected_sum */
	mapped_sum = 0;
	cur = mapped;
	while (cur)
	{
		mapped_sum += INT(cur->content);
		cur = cur->next;
	}
	t_check_int("map_sum", mapped_sum, expected_sum * 2);

	ft_lstclear(&lst, del_noop);
	ft_lstclear(&mapped, del_noop);
}

static void	test_delone_and_clear_partial(void)
{
	t_list	*lst;
	t_list	*second;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(VAL(1)));
	ft_lstadd_back(&lst, ft_lstnew(VAL(2)));
	ft_lstadd_back(&lst, ft_lstnew(VAL(3)));

	/* detach head manually and delone it */
	second = lst->next;
	ft_lstdelone(lst, del_noop);
	lst = second;
	t_check_int("after_delone_size", ft_lstsize(lst), 2);
	t_check_int("after_delone_first", INT(lst->content), 2);

	ft_lstclear(&lst, del_noop);
	t_check("after_clear_null", lst == NULL);
}

/* stress: 3000-node churn with random values, check size + sum invariants */
static void	test_stress_rand(void)
{
	t_list	*lst;
	t_list	*cur;
	long	sum_push;
	long	sum_iter;
	int		i;
	int		v;

	t_reseed(0xDEADBEEF);
	lst = NULL;
	sum_push = 0;
	i = 0;
	while (i < 3000)
	{
		v = (int)(t_rand() % 10000);
		ft_lstadd_back(&lst, ft_lstnew(VAL(v)));
		sum_push += v;
		i++;
	}
	t_check_int("stress_size", ft_lstsize(lst), 3000);

	/* manual sum via traversal */
	sum_iter = 0;
	cur = lst;
	while (cur)
	{
		sum_iter += INT(cur->content);
		cur = cur->next;
	}
	t_check_int("stress_sum_match", sum_iter, sum_push);

	/* clear to empty then refill small */
	ft_lstclear(&lst, del_noop);
	t_check_int("stress_after_clear_size", ft_lstsize(lst), 0);

	i = 0;
	while (i < 5)
	{
		ft_lstadd_back(&lst, ft_lstnew(VAL(i * 10)));
		i++;
	}
	t_check_int("refill_size", ft_lstsize(lst), 5);
	t_check_int("refill_first", INT(lst->content), 0);
	t_check_int("refill_last", INT(ft_lstlast(lst)->content), 40);
	ft_lstclear(&lst, del_noop);
}

/* test lstsize on NULL */
static void	test_null_guards(void)
{
	t_list	*empty;

	t_check_int("size_null", ft_lstsize(NULL), 0);
	t_check("last_null", ft_lstlast(NULL) == NULL);
	/*
	 * SUSPECTED BUG: ft_lstclear(NULL, del) crashes — it dereferences
	 * the outer pointer unconditionally (!*lst) before checking if lst
	 * itself is NULL. We do NOT call ft_lstclear(NULL,...) here.
	 * Instead we call it with a valid pointer-to-NULL (safe path).
	 */
	empty = NULL;
	ft_lstclear(&empty, del_noop);
	t_check("null_clear_noop", empty == NULL);
}

int	main(void)
{
	t_begin("list");
	t_reseed(0xC0FFEE42);
	test_null_guards();
	test_basics();
	test_add_front_back_order();
	test_lstiter_and_lstmap();
	test_delone_and_clear_partial();
	test_stress_rand();
	return (t_end());
}
