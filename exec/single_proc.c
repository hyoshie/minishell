/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:33:49 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/15 13:33:52 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_cmd_handler(t_proc *proc, t_info *info)
{
	redirect_pipe(proc->io_info, info);
	redirect_reset(proc->io_info, info);
	return (0);
}

/* use WEXITSTATUS(status) for return*/
//need to think if you need to put is_no_cmd in fork
int	single_proc(t_proc *proc, t_info *info)
{
	pid_t	pid;
	pid_t	wpid;
	int		exit_flag;

	exit_flag = 0;
	if (is_no_cmd(proc))
		return (no_cmd_handler(proc, info));
	if (is_builtin(proc->cmd))
	{
		redirect_pipe(proc->io_info, info);
		exit_flag = exec_builtin(proc, info);
		redirect_reset(proc->io_info, info);
		return (exit_flag);
	}
	pid = xfork();
	if (pid == 0)
	{
		redirect_pipe(proc->io_info, info);
		if (ft_exec(proc->cmd, info) == -1)
			xperror("child");
	}
	wpid = waitpid(pid, NULL, 0);
	return (exit_flag);
}