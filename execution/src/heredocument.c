/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/12 06:59:02 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_filename(t_minishell **mini)
{
	char	*tmp;
	char	*name;
	int		i;

	i = -1;
	while (++i < 1000)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin(ft_strdup("/tmp/heredoc_"), tmp);
		ft_strlcpy((*mini)->filename, name, ft_strlen(name) + 4);
		free(name);
		if (access((*mini)->filename, F_OK) != 0)
			return ;
	}
	return ;
}

void	open_here_doc(t_minishell *mini, int *fd)
{
	char	*line;

	heredoc_filename(&mini);
	printf("%s\n", mini->filename);
	*fd = open(mini->filename, O_CREAT | O_RDWR, 0644);
	if (*fd < 0)
		{perror("Minishell_open_here_doc");return;}
	while (1)
	{
		line = gnl(0);
		if (!line)
			break;
		if (ft_strncmp(line, mini->exc->redrc->pt, ft_strlen(mini->exc->redrc->pt)) == 0)
			break ;
		if (mini->exc->redrc->acs == 1)
			line = expand_var(mini, line);
		if (line)
			ft_putendl_fd(line, *fd);
		else if (!line)
			write(*fd, "\n", 1);	
		free(line);
	}
	close(*fd);
	*fd = open(mini->filename, O_CREAT | O_RDWR, 0644);
	if (*fd < 0)
	{
		perror("Minishell_open_here_doc");
		return ;
	}
	return ;
}
