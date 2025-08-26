/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:10:00 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/26 14:10:07 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd error");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_change_directory(t_dat *data, size_t k)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (data->xln[k + 1] == NULL || ft_strcmp(data->xln[k + 1], "~") == 0)
	{
		path = ft_get_val_from_list(data->ev, "HOME");
		if (path == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else
		path = data->xln[k + 1];
	if (chdir(path) == 0)
		ft_update_directories(data, oldpwd);
	else
		ft_cd_error(path);
}

void	ft_echo(char **arr, size_t k)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (arr[k + i] != NULL && ft_strncmp(arr[k + i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (arr[k + i] != NULL)
	{
		printf("%s", arr[k + i]);
		i++;
		if (arr[k + i] != NULL)
			printf(" ");
	}
	if (newline)
		printf("\n");
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int	ft_handle_builtin(t_dat *data, size_t k)
{
	if (data == NULL || data->xln == NULL)
		return (0);
	if (ft_strcmp(data->xln[k], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->xln[k], "cd") == 0)
		ft_change_directory(data, k);
	else if (ft_strcmp(data->xln[k], "echo") == 0)
		ft_echo(data->xln, k);
	else if (ft_strcmp(data->xln[k], "exit") == 0)
		ft_exit(data, k);
	else if (ft_strcmp(data->xln[k], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->xln[k], "unset") == 0)
		ft_unset_multi_var(data, k);
	else if (ft_strcmp(data->xln[k], "export") == 0)
		ft_export_multi_var(data, k);
	else
		return (0);
	return (1);
}
