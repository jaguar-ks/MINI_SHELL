/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_rdrct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:14:56 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/27 12:04:11 by faksouss         ###   ########.fr       */
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
		exit(error(file, 1));
}

void	open_heredoc(t_list *lim, t_minishell *mini, int *fl)
{
	int		pid;
	int		fd[2];
	char	*r;

	r = NULL;
	if (pipe(fd) < 0)
		exit(error("pipe", errno));
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("Heredoc > ", 2);
			r = gnl(0);
			if (!r || !ft_strcmp(r, lim->pt))
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

void	open_output(t_list *fl, int *fd)
{
	if (fl->wt == TR_F)
		*fd = open(fl->pt, (O_CREAT | O_TRUNC | O_WRONLY), 0777);
	else if (fl->wt == AP_F)
		*fd = open(fl->pt, (O_CREAT | O_APPEND | O_WRONLY), 0777);
	if (*fd < 0)
		exit(error(fl->pt, 1));
}

void	open_rdrct(t_list *cmd, t_minishell *mini)
{
	int		in;
	int		out;
	t_list	*tmp;

	tmp = cmd;
	in = -1;
	out = -1;
	while (tmp)
	{
		if (tmp->wt == APND || tmp->wt == TRNC)
			open_output(tmp->next, &out);
		if (tmp->wt == INPT)
			open_input(tmp->next->pt, &in);
		else if (tmp->wt == HEREDOC)
			open_heredoc(tmp->next, mini, &in);
		tmp = tmp->next;
	}
	if (in > 0)
		dup2(in, STDIN_FILENO);
	if (out > 0)
		dup2(out, STDOUT_FILENO);
}
