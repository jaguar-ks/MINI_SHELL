/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_char_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:11:24 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/11 05:29:46 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	env_len(t_list *en)
{
	t_list	*tmp;
	int		ct;

	ct = 0;
	tmp = en;
	while (tmp)
	{
		if (tmp->acs)
			ct++;
		tmp = tmp->next;
	}
	return (ct);
}

char	**take_char_env(t_list *en)
{
	t_list	*tmp;
	char	**env;
	int		i;

	env = (char **)malloc(sizeof(char *) * (env_len(en) + 1));
	if (!env)
		return (NULL);
	i = 0;
	tmp = en;
	while (tmp)
	{
		if (tmp->acs && ft_strchr(tmp->pt, '='))
		{
			env[i] = ft_strdup(tmp->pt);
			i++;
		}
		if (i == env_len(en))
			break ;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

int	check_cmd(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	count_cmd_prt(t_list *cmd)
{
	t_list	*tmp;
	int		ct;

	ct = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD || tmp->wt == FLG || tmp->wt == ARG)
			ct++;
		tmp = tmp->next;
	}
	return (ct);
}

char	**take_char_cmd(t_list *cmd)
{
	t_list	*tmp;
	char	**cm;
	int		i;
	int		j;

	cm = NULL;
	i = count_cmd_prt(cmd);
	cm = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cm)
		return (NULL);
	tmp = cmd;
	j = -1;
	while (tmp)
	{
		if (tmp->wt == CMD || tmp->wt == FLG || tmp->wt == ARG)
			cm[++j] = ft_strdup(tmp->pt);
		tmp = tmp->next;
	}
	cm[j + 1] = NULL;
	return (cm);
}
