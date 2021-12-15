/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:47:49 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/15 16:19:19 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	launch_shell(t_proc *proc, t_info *info)
{
	int	exit_flag;

	if (!proc)
		return (0);
	if (is_single_proc(proc))
		exit_flag = single_proc(proc, info);
	else
		exit_flag = exec_multi_procs(proc, info);
	return (exit_flag);
}

//need change the free(froc)
void	loop_shell(t_info *info)
{
	char	*line;
	bool	exit_flag;
	t_proc	*proc;

	exit_flag = 0;
	set_signal_in_read();
	while (!exit_flag)
	{
		printf("[%d]", info->exit_status);
		line = readline("minishell > ");
		if (line == NULL)
		{
			printf("Catch Ctrl-D\n");
			break ;
		}
		add_history(line);
		info->exit_status = parse_line(&proc, line);
		if (info->exit_status == EMPTY_LINE || info->exit_status == SYNTAX_ERR)
			continue ;
		exit_flag = launch_shell(proc, info);
		free(line);
		free(proc);
	}
	rl_clear_history();
}
