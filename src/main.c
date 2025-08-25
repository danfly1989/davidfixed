/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:47:14 by daflynn           #+#    #+#             */
/*   Updated: 2025/08/25 18:47:19 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_dat	data;

	data = ft_duplicate_input_args(argc, argv, env);
	ft_set_main_signals();
	while (1)
	{
		line = readline("dandav>");
		if (line == NULL)
			break ;
		if (line && *line && !ft_strisspace(line))
			add_history(line);
		ft_check_var_assign_and_expand_line(&data, line);
		if (line)
			free(line);
		ft_free_string_array(data.ln);
		ft_free_string_array(data.xln);
		data.ln = NULL;
		data.xln = NULL;
	}
	ft_cleanup_data(&data);
	return (0);
}

t_dat	ft_duplicate_input_args(int argc, char **argv, char **env)
{
	t_dat	data;

	(void)argc;
	data.av = NULL;
	data.ev = NULL;
	data.lo = NULL;
	data.ln = NULL;
	data.xln = NULL;
	data.tmp1 = NULL;
	data.tmp2 = NULL;
	data.i = 0;
	data.j = 0;
	data.k = 0;
	data.tot = 0;
	data.st = 0;
	data.last_exit_status = 0;
	data.avs = NULL;
	data.evs = NULL;
	data.av = create_lst_frm_arr(argv + 1, NULL, 0, ft_create_node);
	data.ev = create_lst_frm_arr(env, NULL, 0, ft_create_var_node);
	ft_increment_shlvl(&data.ev);
	return (data);
}
