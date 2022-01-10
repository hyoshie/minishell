/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:22:20 by yshimazu          #+#    #+#             */
/*   Updated: 2022/01/06 14:15:13 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	update_pwd(char *current_path, char *dest_path, t_info *info)
{
	dict_update_value(ft_xstrdup("pwd"), \
		ft_xstrdup(dest_path), info->pwd);
	dict_update_value(ft_xstrdup("oldpwd"), \
		ft_xstrdup(current_path), info->pwd);
	dict_update_value(ft_xstrdup("PWD"), \
		ft_xstrdup(dest_path), info->env);
	dict_update_value(ft_xstrdup("OLDPWD"), \
		ft_xstrdup(current_path), info->env);
	g_exit_status = 0;
}

static bool	dot_handle(char *operand, char *current_path, t_info *info)
{
	char	*cwd;
	char	*update_path;

	if (ft_strcmp(operand, ".") == 0)
	{
		cwd = getcwd(0, 0);
		if (!cwd)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd("error retrieving current directory: ", STDERR_FILENO);
			perror("getcwd: cannot access parent directories");
			update_path = ft_xstrjoin(current_path, "/.");
			update_pwd(current_path, update_path, info);
			multi_free(operand, current_path, update_path, NULL);
			return (false);
		}
		else
			free(cwd);
	}
	return (true);
}

int	exec_cd(char **args, t_info *info)
{
	char	*current_path;
	char	*dest_path;
	char	*operand;
	t_clst	*path_clst;

	current_path = ft_xstrdup(dict_get_value("pwd", info->pwd));
	operand = set_cd_dest(args, info);
	if (!operand)
	{
		free(current_path);
		return (CONTINUE);
	}
	if (!dot_handle(operand, current_path, info))
		return (CONTINUE);
	path_clst = path_to_clst(current_path, operand);
	clst_del_content(path_clst, ".");
	del_before_dots(path_clst);
	dest_path = clst_to_line(path_clst);
	clst_clear(path_clst);
	if (chdir(operand) != 0)
		cd_perror(args[1]);
	else
		update_pwd(current_path, dest_path, info);
	multi_free(operand, current_path, dest_path, NULL);
	return (CONTINUE);
}
