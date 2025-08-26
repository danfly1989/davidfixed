/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:57:09 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 13:57:17 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_value(t_va *list, const char *name)
{
	size_t	n;

	n = ft_strlen(name);
	while (list)
	{
		if (list->name && ft_strncmp(list->name, name, n) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

char	*ft_extract_var_key(const char *str, size_t *i)
{
	size_t	start;
	char	*key;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	return (key);
}

int	ft_update_existing_var(t_va *node, const char *name, const char *val)
{
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(name)) == 0)
		{
			free(node->value);
			node->value = ft_strdup(val);
			if (!node->value)
				perror("minishell: malloc error");
			return (1);
		}
		node = node->next;
	}
	return (0);
}
