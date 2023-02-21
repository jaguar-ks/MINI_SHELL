/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_cmd_ln.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:10:55 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/21 14:51:21 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	skip_white_spaces(t_minishell *mini, int *i)
{
	while (mini->line[++(*i)])
		if (!ft_isspace(mini->line[*i]))
			break ;
}

char	*take_wrd(t_minishell *mini, int *i)
{
	char	*str;
	int		j;

	j = *i;
	while (mini->line[++j])
		if (mini->line[j] == '$' || mini->line[j] == '"'
			|| mini->line[j] == '|' || mini->line[j] == '<'
			|| mini->line[j] == '>')
			break ;
	str = ft_substr(mini->line, *i, j - (*i));
	*i = j;
	return (str);
}

t_list	*parss_command_line(t_minishell *mini)
{
	int		i;
	t_list	*cmd;

	mini->ext_st = check_syntax(mini->line);
	if (mini->ext_st != 1)
		return (NULL);
	i = -1;
	cmd = NULL;
	skip_white_spaces(mini, &i);
	if (mini->line[i] == '\0')
		return (mini->ext_st = 0, NULL);
	while (mini->line[i])
	{
		if (mini->line[i] == '\'' || mini->line[i] == '"')
			take_quotes(mini, &cmd, &i);
		else if (mini->line[i] == '<' || mini->line[i] == '>')
			take_rediraction(mini, &cmd, &i);
	}
}
