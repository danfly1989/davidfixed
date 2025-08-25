/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:55:08 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 18:55:57 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_main_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_parent_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_child_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_set_main_nested_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_nested_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_no_pipe_child_signals(t_dat *d)
{
	if (ft_strcmp(d->xln[0], "./minishell") == 0)
		ft_set_main_nested_signals();
	else
		ft_set_child_signals();
}

void	ft_set_heredoc_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = ft_heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_DFL);
}