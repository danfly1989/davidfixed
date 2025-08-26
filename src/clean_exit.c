/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:52:59 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 18:53:08 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanup_data(t_dat *data)
{
	if (data->ev != NULL)
		ft_free_list(data->ev);
	if (data->av != NULL)
		ft_free_list(data->av);
	if (data->lo != NULL)
		ft_free_list(data->lo);
	if (data->ln != NULL)
		ft_free_string_array(data->ln);
	if (data->xln != NULL)
		ft_free_string_array(data->xln);
	if (data->tmp1 != NULL)
		free(data->tmp1);
	if (data->tmp2 != NULL)
		free(data->tmp2);
}

void	ft_cleanup_exit(t_dat *data, int flag)
{
	ft_cleanup_data(data);
	rl_clear_history();
	exit(flag);
}

void	ft_free_list(t_va *head)
{
	t_va	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

char	*ft_expand_exit_status(t_dat *d, char *token)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?')
			res = append_exit_status(res, d->last_exit_status, &i);
		else
			res = append_char(res, token, &i);
	}
	return (res);
}

void	ft_exit(t_dat *data, size_t k)
{
	int	status;

	if (data->xln[k + 1] && data->xln[k + 2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	rl_clear_history();
	if (data->xln[k + 1] == NULL)
		ft_cleanup_exit(data, 0);
	if (ft_is_number(data->xln[k + 1]) == 0)
	{
		ft_exit_numeric_error(data->xln[k + 1]);
		ft_cleanup_exit(data, 255);
	}
	status = ft_atoi(data->xln[k + 1]);
	ft_cleanup_exit(data, status % 256);
}

void	ft_exit_numeric_error(char *arg)
{
	write(2, "minishell: exit: ", 18);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
}