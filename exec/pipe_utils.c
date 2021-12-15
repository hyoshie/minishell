/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:09:01 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/15 22:34:59 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pipes_close(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	redirect_reset(t_io *io_info, t_info *info)
{
	if (!is_redirect(io_info))
		return (0);
	xdup2(info->stdfd[SAVED_IN], STDIN_FILENO);
	xdup2(info->stdfd[SAVED_OUT], STDOUT_FILENO);
	xdup2(info->stdfd[SAVED_ERR], STDOUT_FILENO);
	return (0);
}

static void	xdup2_close(int fd1, int fd2)
{
	xdup2(fd1, fd2);
	close(fd1);
}

void	redirect_pipe(t_io *io_info, t_info *info)
{
	int	fd;

	if (!is_redirect(io_info))
		return ;
	while (io_info)
	{
		if (io_info->kind == OUT_REDIRECT)
		{
			fd = ft_open(io_info->word, OUT_REDIRECT);
			xdup2_close(fd, STDOUT_FILENO);
		}
		else if (io_info->kind == IN_REDIRECT)
		{
			fd = ft_open(io_info->word, IN_REDIRECT);
			xdup2_close(fd, STDIN_FILENO);
		}
		else if (io_info->kind == APPEND)
		{
			fd = ft_open(io_info->word, APPEND);
			xdup2_close(fd, STDOUT_FILENO);
		}
		else if (io_info->kind == HEREDOC)
			heredoc_handler(io_info, info);
		io_info = io_info->next;
	}
}
