/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:28:47 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/03 20:57:45 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*expan_variable(char *var, t_minishell *mini)
{
	t_list	*tmp;
	char	*vr;
	int		i;

	i = 1;
	tmp = mini->env;
	if (var[i] == '?')
		return (ft_itoa(*mini->ext_st));
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
			if (!ft_strncmp(tmp->pt, vr, ft_strlen(vr)))
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

	exp = NULL;
	j = *i;
	while (line[++j])
		if (line[j] != '$')
			break ;
	if ((j - *i) % 2 != 0)
	{
		if (check_expand(&line[j - 1]))
		{
			exp = expan_variable(&line[j - 1], mini);
			if (line[j] == '?')
				j++;
			else if (ft_isalnum(line[j]) || line[j] == '_')
				while (line[++j])
					if (!ft_isalnum(line[j]) && line[j] != '_')
						break ;
			return (*i = j, exp);
		}
		return (*i = j, ft_strdup("$"));
	}
	return (*i = j, ft_strdup(""));
}
