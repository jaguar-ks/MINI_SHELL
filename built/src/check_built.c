/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:17:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 03:18:12 by faksouss         ###   ########.fr       */
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
		my_echo(cmd, mini);
	else if (is_cd(cmd))
		my_cd(cmd, mini);
}

int	should_not_fork(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "cd", 3) || !ft_strncmp(tmp->pt, "unset", 6)
				||	!ft_strncmp(tmp->pt, "export", 3) || !ft_strncmp(tmp->pt, "exit", 5))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
