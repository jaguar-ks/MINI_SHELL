/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:15:18 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/31 02:37:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include"../../parsing/inc/parsing.h"
# include"../../execution/inc/execution.h"
# include"../../libtool/inc/libft.h"
# include<signal.h>

int		g_ext_st;

void	mini_shell(t_minishell *mini);
void	out(t_minishell *mini);
char	*inisialise_prompt(void);
void	take_cmd(t_minishell *mini);
void	take_and_do_cmd(t_minishell *mini);
void	handl_segint(int segnum);
void	handl_segint_child(int segnum);

#endif
