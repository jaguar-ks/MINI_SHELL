/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:56:09 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 17:34:26 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

char	*take_lemiter(t_minishell *mini, int *i)
{
	char	*lim;
	int		j;

	*i = skip_white_spaces(mini, *i);
	j = *i;
	if (mini->line[*i] == '\'' || mini->line[*i] == '"')
	{
		while (mini->line[++j])
			if (mini->line[j] == '\'' || mini->line[j] == '"')
				break ;
		lim = ft_substr(mini->line, *i, j - *i);
		j++;
	}
	else
	{
		while (mini->line[++j])
			if (ft_isspace(mini->line[j]))
				break ;
		lim = ft_substr(mini->line, *i, j - *i - 1);
	}
	*i = j;
	return (lim);
}

void	take_heredoc(t_minishell *mini, t_list **cmd, int *i)
{
	char	*herdoc;
	char	*lim;
	char	*line;

	lim = take_lemiter(mini, i);
	while (1)
	{
		line = readline("[HEREDOC]> ");
		if (!line || !ft_strncmp(line, lim, ft_strlen(lim)))
		{
			if (line)
				free(line);
			break ;
		}
		herdoc = ft_strjoin(herdoc, line);
		free(line);
	}
	free(lim);
	ft_lstadd_back(cmd, ft_lstnew(herdoc, HEREDOC));
	free(herdoc);
}

int	take_input_fl(t_minishell *mini, t_list **cmd, int i)
{
	int		j;
	char	*fl;

	i = skip_white_spaces(mini, i);
	j = i;
	if (mini->line[i] == '\'' || mini->line[i] == '"')
	{
		while (mini->line[++j])
			if (mini->line[j] == '\'' || mini->line[j] == '"')
				break ;
		fl = ft_substr(mini->line, i, j - i);
		j++;
	}
	else
	{
		while (mini->line[++j])
			if (ft_isspace(mini->line[j]))
				break ;
		fl = ft_substr(mini->line, i, j - i);
	}
	ft_lstadd_back(cmd, ft_lstnew(fl, INPT));
	free(fl);
	return (j);
}

int	take_input(t_minishell *mini, t_list **cmd, int i)
{
	if (mini->line[i + 1] == '<')
	{
		i += 2;
		take_heredoc(mini, cmd, &i);
	}
	else
	{
		i += 1;
		i = take_input_fl(mini, cmd, i);
	}
	return (i);
}
