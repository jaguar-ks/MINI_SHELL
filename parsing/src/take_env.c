/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:52:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/21 18:03:47 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

t_list	*take_env(char **en)
{
	t_list	*env;
	int		i;

	i = -1;
	while (en[++i])
		ft_lstadd_back(&env, ft_lstnew(en[i], EN));
	return (env);
}
