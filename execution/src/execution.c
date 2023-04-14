/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/14 02:45:54 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//   <<     EOF  cat  -e   |  cat   >  outfile  |  echo "More"  >>  outfile  |  echo  $PATH
// HEREDOC LMTR  CMD  FLG  PP CMD TRNC   TR_F   PP  CMD   ARG  APND  AP_F    PP CMD  ARG

// $? prints exit status

// 3.1.1 Shell Operation
	// The following is a brief description of the shell's operation when it reads and executes a
	// command. Basically, the shell does the following:
	// 1. Reads its input from a file (see Section 3.8 [Shell Scripts], page 46), from a string
	// supplied as an argument to the -c invocation option (see Section 6.1 [Invoking Bash],
	// page 91), or from the user's terminal.
	// 2. Breaks the input into words and operators, obeying the quoting rules described in
	// Section 3.1.2 [Quoting], page 6. These tokens are separated by metacharacters. Alias
	// expansion is performed by this step (see Section 6.6 [Aliases], page 100).
	// 3. Parses the tokens into simple and compound commands (see Section 3.2 [Shell Com-
	// mands], page 9).
	// 4. Performs the various shell expansions (see Section 3.5 [Shell Expansions], page 24),
	// breaking the expanded tokens into lists of filenames (see Section 3.5.8 [Filename Ex-
	// pansion], page 35) and commands and arguments.
	// 5. Performs any necessary redirections (see Section 3.6 [Redirections], page 38) and re-
	// moves the redirection operators and their operands from the argument list.
	// 6. Executes the command (see Section 3.7 [Executing Commands], page 42).
	// 7. Optionally waits for the command to complete and collects its exit status (see
	// Section 3.7.5 [Exit Status], page 44).

/*
	PIPE_IN and PIPE_OUT are file descriptors saying where input comes
   from and where it goes.  They can have the value of NO_PIPE, which means
   I/O is stdin/stdout.
*/

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

void	handle_redrc_and_heredoc(t_minishell *mini, t_exec *exec_cmd)
{
	int		fd;
	int		dup_in;
	t_list	*tmp;

	fd = 0;
	dup_in = dup(STDIN_FILENO);
	tmp = exec_cmd->redrc;
	signal(SIGINT, handl_segint_child);
	while (tmp)
	{
		if (tmp->wt == IN_F)
		{
			fd = open(tmp->pt, O_RDONLY);
			if (fd < 0)
				{*mini->ext_st = 1; perror("Minishell_redrc1"); exit(1);}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (tmp->wt == AP_F || tmp->wt == TR_F)
		{
			if (tmp->wt == TR_F)
				fd = open(tmp->pt, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
			else
				fd = open(tmp->pt, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0644);
			if (fd == -1)
				{fprintf(stderr, "%s", tmp->pt);*mini->ext_st = 1; perror("Minishell_redrc2"); exit(1);}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->wt == LMTR)
		{
			open_here_doc(mini, tmp, &fd, dup_in);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return;
}

void	execute_one_command(t_minishell *mini, t_exec *exec_cmd)
{
	char	*path;

	path = NULL;
	if (exec_cmd->redrc != NULL)
		handle_redrc_and_heredoc(mini, exec_cmd);
	if (exec_cmd && exec_cmd->cmd_exec)
	{
		path = get_cmd_path(mini, exec_cmd->cmd_exec[0]);
		if (!path || exec_cmd->cmd_exec[0][0] == '\0')
			cmd_not_found(exec_cmd->cmd_exec);
		execve(path, exec_cmd->cmd_exec, take_char_env(mini->env));
	}
	exit(0);
	return ;
}

// Execute command and handle redirections, if there is no pipe
void	execute_command_with_nopipe(t_minishell *mini, t_exec *exec_cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_one_command(mini, exec_cmd);
		exit(*mini->ext_st);
	}
	wait(mini->ext_st);
	if (WIFEXITED(*mini->ext_st))
		*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	return ;
}

// **************** COMMENTS **************** //

// Should not wait in while, for each command 
//	cat | cat | cat | ls doesnt behave as bash
// still have to handle (. && ..) when they are given as command

// ***************************************** //
void	execute_cmds(t_minishell *mini)
{
	int		old_fd[2];
	pid_t	pid;
	t_exec	*tmp;
	
	pid = 0;
	tmp = mini->exc;
	if (tmp && tmp->cmd_exec && tmp->next == NULL)
	{
		execute_command_with_nopipe(mini, tmp);
		if (access((const char *)mini->filename, F_OK) == 0)
			unlink((const char *)mini->filename);
		return;
	}
	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	while (tmp)
	{
		pipe(mini->fd);
		pid = fork();
		if (pid == 0)
		{
			close(mini->fd[0]);
			close(old_fd[0]);
			close(old_fd[1]);
			if (tmp->next != NULL)
				dup2(mini->fd[1], STDOUT_FILENO);
			close(mini->fd[1]);
			execute_one_command(mini, tmp);
			exit(1);
		}
		close(mini->fd[1]);
		if (tmp->next && !tmp->next->redrc)
			dup2(mini->fd[0], STDIN_FILENO);
		else
		{		
			wait(mini->ext_st);
			if (WIFEXITED(*mini->ext_st))
				*mini->ext_st = WEXITSTATUS(*mini->ext_st);
		}
		close(mini->fd[0]);
		tmp = tmp->next;
	}
	dup2(old_fd[0], STDIN_FILENO);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[0]);
	close(old_fd[1]);
	while (waitpid(-1, mini->ext_st, 0) != -1)
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	return;
	}
