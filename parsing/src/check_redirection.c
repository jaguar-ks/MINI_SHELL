/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:03:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 15:55:53 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	check_heredoc(char *line, int i)
{
	int	qtp;

	while (line[++i])
		if (!ft_isspace(line[i]))
			break ;
	if (line[i] == '\'' || line[i] == '"')
	{
		qtp = line[i];
		while (line[++i])
			if (line[i] == qtp)
				break ;
		if (line[i] == '\0')
			return (0);
	}
	else if (line[i] == '&' || line[i] == '|' || line[i] == ';'
		|| line[i] == '<' || line[i] == '>' || line[i] == '#'
		|| line[i] == '(' || line[i] == ')' || line[i] == '\0')
		return (0);
	return (1);
}

int	check_input(char *line, int i)
{
	int	qtp;

	if (line[i + 1] == '<')
		return (check_heredoc(line, i + 1));
	else
	{
		while (line[++i])
			if (!ft_isspace(line[i]))
				break ;
		if (line[i] == '\'' || line[i] == '"')
		{
			qtp = line[i];
			while (line[++i])
				if (line[i] == qtp)
					break ;
			if (line[i] == '\0')
				return (0);
		}
		else if (line[i] == '&' || line[i] == '|' || line[i] == ';'
			|| line[i] == '<' || line[i] == '>' || line[i] == '#'
			|| line[i] == '(' || line[i] == ')' || line[i] == '\0')
			return (0);
	}
	return (1);
}

int	check_output(char *line, int i)
{
	int	qtp;

	if (line[i + 1] == '>')
		i++;
	while (line[++i])
		if (!ft_isspace(line[i]))
			break ;
	if (line[i] == '\'' || line[i] == '"')
	{
		qtp = line[i];
		while (line[++i])
			if (line[i] == qtp)
				break ;
		if (line[i] == '\0')
			return (0);
	}
	else if (line[i] == '&' || line[i] == '|' || line[i] == ';'
		|| line[i] == '<' || line[i] == '>' || line[i] == '#'
		|| line[i] == '(' || line[i] == ')' || line[i] == '\0')
		return (0);
	return (1);
}

int	valid_rediraction(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' && !in_quotes(line, i))
		{
			if (!check_input(line, i))
				return (0);
			else
				if (line[i + 1] == '<')
					i++;
		}
		else if (line[i] == '>' && !in_quotes(line, i))
		{
			if (!check_output(line, i))
				return (0);
			else
				if (line[i + 1] == '>')
					i++;
		}
	}
	return (1);
}
