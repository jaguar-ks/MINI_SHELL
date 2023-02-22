/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:15:28 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:20 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	take_flag(t_minishell *mini, t_list **cmd, int i)
{
	char	*flg;
	int		j;

	j = i + 1;
	while (mini->line[j])
	{
		if (ft_isspace(mini->line[j]) || (!ft_isalnum(mini->line[j])
				&& mini->line[j] != '='))
			break ;
		j++;
	}
	flg = ft_substr(mini->line, i, j - i);
	ft_lstadd_back(cmd, ft_lstnew(flg, FLG));
	free(flg);
	return (j);
}
