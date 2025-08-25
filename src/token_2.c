/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:00:09 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 20:00:18 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_token(char *token, t_dat *data, int qt, size_t i)
{
	char	*res;
	char	*tmp;

	if (qt == 1)
		return (ft_strdup(token));
	res = ft_calloc(1, sizeof(char));
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && (ft_isalpha(token[i + 1])
				|| token[i + 1] == '_' || token[i + 1] == '?'))
		{
			i++;
			ft_expand_loop(token, data, &res, &i);
		}
		else
		{
			tmp = res;
			res = ft_strjoin_char(res, token[i++]);
			free(tmp);
		}
	}
	return (res);
}

char	**ft_expand_tokens(t_dat *d, char **tokens, int *qtypes, int i)
{
	char **expanded;

	while (tokens[i])
		i++;
	expanded = malloc(sizeof(char *) * (i + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		d->tmp2 = ft_expand_exit_status(d, tokens[i]);
		expanded[i] = ft_expand_token(d->tmp2, d, qtypes[i], 0);
		free(d->tmp2);
		d->tmp2 = NULL;
		if (!expanded[i])
			return (ft_free_error_expanded(expanded, i));
		i++;
	}
	expanded[i] = NULL;
	return (expanded);
}