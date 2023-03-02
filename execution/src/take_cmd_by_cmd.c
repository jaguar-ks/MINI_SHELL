/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_cmd_by_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:59:03 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/02 17:08:03 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

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
