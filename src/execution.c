/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:19:37 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 14:19:45 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ex_single_cmd(t_dat *d, char *cmd_path)
{
	pid_t	pid;
	t_rdr	r;

	if (ft_handle_builtin(d, d->st))
		return ;
	ft_set_no_pipe_child_signals(d);
	ft_parse_redirection(d->xln, &r);
	if (!ft_apply_sing_redirections(&r, d->xln))
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		cmd_path = ft_get_cmd_path(d, d->xln[0], 0);
		if (!cmd_path)
			ft_cmd_not_found(d->xln[0]);
		execve(cmd_path, d->xln, d->evs);
		exit(1);
	}
	else if (pid > 0)
		ft_get_exit_stat(d, pid);
	else
		perror("fork");
	ft_set_main_signals();
}

void	ft_exec_command(t_dat *d, char **cmd)
{
	char	*cmd_path;

	if (ft_is_builtin(cmd[0]))
	{
		ft_execute_builtin_in_child(d, cmd);
		exit(d->last_exit_status);
	}
	cmd_path = ft_get_cmd_path(d, cmd[0], 0);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, cmd, d->evs);
	free(cmd_path);
	perror("execve");
	exit(1);
}
