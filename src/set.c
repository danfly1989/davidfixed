/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:53:05 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 17:53:15 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_io(int **fd, size_t i, size_t total)
{
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < total - 1)
		dup2(fd[i][1], STDOUT_FILENO);
}

void	ft_reset_iterators(t_dat *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->tot = 0;
	data->st = 0;
}

void	ft_unset_multi_var(t_dat *d, size_t k)
{
	int	i;

	i = 1;
	while (d->xln[k + i] != NULL)
	{
		d->ev = ft_remove_variable_node(d->xln[k + i], d->ev, NULL);
		d->lo = ft_remove_variable_node(d->xln[k + i], d->lo, NULL);
		i++;
	}
}

void	ft_unset_multi_var(t_dat *d, size_t k)
{
	int	i;

	i = 1;
	while (d->xln[k + i] != NULL)
	{
		d->ev = ft_remove_variable_node(d->xln[k + i], d->ev, NULL);
		d->lo = ft_remove_variable_node(d->xln[k + i], d->lo, NULL);
		i++;
	}
}
