/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/12 02:05:32 by faksouss         ###   ########.fr       */
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

void	handle_redrc_and_heredoc(t_minishell *mini)
{
	int		fd;
	t_list	*tmp;

	fd = 0;
	tmp = mini->exc->redrc;
	while (tmp)
	{
		if (tmp->wt == IN_F)
		{
			fd = open(tmp->pt, O_RDONLY);
			if (fd < 0)
				{*mini->ext_st = errno; perror("Minishell_redrc:"); exit(errno);}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (tmp->wt == AP_F || tmp->wt == TR_F)
		{
			if (tmp->wt == TR_F)
				fd = open(tmp->pt, O_CREAT | O_TRUNC | O_RDWR, 0644);
			else
				fd = open(tmp->pt, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (fd < 0)
				{*mini->ext_st = errno; perror("Minishell_redrc:"); exit(errno);}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		// else if (tmp->wt == HEREDOC)
		// {
			// 	if (tmp->acs == 0)
		// }
		tmp = tmp->next;
	}
	return ;
}

void	execute_one_command(t_minishell *mini)
{
	char	*path;
	if (mini->exc->redrc != NULL)
		handle_redrc_and_heredoc(mini);
	path = get_cmd_path(mini, mini->exc->cmd_exec[0]);
	execve(path, mini->exc->cmd_exec, take_char_env(mini->env));
	error("minishell_exec_one:", 127);
	return ;
}

// Execute command and handle redirections, if there is no pipe
void	execute_command_with_nopipe(t_minishell *mini)
{
	t_exec	*tmp;
	int	pid;

	tmp = mini->exc;
	pid = fork();
	if (pid == 0)
	{
		// if (tmp->redrc != NULL)
			// handle_redrc_and_heredoc(mini);
		execute_one_command(mini);
	}
	wait(mini->ext_st);
	if (WIFEXITED(*mini->ext_st))
	{
		*mini->ext_st = WEXITSTATUS(*mini->ext_st);
		// if (*mini->ext_st != 0)
		// 	exit(*mini->ext_st);
	}
	return ;
}

// **************** COMMENTS **************** //

// Exit Status is 32512, in case you enter a bunch of letters, exited from minishell_find_cmd: No such file or directory
void	execute_cmds(t_minishell *mini)
{
	// int		old_fd[2];
	t_exec	*tmp;
	
	tmp = mini->exc;
	if (tmp && tmp->next == NULL)
		return (execute_command_with_nopipe(mini));
	// old_in[0] = dup(STDIN_FILENO);
	// old_out[1] = dup(STDOUT_FILENO);
	// while (tmp)
	// {
	// 	pipe(mini->fd);
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		if (tmp->redrc != NULL)
	// 			handle_redrc_and_heredoc(tmp);

	// 	}

	// }
	// dup2(old_in[0], STDIN_FILENO);
	// dup2(old_out[1], STDOUT_FILENO);
	return;
}
