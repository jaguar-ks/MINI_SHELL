/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:28:55 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/23 15:29:56 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*take_wrd(t_minishell *mini, int *i)
{
	char	*str;
	int		j;

	j = *i;
	while (mini->line[++j])
		if (mini->line[j] == '$' || mini->line[j] == '"'
			|| mini->line[j] == '|' || mini->line[j] == '<'
			|| mini->line[j] == '>' || mini->line[j] == '\''
			|| mini->line[j] == ' ')
			break ;
	str = ft_substr(mini->line, *i, j - (*i));
	*i = j;
	return (str);
}

int	take_word(t_minishell *mini, int i)
{
	char	*wrd;

	wrd = take_wrd(mini, &i);
	ft_lstadd_back(&mini->cmd, ft_lstnew(wrd, WRD));
	free(wrd);
	return (i);
}
