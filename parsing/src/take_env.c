/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:52:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/23 18:44:36 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

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
			tmp->pt = lvl;
			return ;
		}
		tmp = tmp->next;
	}
}

t_list	*take_env(char **en)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	i = -1;
	while (en[++i])
		ft_lstadd_back(&env, ft_lstnew(en[i], EN));
	incriment_shell_lvl(&env);
	tmp = env;
	return (env);
}
