/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_cmd_ln.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:10:55 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:04 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	skip_white_spaces(t_minishell *mini, int i)
{
	while (mini->line[i])
	{
		if (!ft_isspace(mini->line[i]))
			break ;
		i++;
	}
	return (i);
}

char	*take_wrd(t_minishell *mini, int *i)
{
	char	*str;
	int		j;

	j = *i;
	while (mini->line[++j])
		if (mini->line[j] == '$' || mini->line[j] == '"'
			|| mini->line[j] == '|' || mini->line[j] == '<'
			|| mini->line[j] == '>' || mini->line[j] == '\''
			|| mini->line[j] == ' ')
			break ;
	str = ft_substr(mini->line, *i, j - (*i));
	*i = j;
	return (str);
}

int	take_other(t_minishell *mini, t_list **cmd, int i)
{
	char	*smthg;
	int		j;

	j = i;
	while (mini->line[++j])
		if (ft_isspace(mini->line[j]))
			break ;
	smthg = ft_substr(mini->line, i, j - i - 1);
	ft_lstadd_back(cmd, ft_lstnew(smthg, LM));
	free(smthg);
	return (j);
}

int	take_word(t_minishell *mini, int i)
{
	char	*wrd;

	wrd = take_wrd(mini, &i);
	ft_lstadd_back(&mini->cmd, ft_lstnew(wrd, WRD));
	free(wrd);
	return (i);
}

void	parss_command_line(t_minishell *mini)
{
	int		i;

	mini->cmd = NULL;
	i = skip_white_spaces(mini, 0);
	while (mini->line[i] != '\0' || i <= ft_strlen(mini->line))
	{
		if (mini->line[i] == '\'' || mini->line[i] == '"')
			i = take_quotes(mini, &mini->cmd, i);
		else if (mini->line[i] == '<' || mini->line[i] == '>')
			i = take_rediraction(mini, &mini->cmd, i);
		else if (mini->line[i] == '|')
			i = take_pipe(mini, &mini->cmd, i);
		else if (mini->line[i] == '$')
			i = take_var(mini, i);
		else if (mini->line[i] == '-')
			i = take_flag(mini, &mini->cmd, i);
		else if (ft_isalnum(mini->line[i]))
			i = take_word(mini, i);
		else if (ft_isspace(mini->line[i]))
			i = skip_white_spaces(mini, i);
		else
			i = take_other(mini, &mini->cmd, i);
	}
}
