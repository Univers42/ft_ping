/* ************************************************************************** */
/*   test_clist.c — hard tests for circular linked list (ft_circular_list.h) */
/*   Node content is an integer cast to (void*); no content heap is needed.  */
/*   ft_cl_destroy / ft_cl_clear free only the node structs.                 */
/* ************************************************************************** */

#include "libft_test.h"

#define VAL(n)  ((void *)(intptr_t)(n))
#define INT(p)  ((int)(intptr_t)(p))

/* ---- create / destroy empty ---- */
static void	test_create_destroy_empty(void)
{
	t_circular_list	*cl;

	cl = ft_cl_create();
	t_check_nonnull("cl_create", cl);
	t_check("cl_empty_true", ft_cl_is_empty(cl) == true);
	t_check_int("cl_size_0", (long)ft_cl_size(cl), 0);
	t_check("cl_front_null", ft_cl_front(cl) == NULL);
	t_check("cl_back_null", ft_cl_back(cl) == NULL);
	ft_cl_destroy(cl);
}

/* ---- push front/back and circular invariant (last->next == first) ---- */
static void	test_push_and_circular_invariant(void)
{
	t_circular_list	*cl;
	int				i;

	cl = ft_cl_create();

	/* push_back 0..9 */
	i = 0;
	while (i < 10)
	{
		t_check("push_back_ok", ft_cl_push_back(cl, VAL(i)) == true);
		i++;
	}
	t_check_int("size_10", (long)ft_cl_size(cl), 10);
	t_check_int("front_0", INT(ft_cl_front(cl)), 0);
	t_check_int("back_9", INT(ft_cl_back(cl)), 9);

	/* circular invariant: last->next is first */
	t_check("circular_inv", INT(cl->last->next->data) == INT(ft_cl_front(cl)));

	ft_cl_clear(cl);
	t_check_int("size_after_clear", (long)ft_cl_size(cl), 0);
	t_check("empty_after_clear", ft_cl_is_empty(cl) == true);

	/* push_front 0..9: front=9, back=0 */
	i = 0;
	while (i < 10)
	{
		ft_cl_push_front(cl, VAL(i));
		i++;
	}
	t_check_int("front_front9", INT(ft_cl_front(cl)), 9);
	t_check_int("back_front0", INT(ft_cl_back(cl)), 0);
	t_check("circular_inv2", INT(cl->last->next->data) == INT(ft_cl_front(cl)));
	ft_cl_destroy(cl);
}

/* ---- pop_front / pop_back ---- */
static void	test_pop(void)
{
	t_circular_list	*cl;

	cl = ft_cl_create();
	ft_cl_push_back(cl, VAL(1));
	ft_cl_push_back(cl, VAL(2));
	ft_cl_push_back(cl, VAL(3));
	ft_cl_push_back(cl, VAL(4));
	ft_cl_push_back(cl, VAL(5));

	t_check_int("pop_front_1", INT(ft_cl_pop_front(cl)), 1);
	t_check_int("pop_front_2", INT(ft_cl_pop_front(cl)), 2);
	t_check_int("size_after_pf", (long)ft_cl_size(cl), 3);

	t_check_int("pop_back_5", INT(ft_cl_pop_back(cl)), 5);
	t_check_int("pop_back_4", INT(ft_cl_pop_back(cl)), 4);
	t_check_int("size_after_pb", (long)ft_cl_size(cl), 1);
	t_check_int("last_elem", INT(ft_cl_front(cl)), 3);

	/* pop last element */
	t_check_int("pop_last_front", INT(ft_cl_pop_front(cl)), 3);
	t_check_int("size_0", (long)ft_cl_size(cl), 0);
	t_check("empty_after_pop_all", ft_cl_is_empty(cl) == true);

	/* pop on empty => NULL */
	t_check("pop_front_empty_null", ft_cl_pop_front(cl) == NULL);
	t_check("pop_back_empty_null", ft_cl_pop_back(cl) == NULL);

	ft_cl_destroy(cl);
}

/* ---- get / set ---- */
static void	test_get_set(void)
{
	t_circular_list	*cl;
	int				i;

	cl = ft_cl_create();
	i = 0;
	while (i < 8)
	{
		ft_cl_push_back(cl, VAL(i * 5));
		i++;
	}
	t_check_int("get_0", INT(ft_cl_get(cl, 0)), 0);
	t_check_int("get_3", INT(ft_cl_get(cl, 3)), 15);
	t_check_int("get_7", INT(ft_cl_get(cl, 7)), 35);
	t_check("get_oob_null", ft_cl_get(cl, 8) == NULL);

	t_check("set_3_ok", ft_cl_set(cl, 3, VAL(999)) == true);
	t_check_int("get_3_new", INT(ft_cl_get(cl, 3)), 999);
	t_check("set_oob_fail", ft_cl_set(cl, 100, VAL(0)) == false);

	ft_cl_destroy(cl);
}

/* ---- insert / remove ---- */
static void	test_insert_remove(void)
{
	t_circular_list	*cl;
	void			*val;

	cl = ft_cl_create();
	ft_cl_push_back(cl, VAL(10));
	ft_cl_push_back(cl, VAL(20));
	ft_cl_push_back(cl, VAL(30));

	/* insert at index 1: [10, 55, 20, 30] */
	t_check("insert_1_ok", ft_cl_insert(cl, 1, VAL(55)) == true);
	t_check_int("size_after_ins", (long)ft_cl_size(cl), 4);
	t_check_int("get_1_ins", INT(ft_cl_get(cl, 1)), 55);
	t_check_int("get_2_ins", INT(ft_cl_get(cl, 2)), 20);

	/* insert at 0: [77, 10, 55, 20, 30] */
	ft_cl_insert(cl, 0, VAL(77));
	t_check_int("front_after_ins0", INT(ft_cl_front(cl)), 77);

	/* insert at end */
	ft_cl_insert(cl, ft_cl_size(cl), VAL(99));
	t_check_int("back_after_ins_end", INT(ft_cl_back(cl)), 99);
	t_check_int("size_all_ins", (long)ft_cl_size(cl), 6);

	/* remove at index 1 */
	val = ft_cl_remove(cl, 1);
	t_check_int("removed_1", INT(val), 10);
	t_check_int("size_after_rm", (long)ft_cl_size(cl), 5);

	/* remove head (index 0) */
	val = ft_cl_remove(cl, 0);
	t_check_int("removed_head", INT(val), 77);

	/* circular invariant after mutation */
	t_check("circular_inv_after_mut",
		INT(cl->last->next->data) == INT(ft_cl_front(cl)));

	ft_cl_destroy(cl);
}

/* ---- rotate forward / backward ---- */
static void	test_rotate(void)
{
	t_circular_list	*cl;
	int				i;

	cl = ft_cl_create();
	i = 0;
	while (i < 5)
	{
		ft_cl_push_back(cl, VAL(i));
		i++;
	}
	/* [0,1,2,3,4], last->next==0 */
	/* rotate_forward 2 steps: last advances 2 => new front is 2 */
	ft_cl_rotate_forward(cl, 2);
	t_check_int("rot_fwd2_front", INT(ft_cl_front(cl)), 2);
	t_check_int("rot_fwd2_back", INT(ft_cl_back(cl)), 1);

	/* rotate_backward 1 step: last retreats 1 => front goes back 1 */
	ft_cl_rotate_backward(cl, 1);
	t_check_int("rot_bwd1_front", INT(ft_cl_front(cl)), 1);

	/* rotate by full size = noop */
	ft_cl_rotate_forward(cl, 5);
	t_check_int("rot_full_front_unchanged", INT(ft_cl_front(cl)), 1);

	/* circular invariant still holds */
	t_check("circular_inv_rot",
		INT(cl->last->next->data) == INT(ft_cl_front(cl)));

	ft_cl_destroy(cl);
}

/* ---- find / contains ---- */
static void	test_find_contains(void)
{
	t_circular_list	*cl;

	cl = ft_cl_create();
	ft_cl_push_back(cl, VAL(100));
	ft_cl_push_back(cl, VAL(200));
	ft_cl_push_back(cl, VAL(300));

	t_check_int("find_100", (long)ft_cl_find(cl, VAL(100)), 0);
	t_check_int("find_200", (long)ft_cl_find(cl, VAL(200)), 1);
	t_check_int("find_300", (long)ft_cl_find(cl, VAL(300)), 2);
	t_check_int("find_miss", (long)ft_cl_find(cl, VAL(999)), -1);
	t_check("contains_200", ft_cl_contains(cl, VAL(200)) == true);
	t_check("not_contains_999", ft_cl_contains(cl, VAL(999)) == false);
	ft_cl_destroy(cl);
}

/* ---- stress ---- */
static void	test_stress(void)
{
	t_circular_list	*cl;
	t_cl_node		*cur;
	long			push_sum;
	long			walk_sum;
	size_t			sz;
	size_t			idx;
	int				i;
	int				v;

	t_reseed(0x1234ABCD);
	cl = ft_cl_create();
	push_sum = 0;
	i = 0;
	while (i < 4000)
	{
		v = (int)(t_rand() % 10000);
		ft_cl_push_back(cl, VAL(v));
		push_sum += v;
		i++;
	}
	sz = ft_cl_size(cl);
	t_check_int("stress_size", (long)sz, 4000);

	/* walk the ring exactly sz times starting from first node */
	walk_sum = 0;
	cur = cl->last->next;  /* first node */
	idx = 0;
	while (idx < sz)
	{
		walk_sum += INT(cur->data);
		cur = cur->next;
		idx++;
	}
	t_check_int("stress_sum", walk_sum, push_sum);

	/* verify ring closes: after sz steps we must be back at first */
	t_check("stress_ring_closed", cur == cl->last->next);

	/* clear -> refill small -> destroy */
	ft_cl_clear(cl);
	t_check_int("stress_clear_size", (long)ft_cl_size(cl), 0);
	i = 0;
	while (i < 7)
	{
		ft_cl_push_back(cl, VAL(i * 3));
		i++;
	}
	t_check_int("refill_size", (long)ft_cl_size(cl), 7);
	t_check_int("refill_front", INT(ft_cl_front(cl)), 0);
	t_check_int("refill_back", INT(ft_cl_back(cl)), 18);
	ft_cl_destroy(cl);
}

/* ---- remove_data ---- */
static void	test_remove_data(void)
{
	t_circular_list	*cl;

	cl = ft_cl_create();
	ft_cl_push_back(cl, VAL(5));
	ft_cl_push_back(cl, VAL(6));
	ft_cl_push_back(cl, VAL(7));

	t_check("rm_data_6", ft_cl_remove_data(cl, VAL(6)) == true);
	t_check_int("size_after_rm_data", (long)ft_cl_size(cl), 2);
	t_check("rm_data_miss", ft_cl_remove_data(cl, VAL(99)) == false);
	/* circular invariant */
	t_check("circ_inv_after_rmd",
		INT(cl->last->next->data) == INT(ft_cl_front(cl)));
	ft_cl_destroy(cl);
}

int	main(void)
{
	t_begin("clist");
	t_reseed(0xC1C1C1C1);
	test_create_destroy_empty();
	test_push_and_circular_invariant();
	test_pop();
	test_get_set();
	test_insert_remove();
	test_rotate();
	test_find_contains();
	test_remove_data();
	test_stress();
	return (t_end());
}
