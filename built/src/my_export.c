/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:06:38 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/10 03:00:54 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	is_export(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD)
			if (!ft_strncmp(tmp->pt, "export", 7))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	sort_env(t_list *env)
{
	t_list	*tmp;
	t_list	*tmp1;
	char	*swp;

	tmp = env;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			if (tmp1 && ft_strcmp(tmp->pt, tmp1->pt) > 0)
			{
				swp = tmp->pt;
				tmp->pt = tmp1->pt;
				tmp1->pt = swp;
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}

void	print_export(t_list *exp)
{
	t_list	*tmp;

	sort_env(exp);
	tmp = exp;
	while (tmp)
	{
		if (tmp->acs)
			ft_printf("declare - x %s\n", STDOUT_FILENO, tmp->pt);
		tmp = tmp->next;
	}
}

void	take_export(t_list **exp, t_list *en)
{
	t_list	*tmp;
	char	*prt;

	tmp = en;
	while (tmp)
	{
		ft_lstadd_back(exp, dup_node(tmp));
		if (ft_strchr(ft_lstlast(*exp)->pt, '='))
		{
			prt = ft_strjoin(ft_strjoin(ft_substr(ft_lstlast(*exp)->pt, 0,
							ft_strchr(ft_lstlast(*exp)->pt,
								'=') - ft_lstlast(*exp)->pt + 1),
						ft_strdup("\"")),
					ft_strjoin(ft_substr(ft_strchr(ft_lstlast(*exp)->pt,
								'='), 1,
							ft_strlen(ft_strchr(ft_lstlast(*exp)->pt,
									'='))), ft_strdup("\"")));
			free(ft_lstlast(*exp)->pt);
			ft_lstlast(*exp)->pt = prt;
		}
		tmp = tmp->next;
	}
}

void	my_export(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	t_list	*exp;

	cm = take_char_cmd(cmd);
	exp = NULL;
	take_export(&exp, mini->env);
	if (!cm[1])
		print_export(exp);
	ft_lstclear(&exp);
	deallocate(cm);
}
