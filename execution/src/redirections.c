/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:42:01 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/17 04:42:06 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	open_pipes(t_minishell *mini, t_exec *pipeline)
{
	int	fd[2];
	int	i;

	i = 0;
	pipeline->in = -1;
	while (pipeline)
	{
		if (pipe(fd))
			{perror("pipe");exit(1);}
		mini->open_fds[mini->fd_cnt++] = fd[0];
		mini->open_fds[mini->fd_cnt++] = fd[1];
		if (pipeline->next)
		{
			pipeline->next->in = fd[0];
			pipeline->out = fd[1];
		}
		// printf("in %d | out %d | i = %d\n", pipeline->in, pipeline->out, i);
		i++;
		pipeline = pipeline->next;
	}
	return ;
}

// void	handle_redirections(t_minishell *mini, t_exec *exec_cmd)
// {
// 	int fd;
// 	t_list *tmp;

// 	fd = 0;
// 	tmp = exec_cmd->redrc;
// 	signal(SIGINT, handl_segint_child);
// 	while (tmp)
// 	{
// 		if (tmp->wt == IN_F)
// 		{
// 			fd = open(tmp->pt, O_RDONLY);
// 				error("Minishell_redrc1", 1);
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (tmp->wt == AP_F || tmp->wt == TR_F)
// 		{
// 			if (tmp->wt == TR_F)
// 				fd = open(tmp->pt, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
// 			else
// 				fd = open(tmp->pt, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0644);
// 			if (fd == -1)
// 				error("Minishell_redrc2", 1);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return;
// }
