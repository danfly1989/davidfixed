/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:45:01 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 19:45:08 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_apply_sing_redirections(t_rdr *r, char **tok)
{
	if (r->in_file && !ft_redir_in(r->in_file))
		return (perror("minishell"), 0);
	if (r->out_file && !ft_redir_out(r->out_file))
		return (perror("minishell"), 0);
	if (r->append_file && !ft_redir_append(r->append_file))
		return (perror("minishell"), 0);
	if (r->heredoc_delim && !ft_handle_heredoc(r->heredoc_delim, NULL))
		return (perror("minishell"), 0);
	ft_free_redirection(r);
	return (ft_remove_sing_redirections(tok, 0, 0));
}

int	ft_apply_redirections(t_rdr *r, char ***cmd)
{
	if (r->in_file && !ft_redir_in(r->in_file))
		return (0);
	if (r->out_file && !ft_redir_out(r->out_file))
		return (0);
	if (r->append_file && !ft_redir_append(r->append_file))
		return (0);
	if (r->heredoc_delim && !ft_handle_heredoc(r->heredoc_delim, NULL))
		return (0);
	ft_free_redirection(r);
	return (ft_remove_redirections(cmd, 0, 0));
}

int	ft_remove_redirections(char ***tokens_ptr, int i, int j)
{
	char	**tokens;

	if (!tokens_ptr || !*tokens_ptr)
		return (0);
	tokens = *tokens_ptr;
	while (tokens[i])
	{
		if (ft_is_redirection(tokens[i]) && tokens[i + 1])
		{
			free(tokens[i]);
			free(tokens[i + 1]);
			j = i - 1;
			while (tokens[++j + 2])
				tokens[j] = tokens[j + 2];
			tokens[j] = NULL;
			tokens[j + 1] = NULL;
			continue ;
		}
		i++;
	}
	*tokens_ptr = tokens;
	return (1);
}

int	ft_remove_sing_redirections(char **t, int i, int j)
{
	if (!t)
		return (0);
	i = 0;
	while (t[i])
	{
		if (ft_is_redirection(t[i]) && t[i + 1])
		{
			free(t[i]);
			free(t[i + 1]);
			j = i;
			while (t[j + 2])
			{
				t[j] = t[j + 2];
				j++;
			}
			t[j] = NULL;
			t[j + 1] = NULL;
			continue ;
		}
		i++;
	}
	return (1);
}

int	ft_is_redirection(char *str)
{
	return (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") || !ft_strcmp(str,
			">>") || !ft_strcmp(str, "<<"));
}
