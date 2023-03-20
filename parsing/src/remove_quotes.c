/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:55:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/20 03:57:04 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*take_and_expand(t_minishell *mini, char *str, int *i)
{
	char	*r;
	int		j;
	int		s;

	r = NULL;
	j = *i;
	while (1)
	{
		s = j + (j == *i);
		while (str[++j] != str[*i])
			if (str[j] == '$')
				break ;
		if (j > s)
			r = ft_strjoin(r, ft_substr(str, s, j - s));
		if (str[j] == '$')
			r = ft_strjoin(r, take_dollar(mini, str, &j));
		if (str[j] == str[*i])
			break ;
	}
	return (*i = j, ft_strjoin(r, ft_strdup("")));
}

char	*take_wthout_expand(char *str, int *i)
{
	int		j;
	int		s;
	char	*r;

	j = *i + 1;
	r = NULL;
	s = j;
	while (str[j] != str[*i])
		j++;
	r = ft_strjoin(r, ft_substr(str, s, j - s));
	return (*i = j, r);
}

char	*take_new_str(t_minishell *mini, t_list *prt)
{
	int		i;
	int		s;
	char	*r;

	i = -1;
	r = NULL;
	while (1)
	{
		s = i + (i == -1 || (prt->pt[i] == '\'' || prt->pt[i] == '"'));
		while (prt->pt[++i])
			if (prt->pt[i] == '"' || prt->pt[i] == '\'')
				break ;
		if (i > s)
			r = ft_strjoin(r, ft_substr(prt->pt, s, i - s));
		if (prt->pt[i] == '"' && prt->wt != LMTR)
			r = ft_strjoin(r, take_and_expand(mini, prt->pt, &i));
		if (prt->pt[i] == '\'' || (prt->pt[i] == '"' && prt->wt == LMTR))
			r = ft_strjoin(r, take_wthout_expand(prt->pt, &i));
		if (prt->pt[i] == '\0')
			break ;
	}
	return (free(prt->pt), r);
}

void	remove_quotes(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->pt, '\'') || ft_strchr(tmp->pt, '"'))
		{
			tmp->pt = take_new_str(mini, tmp);
			if (tmp->wt == LMTR)
				tmp->acs = 0;
		}
		tmp = tmp->next;
	}
}
