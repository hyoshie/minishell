/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:35:32 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/15 17:20:12 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "../utils/utils.h"
#include "../parser/parser.h"

#define PATHNAME_SIZE 512

int		exec_builtin(t_proc *proc, t_info *info);
bool	is_builtin(char **args);
int		exec_echo(char **args, t_info *info);
int		exec_export(char **args, t_info *info);
int		exec_unset(char **args, t_info *info);

#endif