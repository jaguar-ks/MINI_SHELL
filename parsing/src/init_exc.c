/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:45:15 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/11 04:34:18 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	check_rdrct(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == HEREDOC || tmp->wt == INPT || tmp->wt == APND
			|| tmp->wt == TRNC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	take_rdrct(t_list *cmd, t_list **rdrct)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == HEREDOC || tmp->wt == INPT || tmp->wt == APND
			|| tmp->wt == TRNC)
			ft_lstadd_back(rdrct, dup_node(tmp->next));
		tmp = tmp->next;
	}
}

void	take_exc_prt(t_minishell *mini, t_list *cmd)
{
	t_exec	*new;
	t_exec	*tmp;

	new = (t_exec *)malloc(sizeof(t_exec));
	if (!new)
		return ;
	new->next = NULL;
	new->cmd_exec = NULL;
	if (check_cmd(cmd))
		new->cmd_exec = take_char_cmd(cmd);
	new->redrc = NULL;
	if (check_rdrct(cmd))
		take_rdrct(cmd, &new->redrc);
	if (!mini->exc)
		mini->exc = new;
	else
	{
		tmp = mini->exc;
		while (tmp->next)
			tmp = tmp->next;
		tmp = new;
	}
	ft_lstclear(&cmd);
}

void	init_exc(t_minishell *mini)
{
	t_list	**cmd;
	int		i;

	i = -1;
	cmd = split_cmd_list(mini);
	while (cmd[++i])
		take_exc_prt(mini, cmd[i]);
	free(cmd);
}

void	cmd_not_found(char **cm)
{
	int	ext;
	DIR	*dir;

	dir = opendir(cm[0]);
	if (dir)
	{
		closedir(dir);
		ext = error(cm[0], 126);
	}
	else
		ext = error(cm[0], 127);
	deallocate(cm);
	exit(ext);
}