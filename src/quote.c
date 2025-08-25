/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:02:06 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 20:02:16 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}

void	ft_detect_quote_type(char *token, int *quote_type)
{
	char *eq;
	char quote;

	if (token[0] == '\'')
		*quote_type = 1;
	else if (token[0] == '"')
		*quote_type = 2;
	else
	{
		eq = ft_strchr(token, '=');
		if (eq && (*(eq + 1) == '\'' || *(eq + 1) == '"'))
		{
			quote = *(eq + 1);
			if (quote == '\'')
				*quote_type = 1;
			else
				*quote_type = 2;
		}
	}
}