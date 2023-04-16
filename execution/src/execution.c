/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/16 20:49:01 by mfouadi          ###   ########.fr       */
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

void	execute_command(t_minishell *mini, t_exec *cmd_to_exec)
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

void	wait_childs(t_minishell *mini)
{
	while (waitpid(-1, mini->ext_st, 0) != -1)
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	return ;
}

/*

	<< h ==> Ctrl^D ==> segfault
	<< h ==> Delimiter ==> segfault : cmd_not_found

*/
void	execute_cmds(t_minishell *mini)
{
	t_exec	*tmp;

	if (!mini || !mini->exc)
		return ;
	mini->fd_cnt = 0;
	// Initialize fd's variables to -1, which means normal STDIN / STDOUT, 
	// 1 - open heredoc file, read from stdin, store I/O fd's
	// open_pipes(mini->exc);
	open_heredoc(mini, mini->exc);
/***************************** PRINT FDS *************************
	while (mini->exc)
	{
		printf("in : %d\n", mini->exc->in);
		printf("out : %d\n", mini->exc->out);
		while (mini->exc->redrc)
		{
			printf("in_fd : %d\n", mini->exc->redrc->in_fd);
			printf("out_fd : %d\n", mini->exc->redrc->out_fd);
			mini->exc->redrc = mini->exc->redrc->next;
		}
	// 	mini->exc = mini->exc->next;
	// 	printf("\n");
	// }
*****************************************************************/

	// 2 - open any infile, outfile, and store I/O fd's
	// open_redrc(mini->exc);
	// pipe_fork_dup_and_execute();
	/*
	//	Execute cmds and go directly reads or write to fd's, without opening anything
	//	dont forget to close openned fd's
	**
	**	if (check_builtin();)
	**		if (mini->exc->in > 0)
	**			dup2(mini->exc->in, STDIN_FILENO);
	**			close(mini->exc->in);
	**		if (mini->exc->out > 0)
	**			dup2(mini->exc->out, STDOUT_FILENO);
	**			close(mini->exc->out);
	**		If (it's cd, unset or export don't fork)
	**			execute_built_in();
	**			return ;
	*/
	//	close all openned fd's in each child process [IN, OUT, ERR, fd[0], fd[1], ]
	// 	close_child_fds();
	tmp = mini->exc;
	pid_t	pid;
	while (tmp)
	{
		pid = fork();
		if (pid == 0)
		{
			// fprintf(stderr, "%d\n", tmp->in);
			if (tmp->in > 0)
				if (dup2(tmp->in, STDIN_FILENO) < 0)
					perror("dup1");
			if (tmp->out > 0)
				if (dup2(tmp->out, STDOUT_FILENO) < 0)
					perror("dup2");
			close_file_descriptors(mini);
			execute_command(mini, tmp);
			cmd_not_found(tmp->cmd_exec);
		}
		else
			tmp = tmp->next;
	}
	// // close all openned fd's in parent process
	close_file_descriptors(mini);
	// delete heredoc_temporary file
	// unlink(filename...)
	wait_childs(mini);
	return ;
}
