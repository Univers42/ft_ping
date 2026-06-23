/* ************************************************************************** */
/*   test_dlist.c — hard tests for the doubly-linked list (ft_doubly_list.h) */
/*   Nodes hold integers cast to (void*). No content heap needed; the node   */
/*   structs are freed by ft_dll_destroy / ft_dll_clear.                     */
/* ************************************************************************** */

#include "libft_test.h"

#define VAL(n)  ((void *)(intptr_t)(n))
#define INT(p)  ((int)(intptr_t)(p))

/* ---- basics ---- */
static void	test_create_destroy_empty(void)
{
	t_doubly_list	*dl;

	dl = ft_dll_create();
	t_check_nonnull("dll_create", dl);
	t_check("dll_empty_true", ft_dll_is_empty(dl) == true);
	t_check_int("dll_size_0", (long)ft_dll_size(dl), 0);
	t_check("dll_front_null", ft_dll_front(dl) == NULL);
	t_check("dll_back_null", ft_dll_back(dl) == NULL);
	ft_dll_destroy(dl);
}

/* ---- push_front / push_back order ---- */
static void	test_push_order(void)
{
	t_doubly_list	*dl;
	int				i;

	dl = ft_dll_create();

	/* push_back 0..999: front=0, back=999 */
	i = 0;
	while (i < 1000)
	{
		t_check("push_back_ok", ft_dll_push_back(dl, VAL(i)) == true);
		i++;
	}
	t_check_int("size_after_back", (long)ft_dll_size(dl), 1000);
	t_check_int("front_after_back", INT(ft_dll_front(dl)), 0);
	t_check_int("back_after_back", INT(ft_dll_back(dl)), 999);
	ft_dll_clear(dl);
	t_check_int("size_after_clear", (long)ft_dll_size(dl), 0);
	t_check("empty_after_clear", ft_dll_is_empty(dl) == true);

	/* push_front 0..999: front=999, back=0 */
	i = 0;
	while (i < 1000)
	{
		ft_dll_push_front(dl, VAL(i));
		i++;
	}
	t_check_int("size_after_front", (long)ft_dll_size(dl), 1000);
	t_check_int("front_after_front", INT(ft_dll_front(dl)), 999);
	t_check_int("back_after_front", INT(ft_dll_back(dl)), 0);
	ft_dll_destroy(dl);
}

/* ---- pop_front / pop_back ---- */
static void	test_pop(void)
{
	t_doubly_list	*dl;
	int				i;

	dl = ft_dll_create();
	i = 0;
	while (i < 5)
	{
		ft_dll_push_back(dl, VAL(i));
		i++;
	}
	/* pop from front: 0,1,2 */
	t_check_int("pop_front_0", INT(ft_dll_pop_front(dl)), 0);
	t_check_int("pop_front_1", INT(ft_dll_pop_front(dl)), 1);
	t_check_int("pop_front_2", INT(ft_dll_pop_front(dl)), 2);
	t_check_int("size_after_pop_front", (long)ft_dll_size(dl), 2);

	/* pop from back: 4, then 3 */
	t_check_int("pop_back_4", INT(ft_dll_pop_back(dl)), 4);
	t_check_int("pop_back_3", INT(ft_dll_pop_back(dl)), 3);
	t_check_int("size_empty_after_pop", (long)ft_dll_size(dl), 0);
	t_check("empty_after_pop", ft_dll_is_empty(dl) == true);

	/* pop on empty must return NULL */
	t_check("pop_front_empty_null", ft_dll_pop_front(dl) == NULL);
	t_check("pop_back_empty_null", ft_dll_pop_back(dl) == NULL);
	ft_dll_destroy(dl);
}

/* ---- get / set ---- */
static void	test_get_set(void)
{
	t_doubly_list	*dl;
	int				i;

	dl = ft_dll_create();
	i = 0;
	while (i < 10)
	{
		ft_dll_push_back(dl, VAL(i * 10));
		i++;
	}
	t_check_int("get_0", INT(ft_dll_get(dl, 0)), 0);
	t_check_int("get_5", INT(ft_dll_get(dl, 5)), 50);
	t_check_int("get_9", INT(ft_dll_get(dl, 9)), 90);
	t_check("get_oob_null", ft_dll_get(dl, 10) == NULL);

	/* set index 5 to 555 */
	t_check("set_5_ok", ft_dll_set(dl, 5, VAL(555)) == true);
	t_check_int("get_5_after_set", INT(ft_dll_get(dl, 5)), 555);
	t_check("set_oob_fail", ft_dll_set(dl, 100, VAL(0)) == false);

	ft_dll_destroy(dl);
}

/* ---- insert / remove ---- */
static void	test_insert_remove(void)
{
	t_doubly_list	*dl;
	void			*val;

	dl = ft_dll_create();
	ft_dll_push_back(dl, VAL(1));
	ft_dll_push_back(dl, VAL(2));
	ft_dll_push_back(dl, VAL(3));

	/* insert at index 1: [1, 99, 2, 3] */
	t_check("insert_1_ok", ft_dll_insert(dl, 1, VAL(99)) == true);
	t_check_int("size_after_insert", (long)ft_dll_size(dl), 4);
	t_check_int("get_0_after_ins", INT(ft_dll_get(dl, 0)), 1);
	t_check_int("get_1_after_ins", INT(ft_dll_get(dl, 1)), 99);
	t_check_int("get_2_after_ins", INT(ft_dll_get(dl, 2)), 2);
	t_check_int("get_3_after_ins", INT(ft_dll_get(dl, 3)), 3);

	/* insert at 0 (new head): [77, 1, 99, 2, 3] */
	ft_dll_insert(dl, 0, VAL(77));
	t_check_int("head_after_insert0", INT(ft_dll_front(dl)), 77);

	/* insert at end (size): [77, 1, 99, 2, 3, 55] */
	ft_dll_insert(dl, ft_dll_size(dl), VAL(55));
	t_check_int("tail_after_insert_end", INT(ft_dll_back(dl)), 55);
	t_check_int("size_after_all_inserts", (long)ft_dll_size(dl), 6);

	/* remove at index 1 (should return 1) */
	val = ft_dll_remove(dl, 1);
	t_check_int("removed_val", INT(val), 1);
	t_check_int("size_after_remove", (long)ft_dll_size(dl), 5);
	t_check_int("head_after_remove1", INT(ft_dll_front(dl)), 77);

	/* remove head (index 0) */
	val = ft_dll_remove(dl, 0);
	t_check_int("removed_head", INT(val), 77);
	t_check_int("size_after_rmhead", (long)ft_dll_size(dl), 4);

	ft_dll_destroy(dl);
}

/* ---- reverse ---- */
static void	test_reverse(void)
{
	t_doubly_list	*dl;
	int				i;

	dl = ft_dll_create();
	i = 0;
	while (i < 6)
	{
		ft_dll_push_back(dl, VAL(i));
		i++;
	}
	/* [0,1,2,3,4,5] */
	ft_dll_reverse(dl);
	/* [5,4,3,2,1,0] */
	t_check_int("rev_front", INT(ft_dll_front(dl)), 5);
	t_check_int("rev_back", INT(ft_dll_back(dl)), 0);
	t_check_int("rev_mid", INT(ft_dll_get(dl, 3)), 2);
	ft_dll_reverse(dl);
	/* back to [0,1,2,3,4,5] */
	t_check_int("re-rev_front", INT(ft_dll_front(dl)), 0);
	t_check_int("re-rev_back", INT(ft_dll_back(dl)), 5);
	ft_dll_destroy(dl);
}

/* ---- find / contains ---- */
static void	test_find_contains(void)
{
	t_doubly_list	*dl;

	dl = ft_dll_create();
	ft_dll_push_back(dl, VAL(10));
	ft_dll_push_back(dl, VAL(20));
	ft_dll_push_back(dl, VAL(30));

	t_check_int("find_10", (long)ft_dll_find(dl, VAL(10)), 0);
	t_check_int("find_20", (long)ft_dll_find(dl, VAL(20)), 1);
	t_check_int("find_30", (long)ft_dll_find(dl, VAL(30)), 2);
	t_check_int("find_miss", (long)ft_dll_find(dl, VAL(99)), -1);
	t_check("contains_20", ft_dll_contains(dl, VAL(20)) == true);
	t_check("not_contains_99", ft_dll_contains(dl, VAL(99)) == false);
	ft_dll_destroy(dl);
}

/* ---- stress: thousands of nodes, check sum invariant ---- */
static void	test_stress(void)
{
	t_doubly_list	*dl;
	t_dll_node		*cur;
	long			push_sum;
	long			walk_sum;
	int				i;
	int				v;

	t_reseed(0xABCD1234);
	dl = ft_dll_create();
	push_sum = 0;
	i = 0;
	while (i < 5000)
	{
		v = (int)(t_rand() % 10000);
		ft_dll_push_back(dl, VAL(v));
		push_sum += v;
		i++;
	}
	t_check_int("stress_size", (long)ft_dll_size(dl), 5000);

	/* walk forward via head/next and sum */
	walk_sum = 0;
	cur = dl->head;
	while (cur)
	{
		walk_sum += INT(cur->data);
		cur = cur->next;
	}
	t_check_int("stress_fwd_sum", walk_sum, push_sum);

	/* walk backward via tail/prev and sum */
	walk_sum = 0;
	cur = dl->tail;
	while (cur)
	{
		walk_sum += INT(cur->data);
		cur = cur->prev;
	}
	t_check_int("stress_bwd_sum", walk_sum, push_sum);

	/* clear -> refill small -> destroy */
	ft_dll_clear(dl);
	t_check_int("stress_clear_size", (long)ft_dll_size(dl), 0);
	i = 0;
	while (i < 10)
	{
		ft_dll_push_back(dl, VAL(i));
		i++;
	}
	t_check_int("refill_size", (long)ft_dll_size(dl), 10);
	ft_dll_destroy(dl);
}

/* ---- remove_data ---- */
static void	test_remove_data(void)
{
	t_doubly_list	*dl;

	dl = ft_dll_create();
	ft_dll_push_back(dl, VAL(7));
	ft_dll_push_back(dl, VAL(8));
	ft_dll_push_back(dl, VAL(9));

	t_check("rm_data_8", ft_dll_remove_data(dl, VAL(8)) == true);
	t_check_int("size_after_rm_data", (long)ft_dll_size(dl), 2);
	t_check("rm_data_miss", ft_dll_remove_data(dl, VAL(99)) == false);
	ft_dll_destroy(dl);
}

int	main(void)
{
	t_begin("dlist");
	t_reseed(0xDEAD4242);
	test_create_destroy_empty();
	test_push_order();
	test_pop();
	test_get_set();
	test_insert_remove();
	test_reverse();
	test_find_contains();
	test_remove_data();
	test_stress();
	return (t_end());
}
