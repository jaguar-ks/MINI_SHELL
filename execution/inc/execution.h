/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:31:17 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/17 06:39:46 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "parsing.h"
# include "built.h"
# include "mini_shell.h"

// Opens heredoc, opens redirections then executes pipeline
void	execute_pipeline(t_minishell *mini);

// ** Looks for PATH variable, then splits it with ':' and store it in a char **
char	*get_cmd_path(t_minishell *mini, char *cmd);

/* The output of each command in the pipeline is connected via a pipe to
	the input of the next command.*/
void	open_pipes(t_minishell *mini, t_exec *pipeline);

// **	close all openned file descriptors, unless STDIN, STDOUT, and STDERR
void	close_file_descriptors(t_minishell *mini);

/*
	Opens redirections '<' '>' '>>', and heredoc '<<' which is stored
	in a tmp file for later use in execute_pipeline()
*/
void	open_heredoc_and_redirections(t_minishell *mini, t_exec *cmd_list);

#endif
