/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:47 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/07 03:57:47 by faksouss         ###   ########.fr       */
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
		return (ft_itoa(mini->ext_st / 255));
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			break ;
		i++;
	}
	vr = ft_strjoin(ft_substr(var, 1, i - 1), ft_strdup("="));
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
	if (str[1] == '?' || (ft_isalpha(str[1]) || str[1] == '_'))
		return (1);
	else
		return (0);
}

char	*take_dollar(t_minishell *mini, char *line, int *i)
{
	char	*exp;
	int		j;

	j = 0;
	exp = NULL;
	if (check_expand(&line[*i]))
	{
		exp = expan_variable(&line[*i], mini);
		while (line[++(*i)])
			if (!ft_isalnum(line[*i]) && line[*i] != '_'
				&& line[*i] != '?')
				break ;
	}
	else
	{
		if (line[*i + 1] == '$')
			exp = ft_strdup("$");
		else
			exp = ft_strdup("");
		*i += 2;
		return (exp);
	}
	return (exp);
}
