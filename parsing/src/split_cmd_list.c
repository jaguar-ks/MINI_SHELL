/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:09:09 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/18 09:58:49 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

t_list	*move_to_next_cmd(t_list *cmd, int i)
{
	t_list	*tmp;
	int		j;

	j = 0;
	tmp = cmd;
	if (i == 0)
		return (tmp);
	while (tmp)
	{
		if (tmp->wt == PP)
			j++;
		tmp = tmp->next;
		if (j == i)
			break ;
	}
	return (tmp);
}

t_list	*single_cmd(t_minishell *mini)
{
	static int	i;
	t_list		*s_cmd;
	t_list		*tmp;

	s_cmd = NULL;
	if (i < 0)
		return (i = 0, NULL);
	tmp = move_to_next_cmd(mini->cmd, i);
	while (tmp)
	{
		if (tmp->wt == PP)
		{
			i++;
			break ;
		}
		ft_lstadd_back(&s_cmd, dup_node(tmp));
		tmp = tmp->next;
	}
	if (!tmp)
		i = -1;
	return (s_cmd);
}

int	how_many_pipe(t_list *cmd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == PP)
			i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

t_list	**split_cmd_list(t_minishell *mini)
{
	t_list	**cmd;
	int		i;
	int		j;

	i = how_many_pipe(mini->cmd);
	cmd = (t_list **)malloc(sizeof(t_list *) * (i + 1));
	if (!cmd)
		return (NULL);
	j = -1;
	while (++j <= i)
		cmd[j] = single_cmd(mini);
	return (cmd);
}

int	error(char *er, int ext_er)
{
	if (ext_er == 127)
		ft_printf("Minishell : Command not found : %s\n", STDERR_FILENO, er);
	else if (ext_er == 126)
		ft_printf("Minishell : Is a directory : %s\n", STDERR_FILENO, er);
	else if (ext_er == 258)
		ft_printf("Minishell : Syntax error\n", STDERR_FILENO);
	else
		ft_printf("Minishell : %s : %s\n", STDERR_FILENO, strerror(errno), er);
	return (ext_er);
}
