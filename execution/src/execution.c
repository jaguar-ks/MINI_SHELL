/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/03 21:46:14 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// **	Execute one command
static void	_execute_command(t_minishell *mini, t_exec *cmd_to_exec)
{
	char	*path;

	path = NULL;
	if (mini->exc->cmd_exec && mini->exc->cmd_exec[0]
		&& check_builtin(cmd_to_exec->cmd_exec[0]))
		return (do_builtin(cmd_to_exec, mini), exit(*mini->ext_st));
	if (cmd_to_exec->cmd_exec && cmd_to_exec->cmd_exec[0])
		path = get_cmd_path(mini, cmd_to_exec->cmd_exec[0]);
	if (!path)
		cmd_not_found(cmd_to_exec->cmd_exec);
	execve(path, cmd_to_exec->cmd_exec, take_char_env(mini->env));
	cmd_not_found(cmd_to_exec->cmd_exec);
	exit(error("execve", errno));
}

// **	Wait for child processes until they finish
static int	wait_childs(t_minishell *mini, int pid)
{
	if (*mini->ext_st == 11)
		*mini->ext_st = (ft_printf("%d segmentation fault\n", 2, pid), 139);
	while (1)
		if (wait(NULL) == -1)
			break ;
	return (*mini->ext_st);
}

// Initialize fd's variables to -1, which means normal STDIN / STDOUT
static void	init_var(t_minishell *mini, t_exec *pipeline)
{
	mini->fd_cnt = 0;
	while (pipeline)
	{
		pipeline->rdrct_err = 0;
		pipeline->in = -2;
		pipeline->out = -2;
		pipeline = pipeline->next;
	}
	return ;
}

void	_execute_in_child(t_minishell *mini, t_exec *command)
{
	if (command->in > 0)
		if (dup2(command->in, STDIN_FILENO) < 0)
			exit(error("dup", errno));
	if (command->out > 0)
		if (dup2(command->out, STDOUT_FILENO) < 0)
			exit(error("dup", errno));
	close_file_descriptors(mini);
	_execute_command(mini, command);
}

// Opens heredoc, opens redirections then executes pipeline
void	execute_pipeline(t_minishell *mini)
{
	pid_t	pid;

	pid = -1;
	if (!mini || !mini->exc)
		return ;
	init_var(mini, mini->exc);
	if (mini->exc->next)
		open_pipes(mini, mini->exc);
	open_redirections(mini, mini->exc);
	execute_all_commands(mini, mini->exc, &pid);
	close_file_descriptors(mini);
	wait_childs(mini, pid);
	exit(*mini->ext_st);
}
