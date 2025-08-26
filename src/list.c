/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:40:22 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 14:40:29 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_va	*ft_merge_sorted_lists(t_va *a, t_va *b)
{
	t_va	*result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) <= 0)
	{
		result = a;
		result->next = ft_merge_sorted_lists(a->next, b);
	}
	else
	{
		result = b;
		result->next = ft_merge_sorted_lists(a, b->next);
	}
	return (result);
}

void	ft_split_list(t_va *source, t_va **front, t_va **back)
{
	t_va	*fast;
	t_va	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

void	ft_sort_list_by_name(t_va **head_ref)
{
	t_va	*head;
	t_va	*a;
	t_va	*b;

	if (*head_ref == NULL || (*head_ref)->next == NULL)
		return ;
	head = *head_ref;
	ft_split_list(head, &a, &b);
	ft_sort_list_by_name(&a);
	ft_sort_list_by_name(&b);
	*head_ref = ft_merge_sorted_lists(a, b);
}

int	ft_count_list(t_va *head)
{
	t_va	*cur;
	int		count;

	cur = head;
	count = 0;
	while (cur)
	{
		if (cur->name)
			count++;
		cur = cur->next;
	}
	return (count);
}

void	ft_list_to_env_array(t_dat *data)
{
	int		i;
	int		count;
	t_va	*cur;

	i = 0;
	data->tmp1 = NULL;
	count = ft_count_list(data->ev);
	data->evs = malloc((count + 1) * sizeof(char *));
	if (!data->evs)
		return ;
	cur = data->ev;
	while (cur && i < count)
	{
		data->tmp1 = ft_strjoin(cur->name, "=");
		data->evs[i] = ft_strjoin(data->tmp1, cur->value);
		free(data->tmp1);
		data->tmp1 = NULL;
		cur = cur->next;
		i++;
	}
	data->evs[i] = NULL;
}
