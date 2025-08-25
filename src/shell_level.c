/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:49:59 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 18:50:11 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increment_shlvl(t_va **env_list)
{
	t_va	*node;
	t_va	*new;
	int		level;

	node = *env_list;
	while (node)
	{
		if (ft_strcmp(node->name, "SHLVL") == 0)
		{
			level = ft_atoi(node->value) + 1;
			if (level < 1)
				level = 1;
			free(node->value);
			node->value = ft_itoa(level);
			return ;
		}
		node = node->next;
	}
	new = malloc(sizeof(t_va));
	if (!new)
		return ;
	new->name = ft_strdup("SHLVL");
	new->value = ft_itoa(1);
	new->next = *env_list;
	*env_list = new;
}

int	ft_create_shlvl(t_va **env_list)
{
	t_va	*new_node;

	new_node = malloc(sizeof(t_va));
	if (!new_node)
		return (0);
	new_node->name = ft_strdup("SHLVL");
	new_node->value = ft_itoa(1);
	if (!new_node->name || !new_node->value)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (0);
	}
	new_node->next = *env_list;
	*env_list = new_node;
	return (1);
}
