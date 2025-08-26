/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:33:24 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 14:33:30 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_error(char *path)
{
	char	*msg;

	msg = strerror(errno);
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_exit_numeric_error(char *arg)
{
	write(2, "minishell: exit: ", 18);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
}
