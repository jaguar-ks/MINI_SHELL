/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:17:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/18 09:36:03 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	check_builtin(char *cmd)
{
	return ((!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
			|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "exit")));
}

void	do_builtin(t_exec *cmd, t_minishell *mini)
{
	if (!is_echo(cmd->cmd_exec[0]))
		my_echo(cmd);
	else if (!is_cd(cmd->cmd_exec[0]))
		my_cd(cmd, mini);
	else if (!is_pwd(cmd->cmd_exec[0]))
		my_pwd(mini->env);
	else if (!is_env(cmd->cmd_exec[0]))
		my_env(mini->env);
	else if (!is_exit(cmd->cmd_exec[0]))
		my_exit(cmd, mini);
	else if (!is_unset(cmd->cmd_exec[0]))
		my_unset(cmd, mini);
	else if (!is_export(cmd->cmd_exec[0]))
		my_export(cmd, mini);
}

int	should_not_fork(char **cmd)
{
	if (!is_cd(cmd[0]) || !is_exit(cmd[0]) || !is_unset(cmd[0]))
		return (0);
	if (!is_export(cmd[0]))
		if (!cmd[1])
			return (0);
	return (1);
}
