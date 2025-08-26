/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:51:04 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 19:51:10 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_var_name(char *str)
{
	char	*name;
	size_t	i;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_extract_var_value(char *str, char quote, size_t len)
{
	char	*val;
	size_t	i;

	if (!str || str[0] == '\0')
		return (NULL);
	if (str[0] == '"' || str[0] == '\'')
	{
		quote = str[0];
		str++;
	}
	while (str[len] && str[len] != quote)
		len++;
	val = malloc(len + 1);
	if (!val)
		return (NULL);
	i = -1;
	while (++i < len)
		val[i] = str[i];
	val[len] = '\0';
	return (val);
}
