/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 01:05:52 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/06 21:45:01 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			break ;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

int	in_quotes(char *line, int i)
{
	int	j;
	int	in_s;
	int	in_d;

	j = -1;
	in_s = 0;
	in_d = 0;
	while (line[++j])
	{
		if (line[j] == '\'')
			in_s = (in_s == 0);
		if (line[j] == '"')
			in_d = (in_d == 0);
		if (j == i)
			break ;
	}
	return ((in_s || in_d));
}

int	valid_ct(char *cl)
{
	int	i;
	int	j;

	i = 0;
	while (cl[i])
	{
		if (cl[i] == '\'' || cl[i] == '"')
		{
			j = i;
			while (cl[++j])
				if (cl[j] == cl[i])
					break ;
			if (cl[j] == '\0')
				return (0);
			i = j;
		}
		i++;
	}
	return (1);
}

int	valid_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (0);
	while (line[++i])
	{
		if (line[i] == '|' && !in_quotes(line, i))
		{
			while (line[++i])
				if (!ft_isspace(line[i]) || line[i] == '|')
					break ;
			if (line[i] == '\0' || line[i] == '|')
				return (0);
		}
	}
	return (1);
}

int	check_syntax(char *line)
{
	if (empty_line(line))
		return (0);
	else if (!valid_ct(line))
		return (258);
	else if (!valid_rediraction(line))
		return (258);
	else if (!valid_pipe(line))
		return (258);
	else
		return (0);
}
