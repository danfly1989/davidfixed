/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:52:18 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 19:52:28 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nested_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_parent_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_child_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	ft_heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}