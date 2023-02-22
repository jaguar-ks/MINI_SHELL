/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:47 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:13 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*expan_variable(char *var, t_minishell *mini)
{
	t_list	*tmp;
	char	*vr;
	int		i;
	int		ct;

	i = 1;
	ct = 0;
	tmp = mini->env;
	if (var[i] == '?')
		return (ft_itoa(mini->ext_st));
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break ;
		i++;
	}
	vr = ft_substr(var, 1, i - 1);
	while (tmp)
	{
		if (tmp->acs)
			if (ft_strnstr(tmp->pt, vr, ft_strlen(tmp->pt)))
				return (free(vr), ft_strdup(ft_strchr(tmp->pt, '=') + 1));
		tmp = tmp->next;
	}
	return (free(vr), ft_strdup(""));
}

int	check_expand(char *str)
{
	if (str[1] == '?' || (ft_isalnum(str[1]) || str[1] == '_'))
		return (1);
	else
		return (0);
}

char	*take_dollar(t_minishell *mini, int *i)
{
	char	*exp;
	int		j;

	j = 0;
	if (check_expand(&mini->line[*i]))
	{
		exp = expan_variable(&mini->line[*i], mini);
		while (mini->line[++(*i)])
			if (!ft_isalnum(mini->line[*i]) && mini->line[*i] != '_'
				&& mini->line[*i] != '?')
				break ;
	}
	else
	{
		if (mini->line[*i + 1] == '$')
			while (mini->line[*i + j] == '$')
				j++;
		if (j % 2 == 0 && j > 1)
			exp = ft_strdup("");
		else
			exp = ft_strdup("$");
		*i += j + 1;
	}
	return (exp);
}

int	take_var(t_minishell *mini, int i)
{
	char	*var;

	var = take_dollar(mini, &i);
	ft_lstadd_back(&mini->cmd, ft_lstnew(var, VRB));
	free(var);
	return (i);
}
