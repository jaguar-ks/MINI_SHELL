/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_list_to_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:33:49 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/10 08:27:43 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

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
