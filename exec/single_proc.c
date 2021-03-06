/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:33:49 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/24 16:43:12 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	single_builtin(t_proc *proc, t_info *info)
{
	int		exit_flag;

	exit_flag = CONTINUE;
	if (redirect(proc->io_info))
		exit_flag = exec_builtin(proc, info);
	redirect_reset(proc->io_info, info);
	return (exit_flag);
}

int	single_proc(t_proc *proc, t_info *info)
{
	pid_t	pid;
	int		status;

	if (is_builtin(proc->cmd))
		return (single_builtin(proc, info));
	set_signal_in_cmd();
	pid = xfork();
	if (pid == 0)
	{
		if (!redirect(proc->io_info))
			exit(EXIT_FAILURE);
		ft_exec(proc->cmd, info);
	}
	set_signal_ignore();
	xwaitpid(pid, &status, 0);
	set_signal_in_read();
	if (WIFSIGNALED(status))
		g_exit_status = display_sig_info(WTERMSIG(status));
	else
		g_exit_status = WEXITSTATUS(status);
	return (CONTINUE);
}
