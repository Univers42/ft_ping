/* ************************************************************************** */
/*   test_hash.c — hammers the hash table API; frees everything.              */
/*   Output is logical-only so libc and ft_malloc builds must match.          */
/*                                                                            */
/*   DESIGN NOTE: hash_set stores the caller's key pointer (no internal       */
/*   copy), so all keys must live at stable addresses for the lifetime of      */
/*   the entry.  This test heap-allocates every key with fn_malloc and frees  */
/*   them after hash_destroy.                                                 */
/* ************************************************************************** */

#include "libft_test.h"
#include "ds.h"
#include <stdio.h>
#include <string.h>

/* ---- key pool helpers ---------------------------------------------------- */

/* Allocate a key string via fn_malloc; caller owns it. */
static char	*make_key(unsigned int idx)
{
	char	buf[32];
	size_t	len;
	char	*key;

	snprintf(buf, sizeof(buf), "key_%010u", idx);
	len = strlen(buf);
	key = fn_malloc(len + 1);
	if (!key)
		return (NULL);
	memcpy(key, buf, len + 1);
	return (key);
}

/* ---- basic smoke tests --------------------------------------------------- */

static void	test_init_and_empty(void)
{
	t_hash	h;

	t_check("init_default", hash_init(&h, 0));
	t_check_int("empty_len", (long)h.len, 0);
	t_check("empty_get_null", hash_get(&h, "missing") == NULL);
	hash_destroy(&h, NULL);

	t_check("init_16", hash_init(&h, 16));
	t_check_int("init16_len", (long)h.len, 0);
	hash_destroy(&h, NULL);
}

static void	test_single_entry(void)
{
	t_hash	h;
	char	*k;
	int		val;

	val = 42;
	k = make_key(0);
	t_check("init_single", hash_init(&h, 8));
	t_check("set_single", hash_set(&h, k, &val));
	t_check_int("len_after_set", (long)h.len, 1);
	t_check("get_single", hash_get(&h, k) == &val);
	t_check("miss_before_del", hash_get(&h, "world") == NULL);
	hash_destroy(&h, NULL);
	fn_free(k);
}

static void	test_update_value(void)
{
	t_hash	h;
	char	*k;
	int		a;
	int		b;

	a = 1;
	b = 2;
	k = make_key(1);
	t_check("init_update", hash_init(&h, 16));
	t_check("set_a", hash_set(&h, k, &a));
	t_check("get_a", hash_get(&h, k) == &a);
	t_check("set_b", hash_set(&h, k, &b));
	t_check_int("len_after_update", (long)h.len, 1);
	t_check("get_b", hash_get(&h, k) == &b);
	hash_destroy(&h, NULL);
	fn_free(k);
}

static void	test_delete(void)
{
	t_hash	h;
	char	*k;
	int		v;
	void	*ret;

	v = 99;
	k = make_key(2);
	t_check("init_del", hash_init(&h, 16));
	t_check("set_del", hash_set(&h, k, &v));
	ret = hash_del(&h, k);
	t_check("del_returns_val", ret == &v);
	t_check_int("len_after_del", (long)h.len, 0);
	t_check("get_after_del_null", hash_get(&h, k) == NULL);
	t_check("del_absent_null", hash_del(&h, k) == NULL);
	hash_destroy(&h, NULL);
	fn_free(k);
}

/* ---- bulk insert + lookup ----------------------------------------------- */

#define BULK_N 500

static int	g_values[BULK_N];
static char	*g_keys[BULK_N];

static void	test_bulk_insert(void)
{
	t_hash	h;
	int		i;
	void	*got;
	long	hits;
	long	misses;
	char	*absentkey;

	t_reseed(0xDEADBEEF);
	t_check("init_bulk", hash_init(&h, 64));

	/* Insert BULK_N distinct keys. */
	i = 0;
	while (i < BULK_N)
	{
		g_values[i] = (int)t_rand();
		g_keys[i] = make_key((unsigned int)(i + 10000));
		t_check("bulk_set", hash_set(&h, g_keys[i], &g_values[i]));
		i++;
	}
	t_check_int("bulk_len", (long)h.len, BULK_N);

	/* Verify all keys exist with correct value. */
	hits = 0;
	i = 0;
	while (i < BULK_N)
	{
		got = hash_get(&h, g_keys[i]);
		if (got == &g_values[i])
			hits++;
		i++;
	}
	t_check_int("bulk_hits", hits, BULK_N);

	/* Verify absent keys return NULL. */
	misses = 0;
	i = 0;
	while (i < 50)
	{
		absentkey = make_key((unsigned int)(i + 90000));
		if (hash_get(&h, absentkey) == NULL)
			misses++;
		fn_free(absentkey);
		i++;
	}
	t_check_int("bulk_misses", misses, 50);

	hash_destroy(&h, NULL);
	i = 0;
	while (i < BULK_N)
		fn_free(g_keys[i++]);
}

/* ---- delete subset + re-verify ------------------------------------------ */

#define DEL_N 200

static int	g_del_values[DEL_N];
static char	*g_del_keys[DEL_N];

static void	test_delete_subset(void)
{
	t_hash		h;
	int			i;
	long		del_misses;
	long		keep_hits;

	t_reseed(0xCAFEBABE);
	t_check("init_delsub", hash_init(&h, 64));

	i = 0;
	while (i < DEL_N)
	{
		g_del_values[i] = (int)t_rand();
		g_del_keys[i] = make_key((unsigned int)(i + 20000));
		hash_set(&h, g_del_keys[i], &g_del_values[i]);
		i++;
	}

	/* Delete every other key (even indices). */
	i = 0;
	while (i < DEL_N)
	{
		if ((i & 1) == 0)
			hash_del(&h, g_del_keys[i]);
		i++;
	}
	t_check_int("len_after_partial_del", (long)h.len, DEL_N / 2);

	/* Deleted keys must return NULL. */
	del_misses = 0;
	i = 0;
	while (i < DEL_N)
	{
		if ((i & 1) == 0 && hash_get(&h, g_del_keys[i]) == NULL)
			del_misses++;
		i++;
	}
	t_check_int("deleted_are_gone", del_misses, DEL_N / 2);

	/* Kept keys (odd indices) must still be present. */
	keep_hits = 0;
	i = 0;
	while (i < DEL_N)
	{
		if ((i & 1) == 1 && hash_get(&h, g_del_keys[i]) == &g_del_values[i])
			keep_hits++;
		i++;
	}
	t_check_int("kept_keys_still_hit", keep_hits, DEL_N / 2);

	hash_destroy(&h, NULL);
	i = 0;
	while (i < DEL_N)
		fn_free(g_del_keys[i++]);
}

/* ---- forced resize ------------------------------------------------------- */

#define RESIZE_N 128

static int	g_resize_values[RESIZE_N];
static char	*g_resize_keys[RESIZE_N];

static void	test_forced_resize(void)
{
	t_hash	h;
	int		i;
	long	hits;

	t_reseed(0x13131313);
	t_check("init_tiny", hash_init(&h, 4));

	i = 0;
	while (i < RESIZE_N)
	{
		g_resize_values[i] = (int)t_rand();
		g_resize_keys[i] = make_key((unsigned int)(i + 30000));
		t_check("resize_set", hash_set(&h, g_resize_keys[i], &g_resize_values[i]));
		i++;
	}
	t_check_int("resize_len", (long)h.len, RESIZE_N);

	hits = 0;
	i = 0;
	while (i < RESIZE_N)
	{
		if (hash_get(&h, g_resize_keys[i]) == &g_resize_values[i])
			hits++;
		i++;
	}
	t_check_int("resize_hits", hits, RESIZE_N);

	hash_destroy(&h, NULL);
	i = 0;
	while (i < RESIZE_N)
		fn_free(g_resize_keys[i++]);
}

/* ---- collision stress: small capacity forces collisions ------------------ */

static void	test_collision_keys(void)
{
	t_hash	h;
	char	*k0;
	char	*k1;
	char	*k2;
	int		v0;
	int		v1;
	int		v2;

	v0 = 100;
	v1 = 200;
	v2 = 300;

	k0 = make_key(40000);
	k1 = make_key(40001);
	k2 = make_key(40002);

	/* Use capacity 4 to maximise collisions. */
	t_check("init_coll", hash_init(&h, 4));

	t_check("coll_set0", hash_set(&h, k0, &v0));
	t_check("coll_set1", hash_set(&h, k1, &v1));
	/* k2 will trigger a resize (len >= cap/2) */
	t_check("coll_set2", hash_set(&h, k2, &v2));

	t_check("coll_get0", hash_get(&h, k0) == &v0);
	t_check("coll_get1", hash_get(&h, k1) == &v1);
	t_check("coll_get2", hash_get(&h, k2) == &v2);

	hash_destroy(&h, NULL);
	fn_free(k0);
	fn_free(k1);
	fn_free(k2);
}

/* ---- tombstone reinsert -------------------------------------------------- */

static void	test_tombstone_reinsert(void)
{
	t_hash	h;
	char	*k;
	int		v1;
	int		v2;

	v1 = 7;
	v2 = 8;
	k = make_key(50000);

	t_check("init_tomb", hash_init(&h, 16));
	t_check("tomb_set1", hash_set(&h, k, &v1));
	hash_del(&h, k);
	t_check("tomb_miss", hash_get(&h, k) == NULL);
	/* Re-insert same key after tombstone */
	t_check("tomb_set2", hash_set(&h, k, &v2));
	t_check("tomb_reinsert", hash_get(&h, k) == &v2);
	hash_destroy(&h, NULL);
	fn_free(k);
}

/* ---- destroy with free_val callback ------------------------------------- */

static int	g_free_count = 0;

static void	count_free(void *p)
{
	(void)p;
	g_free_count++;
}

#define CB_N 16

static int	g_cb_values[CB_N];
static char	*g_cb_keys[CB_N];

static void	test_destroy_callback(void)
{
	t_hash	h;
	int		i;

	g_free_count = 0;
	t_check("init_cb", hash_init(&h, 32));

	i = 0;
	while (i < CB_N)
	{
		g_cb_values[i] = i;
		g_cb_keys[i] = make_key((unsigned int)(i + 60000));
		hash_set(&h, g_cb_keys[i], &g_cb_values[i]);
		i++;
	}
	/* Delete first 4 — callback must NOT fire for tombstoned slots. */
	i = 0;
	while (i < 4)
	{
		hash_del(&h, g_cb_keys[i]);
		i++;
	}
	/* 16 inserted - 4 deleted = 12 live; destroy should call callback 12 times. */
	hash_destroy(&h, count_free);
	t_check_int("destroy_cb_count", (long)g_free_count, CB_N - 4);

	i = 0;
	while (i < CB_N)
		fn_free(g_cb_keys[i++]);
}

/* ---- round-trip value check on static keys ----------------------------- */

static const char	*g_static_keys[] = {
	"alpha", "bravo", "charlie", "delta", "echo",
	"foxtrot", "golf", "hotel", "india", "juliet",
	NULL
};

static void	test_static_keys_roundtrip(void)
{
	t_hash	h;
	int		vals[10];
	int		i;
	long	hits;

	t_reseed(0x55AA55AA);
	t_check("init_static", hash_init(&h, 16));

	i = 0;
	while (g_static_keys[i] != NULL)
	{
		vals[i] = (int)t_rand();
		t_check("static_set", hash_set(&h, g_static_keys[i], &vals[i]));
		i++;
	}

	hits = 0;
	i = 0;
	while (g_static_keys[i] != NULL)
	{
		if (hash_get(&h, g_static_keys[i]) == &vals[i])
			hits++;
		i++;
	}
	t_check_int("static_hits", hits, 10);

	/* Absent key. */
	t_check("static_miss", hash_get(&h, "zulu") == NULL);

	hash_destroy(&h, NULL);
}

int	main(void)
{
	t_begin("hash");
	t_reseed(0xABCD1234);
	test_init_and_empty();
	test_single_entry();
	test_update_value();
	test_delete();
	test_bulk_insert();
	test_delete_subset();
	test_forced_resize();
	test_collision_keys();
	test_tombstone_reinsert();
	test_destroy_callback();
	test_static_keys_roundtrip();
	return (t_end());
}
