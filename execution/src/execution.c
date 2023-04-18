/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/18 04:14:58 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// **	Execute one command
static void	_execute_command(t_minishell *mini, t_exec *cmd_to_exec)
{
	char	*path;

	path = NULL;
	if (cmd_to_exec->cmd_exec && cmd_to_exec->cmd_exec[0])
		path = get_cmd_path(mini, cmd_to_exec->cmd_exec[0]);
	if (!path)
		cmd_not_found(cmd_to_exec->cmd_exec);
	execve(path, cmd_to_exec->cmd_exec, take_char_env(mini->env));
	cmd_not_found(cmd_to_exec->cmd_exec);
}

// **	Wait for child processes until they finish
static int	wait_childs(t_minishell *mini)
{
	while (waitpid(-1, mini->ext_st, 0) != -1)
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	return (*mini->ext_st);
}

// Initialize fd's variables to -1, which means normal STDIN / STDOUT
static void	init_var(t_minishell *mini, t_exec *pipeline)
{
	mini->fd_cnt = 0;
	while (pipeline)
	{
		pipeline->rdrct_err = 0;
		pipeline->in = -1;
		pipeline->out = -1;
		ft_bzero(pipeline->heredoc_filename, 25);
		pipeline = pipeline->next;
	}
	return ;
}

static void	_execute_in_child(t_minishell *mini, t_exec *command)
{
	if (command->in > 0)
		if (dup2(command->in, STDIN_FILENO) < 0)
			perror("dup");
	if (command->out > 0)
		if (dup2(command->out, STDOUT_FILENO) < 0)
			perror("dup");
	close_file_descriptors(mini);
	_execute_command(mini, command);
}

// Opens heredoc, opens redirections then executes pipeline
void	execute_pipeline(t_minishell *mini)
{
	t_exec	*tmp;
	pid_t	pid;

	pid = 0;
	if (!mini || !mini->exc)
		return ;
	init_var(mini, mini->exc);
	if (mini->exc->next)
		open_pipes(mini, mini->exc);
	open_heredoc_and_redirections(mini, mini->exc);
	tmp = mini->exc;
	while (tmp)
	{
		pid = -1;
		if (!tmp->rdrct_err)
			pid = fork();
		if (pid == 0)
			_execute_in_child(mini, tmp);
		if (access(tmp->heredoc_filename, F_OK) == 0)
			if (unlink(tmp->heredoc_filename) != 0)
				perror("unlink");
		tmp = tmp->next;
	}
	close_file_descriptors(mini);
	exit(wait_childs(mini));
}
