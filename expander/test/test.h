/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:28:48 by hyoshie           #+#    #+#             */
/*   Updated: 2021/12/13 00:27:10 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../expander.h"
# include "../lexer/test/test.h"

void	test_search_prefix(char *word, char *tstmsg);
void	test_search_prefixs(void);
void	test_expand_var(char *word, char *tstmsg);
void	test_expand_vars(void);
void	test_strclen_array(char *str, char *sep, char *tstmsg);
void	test_strclen_arrays(void);
void	test_append_nonvar(char *str, char *tail, size_t len, char *tstmsg);
void	test_append_nonvars(void);
//test_expand_var_all.c
void	test_expand_var_all(char *line, char *tstmsg);
void	test_expand_var_alls(void);
//lexer/test/test.h
void	print_tokens(t_token *head);
#endif /* TEST_H */