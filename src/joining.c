/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:53:57 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 19:54:07 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_exit_status(char *res, int status, int *i)
{
	char	*temp;

	temp = ft_itoa(status);
	res = ft_strjoin_free(res, temp);
	free(temp);
	*i += 2;
	return (res);
}

char	*append_char(char *res, char *token, int *i)
{
	char	*temp;

	temp = ft_substr(token, *i, 1);
	res = ft_strjoin_free(res, temp);
	free(temp);
	(*i)++;
	return (res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}