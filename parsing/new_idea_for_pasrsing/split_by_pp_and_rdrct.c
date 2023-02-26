/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pp_and_rdrct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:21:30 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/26 16:30:59 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	should_be_splited(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (!in_quotes(str, i))
				return (1);
		}
		i++;
	}
	return (0);
}

void	take_pp_or_rdrct(char *str, int *i, t_list **new)
{
	int		tp;
	char	*r;

	r = NULL;
	if (str[*i] == '|')
	{
		r = ft_strdup("|");
		*i += 1;
	}
	else if (str[*i] == '>' || str[*i] == '<')
	{
		tp = str[*i];
		if (str[*i + 1] == tp)
		{
			r = ft_substr(str, *i, 2);
			*i += 2;
		}
		else
		{
			r = ft_substr(str, *i, 1);
			*i += 1;
		}
	}
	ft_lstadd_back(new, ft_lstnew(r, IND));
	free(r);
}

void	add_to_new_list(t_list **new, char *str)
{
	int		i;
	int		s;
	char	*prt;

	i = -1;
	while (1)
	{
		s = i + (i == -1);
		while (str[++i])
			if ((str[i] == '|' || str[i] == '>' || str[i] == '<')
				&& !in_quotes(str, i))
				break ;
		if (i > s)
		{
			prt = ft_substr(str, s, i - s);
			ft_lstadd_back(new, ft_lstnew(prt, IND));
			free(prt);
		}
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			if (!in_quotes(str, i))
				take_pp_or_rdrct(str, &i, new);
		if (str[i] == '\0')
			break ;
	}
}

void	split_by_pp_and_rdrct(t_minishell *mini)
{
	t_list	*new_cmd_lst;
	t_list	*tmp;

	tmp = mini->cmd;
	new_cmd_lst = NULL;
	while (tmp)
	{
		if (should_be_splited(tmp->pt))
			add_to_new_list(&new_cmd_lst, tmp->pt);
		else
			ft_lstadd_back(&new_cmd_lst, ft_lstnew(tmp->pt, IND));
		tmp = tmp->next;
	}
	ft_lstclear(&mini->cmd);
	mini->cmd = new_cmd_lst;
}
