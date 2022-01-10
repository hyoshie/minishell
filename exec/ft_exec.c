/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:09:35 by yshimazu          #+#    #+#             */
/*   Updated: 2022/01/05 21:41:39 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	cmd_err(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(CMD_NOT_FINED);
}

static char	*path_from_env(char *cmd, char *envpath)
{
	char	*ret;
	char	**path_each;

	path_each = ms_xsplit(envpath, ':');
	if (*path_each == NULL)
		return (cmd);
	ret = search_executable(cmd, path_each);
	if (ret)
		return (ret);
	ret = search_binary(cmd, path_each);
	if (ret)
		return (ret);
	ft_splitfree(path_each);
	cmd_err(cmd);
	return (0);
}

static char	*get_path(char *cmd, char **cmd_array, t_info *info)
{
	char		*envpath;

	envpath = mini_getenv("PATH", info);
	if (envpath == NULL || ft_strchr(cmd_array[0], '/'))
	{
		xdir_check(cmd);
		return (cmd_array[0]);
	}
	else
		return (path_from_env(cmd_array[0], envpath));
}

static void	handle_execve_error(char *path)
{
	int	status;

	if (errno == ENOENT)
		status = CMD_NOT_FINED;
	else
		status = EXEC_FAIL;
	if (errno == ENOEXEC && !is_executable(path))
		errno = EACCES;
	if (errno == ENOEXEC)
	{
		free (path);
		exit(EXIT_SUCCESS);
	}
	print_error(strerror(errno), path);
	free (path);
	exit(status);
}

void	ft_exec(char **cmd, t_info *info)
{
	char	*path;
	char	**environ;

	if (!cmd[0])
		exit (0);
	if (!cmd[0][0] || ft_strcmp(cmd[0], ".") == 0 ||
		ft_strcmp(cmd[0], "..") == 0)
	{
		cmd_err(cmd[0]);
		return ;
	}
	environ = xdict_to_array(info->env, "=");
	path = get_path(cmd[0], cmd, info);
	if (execve(path, cmd, environ) == -1)
		handle_execve_error(path);
}
