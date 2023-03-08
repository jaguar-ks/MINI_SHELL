/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:58:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 03:15:29 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"
# include"../../execution/inc/execution.h"

/*check if the flag -n chould work*/
int		check_echo_flg(char *flg);
/*repreduce the echo bihavior*/
void	my_echo(t_list *cmd, t_minishell *mini);
/*check if the command is echo*/
int		is_echo(t_list *cmd);

#endif
