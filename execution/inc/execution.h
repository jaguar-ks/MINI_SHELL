/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:18:23 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/02 17:12:44 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"

/*calculate the len of the accessable parts of envirement*/
int		env_len(t_list *en);
/*take the accessable parts of the enviremants*/
char	**take_char_env(t_list *en);
/*move to the next command*/
t_list	*move_to_next_cmd(t_list *cmd, int i);
/*take single command at the time*/
t_list	*single_cmd(t_minishell *mini);
// void	execute_cmd_line(t_minishell *mini);
void	do_cmd(t_minishell *mini);

#endif
