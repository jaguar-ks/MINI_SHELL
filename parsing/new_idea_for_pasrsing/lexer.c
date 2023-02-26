/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:34:38 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/26 15:27:15 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

void	identify_special_charcters(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "<<", 3))
			tmp->wt = HEREDOC;
		else if (!ft_strncmp(tmp->pt, "<", 2))
			tmp->wt = INPT;
		else if (!ft_strncmp(tmp->pt, ">>", 3))
			tmp->wt = APND;
		else if (!ft_strncmp(tmp->pt, ">", 2))
			tmp->wt = TRNC;
		else if (!ft_strncmp(tmp->pt, "|", 2))
			tmp->wt = PP;
		tmp = tmp->next;
	}
}

void	identify_rdrct(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (tmp->wt == HEREDOC)
			tmp->next->wt = LMTR;
		else if (tmp->wt == APND)
			tmp->next->wt = AP_F;
		else if (tmp->wt == TRNC)
			tmp->next->wt = TR_F;
		else if (tmp->wt == INPT)
			tmp->next->wt = IN_F;
		tmp = tmp->next;
	}
}
