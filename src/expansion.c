/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:53:40 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 16:53:50 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_loop(char *token, t_dat *data, char **res, size_t *i)
{
	char	*key;
	char	*val;
	char	*tmp;

	key = ft_extract_var_key(token, i);
	if (!key)
		return ;
	val = NULL;
	if (data->lo != NULL)
		val = ft_get_var_value(data->lo, key);
	if (val == NULL)
		val = ft_get_var_value(data->ev, key);
	if (val != NULL)
	{
		tmp = *res;
		*res = ft_strjoin(*res, val);
		free(tmp);
	}
	free(key);
}

void	ft_check_var_assign_and_expand_line(t_dat *data, char *line)
{
	int	*quote_types;

	if (!data || !line)
		return ;
	data->ln = ft_tokenize_line(data, line, &quote_types);
	if (!data->ln)
		return ;
	data->xln = ft_expand_tokens(data, data->ln, quote_types, 0);
	if (!data->xln)
	{
		free(quote_types);
		return ;
	}
	ft_strip_quotes_from_xln(data);
	if (ft_all_valid_lvar(data, data->xln))
		ft_update_local_variables(data);
	ft_external_functions(data, line);
	free(quote_types);
}
