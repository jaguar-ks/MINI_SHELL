/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redirction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:36:17 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/21 15:59:28 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

void	take_redirection(t_minishell *mini, t_list **cmd, int *i)
{
	int	tp;

	if (mini->line[*i] == '<')
		take_input(mini, cmd, i);
	else
		take_output(mini, cmd, i);
}
