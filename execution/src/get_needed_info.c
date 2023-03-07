/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_needed_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:33 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/07 04:01:24 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

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

void	split_and_execute_cmd(t_minishell *mini)
{
	t_list	**cmd;
	int		i;
	int		j;

	i = how_many_pipe(mini->cmd);
	cmd = (t_list **)malloc(sizeof(t_list *) * (i + 1));
	if (!cmd)
		return ;
	j = -1;
	while (++j <= i)
		cmd[j] = single_cmd(mini);
	execute_all(cmd, i, mini);
	j = -1;
	while (++j < i)
		ft_lstclear(&cmd[j]);
	free(cmd);
}
