/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_wht_have_to_be_joind.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:31:03 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/24 16:07:49 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

t_list	*join_wht_need_to_be_joined(t_minishell *mini)
{
	t_list	*cmd;
	t_list	*tmp;

	tmp = mini->cmd;
	cmd = NULL;
	while(tmp)
	{
		if (tmp->wt == WRD)
	}
}
