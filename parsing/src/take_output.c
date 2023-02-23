/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:58:30 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/23 19:36:45 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	take_outfile(t_minishell *mini, t_list **cmd, int i, int tp)
{
	int		j;
	char	*fl;

	i = skip_white_spaces(mini, i);
	j = i;
	if (mini->line[i] == '\'' || mini->line[i] == '"')
	{
		while (mini->line[++j])
			if (mini->line[j] == '\'' || mini->line[j] == '"')
				break ;
		fl = ft_substr(mini->line, i + 1, j - i - 1);
		j++;
	}
	else
	{
		while (mini->line[++j])
			if (ft_isspace(mini->line[j]))
				break ;
		fl = ft_substr(mini->line, i, j - i);
	}
	ft_lstadd_back(cmd, ft_lstnew(fl, tp));
	free(fl);
	return (j);
}

int	take_output(t_minishell *mini, t_list **cmd, int i)
{
	int	tp;

	tp = TRNC;
	if (mini->line[i + 1] == '>')
	{
		tp = APND;
		i += 2;
	}
	else
		i += 1;
	i = take_outfile(mini, cmd, i, tp);
	return (i);
}
