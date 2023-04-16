/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/16 00:15:47 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_filename(t_exec **mini, int *heredoc_fd)
{
	char	*tmp;
	char	*name;
	int		i;

	i = -1;
	while (++i < INT_MAX)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin(ft_strdup("/tmp/heredoc_"), tmp);
		ft_strlcpy((*mini)->heredoc_filename, name, ft_strlen(name) + 1);
		free(name);
		if (access((*mini)->heredoc_filename, F_OK) != 0)
			break ;
	}
	*heredoc_fd = open((*mini)->heredoc_filename, O_CREAT | O_WRONLY, 0644);
	if (*heredoc_fd < 0)
		error((*mini)->heredoc_filename, 1);
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
	else
		wait(NULL);
	return ;
}
