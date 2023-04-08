/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:55:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/08 04:33:37 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"
#include<limits.h>

char	*take_and_expand(t_minishell *mini, char *str, int *i)
{
	char	*r;
	int		j;
	int		s;

	r = NULL;
	j = *i + 1;
	while (1)
	{
		s = j;
		while (str[j] != str[*i])
		{
			if (str[j] == '$')
				break ;
			j++;
		}
		if (j > s)
			r = ft_strjoin(r, ft_substr(str, s, (j - s)));
		if (str[j] == '$')
			r = ft_strjoin(r, take_dollar(mini, str, &j));
		if (str[j] == str[*i])
			break ;
	}
	if (!r)
		r = ft_strjoin(r, ft_strdup(""));
	return (*i = j, r);
}

char	*take_wthout_expand(char *str, int *i, int c)
{
	int		j;
	char	*r;

	j = 0;
	r = NULL;
	while (str[++j])
		if (str[j] == c)
			break ;
	r = ft_substr(str, 1, j - 1);
	return (*i += j, r);
}

char	*take_new_str(t_minishell *mini, t_list *prt)
{
	int		i;
	int		s;
	char	*r;

	i = 0;
	r = NULL;
	while (prt->pt[i])
	{
		s = i;
		while (prt->pt[i] != '"' && prt->pt[i] != '\'' && prt->pt[i])
			i++;
		if (i > s)
			r = ft_strjoin(r, ft_substr(prt->pt, s, i - s));
		if (prt->pt[i] == '"' && prt->wt != LMTR)
			r = ft_strjoin(r, take_and_expand(mini, prt->pt, &i));
		else if (prt->pt[i] == '\'' || (prt->pt[i] == '"' && prt->wt == LMTR))
			r = ft_strjoin(r, take_wthout_expand(&prt->pt[i], &i, prt->pt[i]));
		if (!prt->pt[i])
			break ;
		i++;
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
