/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:17:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/10 09:03:16 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	else
		return (0);
}

int	is_builtin(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (check_builtin(tmp->pt))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	do_builtin(t_list *cmd, t_minishell *mini)
{
	if (is_echo(cmd))
		my_echo(cmd);
	else if (is_cd(cmd))
		my_cd(cmd, mini);
	else if (is_pwd(cmd))
		my_pwd(mini->env);
	else if (is_env(cmd))
		my_env(mini->env);
	else if (is_exit(cmd))
		my_exit(cmd, mini);
	else if (is_unset(cmd))
		my_unset(cmd, mini);
	else if (is_export(cmd))
		my_export(cmd, mini);
}

int	should_not_fork(t_list *cmd)
{
	char	**cm;

	if (!is_cd(cmd) && !is_exit(cmd) && !is_unset(cmd) && !is_export(cmd))
		return (0);
	if (is_export(cmd))
	{
		cm = take_char_cmd(cmd);
		if (!cm[1])
			return (deallocate(cm), 0);
	}
	return (1);
}
