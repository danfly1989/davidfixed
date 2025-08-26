/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagwu <dagwu@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:44:41 by dagwu             #+#    #+#             */
/*   Updated: 2025/06/14 18:44:46 by dagwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_val_from_list(t_va *head, const char *key)
{
	t_va	*cur;
	size_t	len;

	if (!head || !key)
		return (NULL);
	len = ft_strlen(key);
	cur = head;
	while (cur)
	{
		if (ft_strncmp(cur->name, key, len + 1) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

void	ft_update_directories(t_dat *data, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	ft_update_env_variable(data, "OLDPWD", oldpwd);
	ft_update_env_variable(data, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
}

t_va	*ft_remove_variable_node(const char *key, t_va *head, t_va *prev)
{
	t_va	*cur;
	t_va	*next;

	cur = head;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->name, key, ft_strlen(key)) == 0)
		{
			next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			if (prev == NULL)
				head = next;
			else
				prev->next = next;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (head);
}

void	ft_external_functions(t_dat *data, char *line)
{
	char	***cmd;
	int		n;

	(void)line;
	if (!data || !data->xln || !data->xln[0])
		return ;
	if (!ft_validate_syntax(data->xln))
		return ;
	ft_list_to_env_array(data);
	n = ft_count_pipes(data->xln);
	if (n > 0)
	{
		cmd = ft_parse_cmd(data, 0, 0, 0);
		if (!cmd)
			return ;
		ft_execute_pipeline(data, cmd);
		ft_clean_cmd(cmd);
	}
	else
		ft_ex_single_cmd(data, NULL);
	ft_free_string_array(data->evs);
}

int	**init_fd_array(int tot)
{
	int	**fd;
	int	i;

	fd = malloc(sizeof(int *) * tot);
	if (!fd)
		return (NULL);
	i = 0;
	while (i < tot - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			while (--i >= 0)
				free(fd[i]);
			free(fd);
			return (NULL);
		}
		i++;
	}
	fd[tot - 1] = NULL;
	return (fd);
}
