/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/16 00:16:21 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//   <<     EOF  cat  -e   |  cat   >  outfile  |  echo "More"  >>  outfile  |  echo  $PATH
// HEREDOC LMTR  CMD  FLG  PP CMD TRNC   TR_F   PP  CMD   ARG  APND  AP_F    PP CMD  ARG

/*
# define HEREDOC 1
# define LMTR 2
# define APND 3
# define TRNC 4
# define INPT 5
# define PP 6
# define IND 7
# define ARG 8
# define EN 9
# define AP_F 10
# define TR_F 11
# define IN_F 12
# define CMD 13
# define FLG 14
*/

void	open_redirections(t_list *node, int *in, int *out)
{
	if (node->wt == IN_F)
	{
		*in = open(node->pt, O_RDONLY);
		if (*in < 0)
			error(node->pt, 1);
	}
	if (node->wt == AP_F)
	{
		*out = open(node->pt, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*out < 0)
			error(node->pt, 1);
	}
	if (node->wt == TR_F)
	{
		*out = open(node->pt, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*out < 0)
			error(node->pt, 1);
	}
	return ;
}

void	open_heredoc(t_minishell *mini, t_exec *cmd_list)
{
	t_exec	*tmp;
	t_list	*tmp2;

	tmp = cmd_list;
	while (tmp)
	{
		tmp->in = -1;
		tmp->out = -1;
		ft_bzero(tmp->heredoc_filename, 20);
		if (tmp->redrc)
		{
			tmp2 = tmp->redrc;
			while (tmp2)
			{
				if (tmp2->wt == LMTR)
				{
					heredoc_filename(&tmp, &tmp->in);
					open_here_doc(mini, tmp, tmp2);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	return ;
}

void	execute_cmds(t_minishell *mini)
{
	if (!mini || !mini->exc)
		return ;
	// Initialize fd's variables to -1, which means normal STDIN / STDOUT, 

	// 1 - open heredoc file, read from stdin, store I/O fd's
	// 2 - open any infile, outfile, and store I/O fd's
	open_heredoc(mini, mini->exc);
	open_redrc(mini->exc);
	// execute cmds and go directly reads or write to fd's, without opening anything
	// pipe_fork_dup_and_execute();
		// dup I/O
		
		// if (tmp2->wt == IN_F || tmp2->wt == AP_F || tmp2->wt == TR_F)
				// 	open_input_output(tmp2, &tmp->in, &tmp->out);
		// check if the command is a built-in command
	// 	check_builtin();
	// 	// close all openned fd's in each child process [IN, OUT, ERR, fd[0], fd[1], ]
	// 	close_child_fds();
	// // close all openned fd's in parent process
	// close_parent_fds();
	// // delete heredoc_temporary file
	// // unlink(filename...)
	// wait_childs();
	return ;
}
