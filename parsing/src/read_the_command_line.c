/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_command_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:26:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/16 22:54:01 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	valid_ct(char *cl)
{
	int	i;
	int	j;
	int	ct;

	i = -1;
	while (cl[++i])
	{
		if (cl[i] == 34 || cl[i] == 39)
		{
			ct = cl[i];
			j = i;
			while (cl[++j])
				if (cl[j] == ct)
					break ;
			if (cl[j] == '\0')
				return (1);
		}
	}
	return (0);
}

int	is_spc_cr(char c)
{
	if (c == 32 || c == 34 || c == 39 || c == '|' || c == '<' || c == '>'
		|| c == '-' || c == '$')
		return (1);
	else
		return (0);
}

t_list	*cmd_line(char *cl)
{
	t_list	*cml;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cl[++i])
	{
		if (!is_spc_cr(cl[i]))
		{
			while (cl[i] && !is_spc_cr(cl[i]))
				i++;
			ft_lstadd_back(&cml, ft_lstnew(ft_substr(cl, j, i - j), 0));
			j = i;
		}
		else if (is_spc_cr(cl[i]))
		{
			j = i;
			while (cl[i + 1] && !is_spc_cr(cl[i + 1]))
				i++;
			ft_lstadd_back(&cml, ft_lstnew(ft_substr(cl, j, i - j), 0));
			j = i;
		}
	}
	tmp = cml;
	while (tmp)
	{
		printf("->(%s)\n", tmp->pt);
		tmp = tmp->next;
	}
	return (cml);
}
