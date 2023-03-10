/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub_fncts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:02:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/10 08:02:06 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

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

int	check_export_syntax(char *str, int *ext_st)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (ft_printf("Minishell : not a valid identifier : %s\n", 2, str),
			*ext_st = 256, 0);
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
	if ((str[i] == '+' && str[i + 1] != '=') || str[i] != '='
		|| str[i] != '\0')
		return (ft_printf("Minishell : not a valid identifier : %s\n", 2, str),
			*ext_st = 256, 0);
	return (1);
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
