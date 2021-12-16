/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:02:31 by hyoshie           #+#    #+#             */
/*   Updated: 2021/12/16 17:53:24 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../lexer/lexer.h"
# include "../env/env.h"
# include "../libft/mylibft.h"

//expand_var.c
char	*append_nonvar(char *expanded, char *current, size_t len);
char	*append_var(char *str, char *value);
char	*fetch_value(char *prefix, size_t key_len, t_dict *env);
char	*expand_var(char *word, t_dict *env);
//expand_var_all.c
t_token	*expand_var_all(t_token *tokens, t_dict *env);
//utils.c
char	*search_prefix(char *word);
char	*ft_xstrjoin_free(char *str1, char *str2);

#endif /* EXPANDER_H */
