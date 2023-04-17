/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/17 05:09:50 by mfouadi          ###   ########.fr       */
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

static void	_execute_command(t_minishell *mini, t_exec *cmd_to_exec)
{
	char	*path;
	
	path = NULL;
	if (cmd_to_exec->cmd_exec && cmd_to_exec->cmd_exec[0])
		path = get_cmd_path(mini, cmd_to_exec->cmd_exec[0]);
	if (!path)
		cmd_not_found(cmd_to_exec->cmd_exec);
	execve(path, cmd_to_exec->cmd_exec, take_char_env(mini->env));
	perror("execute_cmd");
	cmd_not_found(cmd_to_exec->cmd_exec);
}

static void	wait_childs(t_minishell *mini)
{
	while (waitpid(-1, mini->ext_st, 0) != -1)
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
}

static void	init_var(t_minishell *mini, t_exec *pipeline)
{
	mini->fd_cnt = 0;

	while (pipeline)
	{
		pipeline->in = -1;
		pipeline->out = -1;
		ft_bzero(pipeline->heredoc_filename, 25);
		pipeline = pipeline->next;
	}
	return ;
}

void	execute_cmds(t_minishell *mini)
{
	t_exec	*tmp;

	if (!mini || !mini->exc)
		return ;
	// Initialize fd's variables to -1, which means normal STDIN / STDOUT, 
	init_var(mini, mini->exc);
	if (mini->exc->next)
		open_pipes(mini, mini->exc);
	open_heredoc(mini, mini->exc);

	// 2 - open any infile, outfile, and store I/O fd's
	// open_redrc(mini->exc);

	// if (!mini->exc->next)
	// 	if (is _built ())
	// 		if (should_not_fork())
	// 				do_built_in();
	tmp = mini->exc;
	pid_t	pid;
	while (tmp)
	{
		pid = fork();
		if (pid == 0)
		{
			if (tmp->in > 0)
			{	if (dup2(tmp->in, STDIN_FILENO) < 0)
					perror("dup1");}
			if (tmp->out > 0)
				if (dup2(tmp->out, STDOUT_FILENO) < 0)
					perror("dup2");
			close_file_descriptors(mini);
			_execute_command(mini, tmp);
		}
		if (access(tmp->heredoc_filename, F_OK) == 0)
			unlink(tmp->heredoc_filename);
		tmp = tmp->next;
	}
	close_file_descriptors(mini);
	// delete heredoc_temporary file
	wait_childs(mini);
	// free command list
}

/***************************** PRINT FDS *************************
	// // close all openned fd's in parent process


	printf("\n\n\n******** FD'S *********\n");
	while (mini->exc)
	{
		printf("in : %d\n", mini->exc->in);
		printf("out : %d\n", mini->exc->out);
		mini->exc = mini->exc->next;
		printf("\n");
	}
	return ;
*****************************************************************/
