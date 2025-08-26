/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:50:39 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 16:50:48 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork_children(t_dat *d, char ***cmd, int **fd)
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (i < d->tot)
	{
		pid = fork();
		if (pid == 0)
			ft_child_process(d, cmd, fd, i);
		else if (pid < 0)
			perror("fork");
		i++;
	}
}

void	ft_wait_children(t_dat *d, int tot)
{
	int	status;
	int	i;

	i = 0;
	while (i < tot)
	{
		wait(&status);
		if (WIFEXITED(status))
			d->last_exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	ft_child_process(t_dat *d, char ***cmd, int **fd, size_t i)
{
	t_rdr	r;
	int		len;

	len = 0;
	while (cmd[i][len])
		len++;
	ft_memset(&r, 0, sizeof(r));
	if (!ft_validate_segment(cmd[i], 0, len))
		exit(1);
	ft_setup_io(fd, i, d->tot);
	ft_close_pipes(fd, d->tot);
	ft_parse_redirection(cmd[i], &r);
	if (!ft_apply_redirections(&r, &cmd[i]))
		exit(1);
	ft_exec_command(d, cmd[i]);
}
