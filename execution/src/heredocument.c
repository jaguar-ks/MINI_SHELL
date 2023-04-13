/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/13 02:16:27 by mfouadi          ###   ########.fr       */
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
		ft_strlcpy((*mini)->filename, name, ft_strlen(name)+1);
		free(name);
		if (access((*mini)->filename, F_OK) != 0)
			return ;
	}
	return ;
}

void	open_here_doc(t_minishell *mini, t_list *node, int *fd, int dupp)
{
	char	*line;

	if (mini && mini->exc)
	{heredoc_filename(&mini);
	*fd = open(mini->filename, O_CREAT | O_RDWR, 0644);
	if (*fd < 0)
		{perror("Minishell_open_here_doc");return;}
	dup2(dupp, STDIN_FILENO);
	int du = dup(STDOUT_FILENO);
	// printf("%s\n", mini->filename);
	while (1)
	{
		dup2(STDIN_FILENO, STDOUT_FILENO);
		line = readline("Minishell> ");
		if (!line)
			break;
		if (ft_strncmp(line, node->pt, ft_strlen(node->pt) + 1) == 0)
			break ;
		if (node->acs == 1)
			line = expand_var(mini, line);
		ft_putendl_fd(line, *fd);
		free(line);
	}
	dup2(du, STDOUT_FILENO);
	close(*fd);
	*fd = open(mini->filename, O_CREAT | O_RDWR, 0644);
	if (*fd < 0)
	{
		perror("Minishell_open_here_doc");
		return ;
	}}
	return ;
}
