/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:15:18 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/16 11:03:52 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include"../../parsing/inc/parsing.h"
# include"../../execution/inc/execution.h"
# include"../../libtool/inc/libft.h"

void	mini_shell(t_minishell *mini);
void	out(t_minishell *mini);
char	*inisialise_prompt(void);
void	take_cmd(t_minishell *mini);
void	take_and_do_cmd(t_minishell *mini);

#endif
