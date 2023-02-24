/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:56:09 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/24 15:21:34 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

char	*take_lemiter(t_minishell *mini, int *i, int *exp_ch)
{
	char	*lim;
	int		j;

	*i = skip_white_spaces(mini, *i);
	j = *i;
	if (mini->line[*i] == '\'' || mini->line[*i] == '"')
	{
		while (mini->line[++j])
			if (mini->line[j] == mini->line[*i])
				break ;
		lim = ft_substr(mini->line, *i + 1, j - *i - 1);
		*exp_ch = 0;
		j++;
	}
	else
	{
		while (mini->line[++j])
			if (ft_isspace(mini->line[j]))
				break ;
		lim = ft_substr(mini->line, *i, j - *i);
		*exp_ch = 1;
	}
	*i = j;
	return (lim);
}

char	*take_heredoc_line(char *line, t_minishell *mini)
{
	int		j;
	int		x;
	char	*r;

	j = 0;
	r = NULL;
	while (1)
	{
		x = j;
		while (line[j])
		{
			if (line[j] == '$')
				break ;
			j++;
		}
		r = ft_strjoin(r, ft_substr(line, x, j - x));
		if (line[j] == '$')
			r = ft_strjoin(r, take_dollar(mini, line, &j));
	}
	return (free(line), r);
}

void	take_heredoc(t_minishell *mini, t_list **cmd, int *i)
{
	char	*herdoc;
	char	*lim;
	char	*line;
	int		exp_ch;

	lim = take_lemiter(mini, i, &exp_ch);
	herdoc = NULL;
	while (1)
	{
		line = readline("[HEREDOC]> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, lim, ft_strlen(lim)))
		{
			free(line);
			break ;
		}
		if (exp_ch == 1)
			line = take_heredoc_line(line, mini);
		herdoc = ft_strjoin(herdoc, ft_strjoin(line, ft_strdup("\n")));
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
			if (mini->line[j] == mini->line[i])
				break ;
		fl = ft_substr(mini->line, i + 1, j - i - 1);
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