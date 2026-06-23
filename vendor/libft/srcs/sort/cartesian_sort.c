/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesian_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:13:35 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:32:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include "ds.h"

static t_sort_node	*create_nod(int value, int index)
{
	t_sort_node	*node;

	node = fn_malloc(sizeof(t_sort_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_sort_node	*insert_cartesian(t_sort_node *root, int value, int index)
{
	if (!root)
		return (create_nod(value, index));
	if (index < root->index)
	{
		if (value > root->value)
		{
			root->left = create_nod(value, index);
			root->left->right = root;
			return (root->left);
		}
		root->left = insert_cartesian(root->left, value, index);
	}
	else
		root->right = insert_cartesian(root->right, value, index);
	return (root);
}

static void	inorder_traversal(t_sort_node *root, int *result, int *idx)
{
	if (!root)
		return ;
	inorder_traversal(root->left, result, idx);
	result[(*idx)++] = root->value;
	inorder_traversal(root->right, result, idx);
}

static void	free_tree(t_sort_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	fn_free(root);
}

void	cartesian_sort(int *arr, int size)
{
	t_sort_node	*root;
	int			*result;
	int			i;
	int			idx;

	if (!arr || size <= 1)
		return ;
	root = NULL;
	result = fn_malloc(size * sizeof(int));
	if (!result)
		return ;
	i = -1;
	while (++i < size)
		root = insert_cartesian(root, arr[i], i);
	idx = 0;
	inorder_traversal(root, result, &idx);
	i = -1;
	while (++i < size)
		arr[i] = result[i];
	(fn_free(result), free_tree(root));
}
