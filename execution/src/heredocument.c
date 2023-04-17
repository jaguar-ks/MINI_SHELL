/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/17 05:02:32 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_filename(t_exec **command)
{
	char	*tmp;
	char	*name;
	int		i;

	i = -1;
	while (++i < INT_MAX)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin(ft_strdup("/tmp/heredoc_"), tmp);
		ft_strlcpy((*command)->heredoc_filename, name, ft_strlen(name) + 1);
		free(name);
		if (access((*command)->heredoc_filename, F_OK) != 0)
			break ;
	}
	(*command)->in = open((*command)->heredoc_filename, O_CREAT | O_WRONLY, 0644);
	if ((*command)->in < 0)
		error((*command)->heredoc_filename, 1);
	return ;
}

void	open_here_doc(t_minishell *mini, t_exec *node, t_list *rdrc)
{
	(void)mini;
	char	*line;

	line = NULL;
	if (fork() == 0)
	{
		while (1)
		{
			line = readline("$> ");
			if (!line)
				exit(0);
			if (ft_strncmp(line, rdrc->pt, ft_strlen(rdrc->pt) +1) == 0)
				{free(line);close(node->in);exit(0);}
			if (rdrc->acs)
				line = expand_var(mini, line);
			ft_putendl_fd(line, node->in);
			free(line);
		}
	}
	wait(NULL);
	close(node->in);
	node->in = open(node->heredoc_filename, O_RDONLY, 0644);
	if (node->in < 0)
		error(node->heredoc_filename, 1);
	return ;
}

void	open_heredoc(t_minishell *mini, t_exec *cmd_list)
{
	t_list	*tmp2;

	while (cmd_list)
	{
		if (cmd_list->redrc)
		{
			tmp2 = cmd_list->redrc;
			while (tmp2)
			{
				if (tmp2->wt == LMTR)
				{
					heredoc_filename(&cmd_list);
					mini->open_fds[mini->fd_cnt++] = cmd_list->in;
					open_here_doc(mini, cmd_list, tmp2);
				}
				
				tmp2 = tmp2->next;
			}
		}
		cmd_list = cmd_list->next;
	}
	return ;
}
