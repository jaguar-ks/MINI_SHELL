/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:52:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/01 15:32:03 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

void	identify_special_charcters(t_minishell *mini)
{
	t_list	*tmp;

	tmp = mini->cmd;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "<<", 3))
			tmp->wt = HEREDOC;
		else if (!ft_strncmp(tmp->pt, "<", 2))
			tmp->wt = INPT;
		else if (!ft_strncmp(tmp->pt, ">>", 3))
			tmp->wt = APND;
		else if (!ft_strncmp(tmp->pt, ">", 2))
			tmp->wt = TRNC;
		else if (!ft_strncmp(tmp->pt, "|", 2))
			tmp->wt = PP;
		tmp = tmp->next;
	}
}

void	incriment_shell_lvl(t_list **env)
{
	t_list	*tmp;
	char	*lvl;

	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->pt, "SHLVL=", ft_strlen(tmp->pt)))
		{
			lvl = ft_strjoin(ft_strdup("SHLVL="),
					ft_itoa(ft_atoi(tmp->pt + 6) + 1));
			free(tmp->pt);
			tmp->pt = ft_strdup(lvl);
			free(lvl);
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_shell(t_list **env)
{
	t_list	*tmp;
	char	*shl;

	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->pt, "SHELL=", ft_strlen(tmp->pt)))
		{
			shl = ft_strjoin(ft_strdup("SHELL="),
					ft_strdup("/Users/faksouss/Desktop/mini_shell"));
			free(tmp->pt);
			tmp->pt = ft_strdup(shl);
			free(shl);
			return ;
		}
		tmp = tmp->next;
	}
}

t_list	*take_env(char **en)
{
	t_list	*env;
	int		i;

	i = -1;
	env = NULL;
	while (en[++i])
		ft_lstadd_back(&env, ft_lstnew(en[i], EN));
	incriment_shell_lvl(&env);
	change_shell(&env);
	return (env);
}
