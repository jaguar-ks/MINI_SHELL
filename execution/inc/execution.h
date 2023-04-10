/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:31:17 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/10 18:17:40 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"
# include"../../built/inc/built.h"
# include"../../main/inc/mini_shell.h"

// ************ Execution **************
void	execute_cmds(t_minishell *mini);
// **	Converts env variable from (t_list *) to a (char **)
char	**convert_env(t_list *env);
// **	Returns path variable splitted
char	**get_path(t_minishell *mini);
// **	Returns path of the the given cmd
char	*find_cmd(char **path, char *cmd);

#endif
