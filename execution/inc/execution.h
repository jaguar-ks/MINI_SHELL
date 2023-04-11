/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:31:17 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/11 02:08:10 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "parsing.h"
# include "built.h"
# include "mini_shell.h"

// ************ Execution **************
void	execute_cmds(t_minishell *mini);
// **	Converts env variable from (t_list *) to a (char **)
char	**convert_env(t_list *env);
// **	Returns path variable splitted
char 	*get_cmd_path(t_minishell *mini, char *cmd);

#endif
