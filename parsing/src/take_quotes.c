/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:27:24 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/18 02:29:56 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	valid_ct(char *cl)
{
	int	i;
	int	j;
	int	ct;

	i = -1;
	while (cl[++i])
	{
		if (cl[i] == 34 || cl[i] == 39)
		{
			ct = cl[i];
			j = i;
			while (cl[++j])
				if (cl[j] == ct)
					break ;
			if (cl[j] == '\0')
				return (0);
		}
	}
	return (1);
}

char	*take_double_qts(t_minishell *mini, int i)
{
	int		j;
	char	*r;

	j = i;
	while (mini->line[++j] != '"')
	{
		if (mini->line[j] == '$')
			r = ft_strjoin(r, take_dollar(mini, &j));
		else
			r = ft_strjoin(r, take_wrd(mini, &j));
	}
	return (r);
}

void	take_quotes(t_minishell *mini, t_list **cmd, int *i)
{
	int		j;
	char	*pt;

	j = *i;
	while (mini->line[++j])
		if (mini->line[*i] == mini->line[j])
			break ;
	if (j == *i + 1)
	{
		ft_lstadd_back(cmd, ft_lstnew("", QTS));
		return ;
	}
	else if (mini->line[*i] == '\'')
		pt = ft_substr(mini->line, *i, j - *i);
	else if (mini->line[*i] == '"')
		pt = take_double_qts(mini, *i);
	*i = j;
	ft_lstadd_back(cmd, ft_lstnew(pt, QTS));
	free(pt);
}
