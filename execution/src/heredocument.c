/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/03 16:48:43 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// ** Opens redirections '<' '>' '>>'
static inline int	_handle_redirections(t_minishell *mini, t_list *token,
	int *in, int *out)
{
	t_list	*tmp;

	tmp = token;
	if (tmp->wt == IN_F)
	{
		*in = open(tmp->pt, O_RDONLY);
		if (*in == -1)
			return (*mini->ext_st = error(tmp->pt, 1), g_ext_st);
		mini->open_fds[mini->fd_cnt++] = *in;
	}
	else if (tmp->wt == AP_F || tmp->wt == TR_F)
	{
		if (tmp->wt == TR_F)
			*out = open(tmp->pt, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
		else
			*out = open(tmp->pt, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY,
					0644);
		if (*out == -1)
			return (*mini->ext_st = error(tmp->pt, 1), g_ext_st);
		mini->open_fds[mini->fd_cnt++] = *out;
	}
	return (0);
}

/*	
	Opens redirections '<' '>' '>>', and heredoc '<<' which is stored 
	in a tmp file for later use in execute_pipeline()
*/
void	open_redirections(t_minishell *mini, t_exec *pipeline)
{
	t_list	*tmp2;

	while (pipeline)
	{
		if (pipeline->redrc)
		{
			tmp2 = pipeline->redrc;
			while (tmp2)
			{
				if (!pipeline->rdrct_err)
					pipeline->rdrct_err = _handle_redirections(mini, tmp2,
							&pipeline->in, &pipeline->out);
				tmp2 = tmp2->next;
			}
		}
		pipeline = pipeline->next;
	}
	return ;
}
