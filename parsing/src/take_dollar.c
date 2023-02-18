/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:47 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/18 02:33:16 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*expan_variable(char *var, t_minishell *mini)
{
	t_list	*tmp;
	char	*vr;
	int		i;
	int		ct;

	i = 0;
	ct = 0;
	tmp = mini->env;
	if (var[i + 1] == '?')
		return (ft_itoa(mini->ext_st));
	while (var[++i])
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break ;
	vr = ft_substr(var, 1, i);
	while (tmp)
	{
		if (tmp->acs)
			if (ft_strnstr(tmp->pt, vr, ft_strlen(tmp->pt)))
				return (free(vr), ft_strdup(ft_strchr(tmp->pt, '=') + 1));
		tmp = tmp->next;
	}
	return (free(vr), NULL);
}

int	check_expand(char *str)
{
	int	i;

	i = 0;
	if (str[1] == ' ' || str[1] == '$' || str[1] == '"')
	{
		while (str[i] == '$')
			i++;
		if (i % 2 == 0 && i > 1)
			return (1);
		return (0);
	}
	else if (str[1] == '?' || (ft_isalnum(str[1]) || str[1] == '_'))
		return (1);
}

char	*take_dollar(t_minishell *mini, int *i)
{
	char	*exp;

	if (check_expand(&mini->line[*i]))
	{
		exp = expan_variable(&mini->line[*i], mini);
		while (mini->line[++(*i)])
			if (!ft_isalnum(mini->line[*i]) && mini->line[*i] != '_'
				&& mini->line[*i] != '$' && mini->line[*i] != '?'
				&& mini->line[*i] == '"')
				break ;
		if (!exp)
			exp = ft_strdup("");
	}
	else
	{
		exp = ft_strdup("$");
		while (mini->line[++(*i)] != '"')
			if (mini->line[*i] != '$')
				break ;
	}
	return (exp);
}
