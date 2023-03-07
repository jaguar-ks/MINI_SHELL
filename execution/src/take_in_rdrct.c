/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_in_rdrct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:40:44 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/07 04:04:49 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	check_in_rdrct(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == HEREDOC || tmp->wt == INPT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	open_input(char *file, int *fd)
{
	*fd = open(file, O_RDONLY, 0777);
	if (*fd < 0)
		exit(error(file));
}

void	open_heredoc(t_list *lim, t_minishell *mini, int *fl)
{
	int		pid;
	int		fd[2];
	char	*r;

	r = NULL;
	if (pipe(fd) < 0)
		exit(error("pipe"));
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			r = readline("Heredoc > ");
			if (!r || !ft_strncmp(r, lim->pt, ft_strlen(r)))
				exit(EXIT_SUCCESS);
			if (lim->acs)
				r = expand_var(mini, r);
			ft_putendl_fd(r, fd[1]);
			free(r);
		}
	}
	else
		*fl = (close(fd[1]), waitpid(pid, NULL, 0), fd[0]);
}

void	take_input(t_list *cmd, t_minishell *mini)
{
	int		fd;
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == INPT)
			open_input(tmp->next->pt, &fd);
		else if (tmp->wt == HEREDOC)
			open_heredoc(tmp->next, mini, &fd);
		tmp = tmp->next;
	}
	dup2(fd, STDIN_FILENO);
}
