/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub_fncts_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:47:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/11 03:14:23 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

void	change_env_prt(t_minishell *mini, char *key, char *val, int tp)
{
	t_list	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (is_the_target(key, tmp->pt))
		{
			if (tp == 2)
				tmp->pt = ft_strjoin(tmp->pt, ft_strdup(val));
			else if (tp == 1)
			{
				free(tmp->pt);
				tmp->pt = ft_strjoin(ft_strjoin(ft_strdup(key), ft_strdup("=")),
						ft_strdup(val));
			}
		}
		tmp = tmp->next;
	}
}

void	bring_back_env_prt(t_minishell *mini, char *key, char *val, int tp)
{
	t_list	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (is_the_target(key, tmp->pt))
		{
			free(tmp->pt);
			if (tp)
				tmp->pt = ft_strjoin(ft_strjoin(ft_strdup(key), ft_strdup("=")),
						ft_strdup(val));
			else
				tmp->pt = ft_strdup(key);
			tmp->acs = 1;
		}
		tmp = tmp->next;
	}
}

void	add_new_env_prt(t_minishell *mini, char *key, char *val, int tp)
{
	char	*new;

	if (tp)
		new = ft_strjoin(ft_strjoin(ft_strdup(key), ft_strdup("=")),
				ft_strdup(val));
	else
		new = ft_strdup(key);
	ft_lstadd_back(&mini->env, ft_lstnew(new, EN));
	free(new);
}
