/* ************************************************************************** */
/*   test_queue.c — hard tests for the FIFO queue (ft_queue.h API).          */
/*   Node data is an integer cast to (void*). No heap content; nodes freed   */
/*   by ft_queue_destroy / ft_queue_clear.                                   */
/* ************************************************************************** */

#include "libft_test.h"

#define VAL(n)  ((void *)(intptr_t)(n))
#define INT(p)  ((int)(intptr_t)(p))

/* ---- basics ---- */
static void	test_create_destroy_empty(void)
{
	t_queue	*q;

	q = ft_queue_create();
	t_check_nonnull("queue_create", q);
	t_check("queue_empty_true", ft_queue_is_empty(q) == true);
	t_check_int("queue_size_0", (long)ft_queue_size(q), 0);
	t_check("queue_front_null", ft_queue_front(q) == NULL);
	t_check("queue_rear_null", ft_queue_rear(q) == NULL);
	ft_queue_destroy(q);
}

/* ---- enqueue / dequeue FIFO order (small) ---- */
static void	test_fifo_small(void)
{
	t_queue	*q;
	int		i;

	q = ft_queue_create();
	i = 0;
	while (i < 5)
	{
		t_check("enqueue_ok", ft_queue_enqueue(q, VAL(i)) == true);
		i++;
	}
	t_check_int("size_after_enq5", (long)ft_queue_size(q), 5);
	t_check_int("front_0", INT(ft_queue_front(q)), 0);
	t_check_int("rear_4", INT(ft_queue_rear(q)), 4);

	/* dequeue in FIFO order: 0,1,2,3,4 */
	t_check_int("deq_0", INT(ft_queue_dequeue(q)), 0);
	t_check_int("deq_1", INT(ft_queue_dequeue(q)), 1);
	t_check_int("deq_2", INT(ft_queue_dequeue(q)), 2);
	t_check_int("deq_3", INT(ft_queue_dequeue(q)), 3);
	t_check_int("deq_4", INT(ft_queue_dequeue(q)), 4);
	t_check_int("size_0_after_drain", (long)ft_queue_size(q), 0);
	t_check("empty_after_drain", ft_queue_is_empty(q) == true);

	/* dequeue on empty must return NULL */
	t_check("deq_empty_null", ft_queue_dequeue(q) == NULL);
	ft_queue_destroy(q);
}

/* ---- front / rear peek during partial dequeue ---- */
static void	test_front_rear_peek(void)
{
	t_queue	*q;

	q = ft_queue_create();
	ft_queue_enqueue(q, VAL(10));
	ft_queue_enqueue(q, VAL(20));
	ft_queue_enqueue(q, VAL(30));

	t_check_int("peek_front", INT(ft_queue_front(q)), 10);
	t_check_int("peek_rear", INT(ft_queue_rear(q)), 30);

	/* dequeue one: front moves to 20, rear stays 30 */
	ft_queue_dequeue(q);
	t_check_int("front_after_deq1", INT(ft_queue_front(q)), 20);
	t_check_int("rear_after_deq1", INT(ft_queue_rear(q)), 30);

	ft_queue_destroy(q);
}

/* ---- queue_clear then refill ---- */
static void	test_clear_refill(void)
{
	t_queue	*q;
	int		i;

	q = ft_queue_create();
	i = 0;
	while (i < 100)
	{
		ft_queue_enqueue(q, VAL(i));
		i++;
	}
	t_check_int("size_before_clear", (long)ft_queue_size(q), 100);

	ft_queue_clear(q);
	t_check_int("size_after_clear", (long)ft_queue_size(q), 0);
	t_check("empty_after_clear", ft_queue_is_empty(q) == true);
	t_check("front_null_after_clear", ft_queue_front(q) == NULL);
	t_check("rear_null_after_clear", ft_queue_rear(q) == NULL);

	/* refill */
	i = 0;
	while (i < 5)
	{
		ft_queue_enqueue(q, VAL(i * 2));
		i++;
	}
	t_check_int("refill_size", (long)ft_queue_size(q), 5);
	t_check_int("refill_front", INT(ft_queue_front(q)), 0);
	t_check_int("refill_rear", INT(ft_queue_rear(q)), 8);

	ft_queue_destroy(q);
}

/* ---- FIFO stress: 10000 items, verify dequeue order == enqueue order ---- */
static void	test_fifo_stress(void)
{
	t_queue			*q;
	unsigned int	enq_vals[10000];
	int				i;
	unsigned int	got;
	int				mismatch;

	t_reseed(0xF1F0F1F0);
	q = ft_queue_create();
	i = 0;
	while (i < 10000)
	{
		enq_vals[i] = t_rand() % 100000;
		ft_queue_enqueue(q, VAL((int)enq_vals[i]));
		i++;
	}
	t_check_int("stress_size", (long)ft_queue_size(q), 10000);

	/* dequeue and verify order */
	mismatch = 0;
	i = 0;
	while (i < 10000)
	{
		got = (unsigned int)INT(ft_queue_dequeue(q));
		if (got != enq_vals[i])
			mismatch++;
		i++;
	}
	t_check_int("stress_fifo_mismatches", mismatch, 0);
	t_check_int("stress_empty_after_drain", (long)ft_queue_size(q), 0);
	t_check("stress_is_empty", ft_queue_is_empty(q) == true);

	ft_queue_destroy(q);
}

/* ---- interleaved enqueue/dequeue: sliding window invariant ---- */
static void	test_interleaved(void)
{
	t_queue		*q;
	long		enqueued;
	long		dequeued_sum;
	long		expected_sum;
	int			window;
	int			i;
	int			v;

	t_reseed(0xBABECAFE);
	q = ft_queue_create();
	enqueued = 0;
	dequeued_sum = 0;
	expected_sum = 0;
	window = 0;

	i = 0;
	while (i < 2000)
	{
		/* enqueue a batch of 3 */
		v = (int)(t_rand() % 1000);
		ft_queue_enqueue(q, VAL(v));
		expected_sum += v;
		window++;
		v = (int)(t_rand() % 1000);
		ft_queue_enqueue(q, VAL(v));
		expected_sum += v;
		window++;
		v = (int)(t_rand() % 1000);
		ft_queue_enqueue(q, VAL(v));
		expected_sum += v;
		window++;
		enqueued += 3;

		/* dequeue 1 */
		dequeued_sum += INT(ft_queue_dequeue(q));
		window--;
		i++;
	}
	/* remaining: window items still in queue */
	t_check_int("interleaved_size", (long)ft_queue_size(q), (long)window);

	/* drain remaining and add to dequeued sum */
	while (!ft_queue_is_empty(q))
	{
		dequeued_sum += INT(ft_queue_dequeue(q));
		window--;
	}
	t_check_int("interleaved_window_0", window, 0);
	t_check_int("interleaved_sum", dequeued_sum, expected_sum);
	(void)enqueued;
	ft_queue_destroy(q);
}

/* ---- single-element edge cases ---- */
static void	test_single_elem(void)
{
	t_queue	*q;

	q = ft_queue_create();
	ft_queue_enqueue(q, VAL(42));
	t_check_int("single_size", (long)ft_queue_size(q), 1);
	t_check_int("single_front", INT(ft_queue_front(q)), 42);
	t_check_int("single_rear", INT(ft_queue_rear(q)), 42);
	t_check_int("single_deq", INT(ft_queue_dequeue(q)), 42);
	t_check_int("single_empty_size", (long)ft_queue_size(q), 0);
	t_check("single_empty", ft_queue_is_empty(q) == true);
	ft_queue_destroy(q);
}

int	main(void)
{
	t_begin("queue");
	t_reseed(0xCAFE0042);
	test_create_destroy_empty();
	test_fifo_small();
	test_front_rear_peek();
	test_clear_refill();
	test_single_elem();
	test_interleaved();
	test_fifo_stress();
	return (t_end());
}
