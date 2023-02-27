/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:34:38 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/27 14:52:09 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

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

int	is_rdrct_or_pp(int type)
{
	if (type == IN_F || type == LMTR || type == AP_F
		|| type == TR_F || type == PP)
		return (1);
	else
		return (0);
}

void	identify_cmd(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	if (tmp->wt == IND)
	{
		tmp->wt = CMD;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (is_rdrct_or_pp(tmp->wt) && (tmp->next && tmp->next->wt == IND))
			tmp->next->wt = CMD;
		tmp = tmp->next;
	}
}

void	identify_flag(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if ((tmp->wt == CMD || tmp->wt == FLG) && (tmp->next
				&& tmp->next->wt == IND))
			if (!ft_strncmp(tmp->next->pt, "-", 1))
				tmp->next->wt = FLG;
		tmp = tmp->next;
	}
}

void	identify_arg(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if ((tmp->wt == CMD || tmp->wt == FLG || tmp->wt == ARG)
			&& (tmp->next && tmp->next->wt == IND))
			tmp->next->wt = ARG;
		tmp = tmp->next;
	}
}
