/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:20:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/26 16:17:21 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	check_for_expander(t_list *prt)
{
	int	i;

	i = -1;
	if (prt->wt != LMTR)
	{
		while (prt->pt[++i])
		{
			if (prt->pt[i] == '$' && !in_quotes(prt->pt, i))
				return (1);
		}
	}
	return (0);
}

char	*expand_var(t_minishell *mini, char *old_str)
{
	int		i;
	int		s;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (1)
	{
		s = i;
		while (old_str[i])
		{
			if (old_str[i] == '$' && !in_quotes(old_str, i))
				break ;
			i++;
		}
		new_str = ft_strjoin(new_str, ft_substr(old_str, s, i - s));
		if (old_str[i] == '\0')
			break ;
		if (old_str[i] == '$' && !in_quotes(old_str, i))
			new_str = ft_strjoin(new_str, take_dollar(mini, old_str, &i));
	}
	return (free(old_str), new_str);
}

void	expander(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (check_for_expander(tmp))
			tmp->pt = expand_var(mini, tmp->pt);
		tmp = tmp->next;
	}
}

void	split_cmd_line_by_space(t_minishell *mini)
{
	int		i;
	int		s;
	char	*str;

	str = NULL;
	i = skip_white_spaces(mini, 0);
	s = i;
	while (1)
	{	
		if ((mini->line[i] == ' ' && !in_quotes(mini->line, i))
			|| mini->line[i] == '\0')
		{
			str = ft_substr(mini->line, s, i - s);
			ft_lstadd_back(&mini->cmd, ft_lstnew(str, IND));
			free(str);
			i = skip_white_spaces(mini, i);
			s = i;
		}
		if (mini->line[i] == '\0')
			break ;
		else
			i++;
	}
}
