/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:45:11 by yshimazu          #+#    #+#             */
/*   Updated: 2022/01/05 21:07:52 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	xpath_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(cmd);
	g_exit_status = CMD_NOT_FINED;
	exit (CMD_NOT_FINED);
}

void	xdir_check(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		closedir(dir);
		g_exit_status = EXEC_FAIL;
		exit (EXEC_FAIL);
	}
}

bool	is_executable(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

char	*search_executable(char *cmd, char **path_each)
{
	int		i;
	char	*ret;

	i = -1;
	while (path_each[++i])
	{
		ret = ft_xtrijoin(path_each[i], "/", cmd);
		if (access(ret, X_OK) == 0)
		{
			ft_splitfree(path_each);
			return (ret);
		}
		free(ret);
	}
	return (NULL);
}

char	*search_binary(char *cmd, char **path_each)
{
	int		i;
	char	*ret;

	i = -1;
	while (path_each[++i])
	{
		ret = ft_xtrijoin(path_each[i], "/", cmd);
		if (access(ret, F_OK) == 0)
		{
			ft_splitfree(path_each);
			return (ret);
		}
		free(ret);
	}
	return (NULL);
}
