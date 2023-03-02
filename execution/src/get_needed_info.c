/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_needed_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:33 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/02 19:33:21 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

int	error(char *er)
{
	ft_printf("MiniShell : %s : %s\n", STDERR_FILENO, strerror(errno), er);
	return (errno);
}

void	heredoc(t_list *lim, t_minishell *mini)
{
	int		pid;
	int		fd[2];
	char	*r;

	if (pipe(fd) < 0)
		exit(error("Pipe"));
	pid = fork();
	while (!pid)
	{
		close(fd[0]);
		r = readline("HEREDOC > ");
		if (!r || !ft_strncmp(lim->pt, r, ft_strlen(lim->pt)))
			exit(EXIT_SUCCESS);
		if (lim->acs)
			r = expand_var(mini, r);
		ft_putendl_fd(r, fd[1]);
		free(r);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

void	open_input(t_list *cmd, t_minishell *mini)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == INPT)
		{
			fd = open(tmp->next->pt, O_RDWR, 0777);
			if (fd < 0)
				exit(error(tmp->next->pt));
			dup2(fd, STDIN_FILENO);
		}
		if (tmp->wt == HEREDOC)
			heredoc(tmp->next, mini);
		tmp = tmp->next;
	}
}

void	open_output(t_list *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == TRNC || tmp->wt == APND)
		{
			if (tmp->wt == TRNC)
				fd = open(tmp->next->pt, (O_CREAT | O_TRUNC | O_RDWR), 0777);
			else
				fd = open(tmp->next->pt, (O_CREAT | O_APPEND | O_RDWR), 0777);
			if (fd < 0)
				exit(error(tmp->next->pt));
			dup2(fd, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}

char	**take_cmd_char(t_list *cmd)
{
	t_list	*tmp;
	char	**r;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->wt == CMD || tmp->wt == ARG || tmp->wt == FLG)
			i++;
		tmp = tmp->next;
	}
	r = (char **)malloc(sizeof(char *) * (i + 1));
	if (!r)
		return (NULL);
	tmp = cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->wt == CMD || tmp->wt == FLG || tmp->wt == ARG)
		{
			r[i] = ft_strdup(tmp->pt);
			i++;
		}
		tmp = tmp->next;
	}
	r[i] = NULL;
	return (r);
}

char	*take_path(char *cm, char **en)
{
	char	**pth;
	char	*r;
	char	*cmd;
	int		i;

	i = 0;
	while (ft_strncmp((en[i]), "PATH", 4))
		i++;
	pth = ft_split((en[i] + 5), ':');
	i = -1;
	cmd = ft_strjoin(ft_strdup("/"), cm);
	while (pth[++i])
	{
		r = ft_strjoin(ft_strdup(pth[i]), ft_strdup(cmd));
		if (access(r, X_OK) == 0)
			break ;
		free(r);
		r = NULL;
	}
	return (deallocate(pth), free(cmd), r);
}

void	execute(t_list *env, t_list *cmd, t_minishell *mini)
{
	char	**cm;
	char	**en;
	char	*pth;

	cm = NULL;
	en = NULL;
	en = take_char_env(env);
	open_input(cmd, mini);
	open_output(cmd);
	cm = take_cmd_char(cmd);
	if (access(cm[0], X_OK) == 0)
		pth = cm[0];
	else
		pth = take_path(ft_strdup(cm[0]), en);
	if (!pth)
	{
		ft_printf("MiniShell : command not found : %s\n", 2, cm[0]);
		deallocate(cm);
		ft_lstclear(&cmd);
		exit(127);
	}
	if (execve(pth, cm, en) < 0)
		exit(error("execve"));
}

void	do_cmd(t_minishell *mini)
{
	int		pid;
	t_list	*cmd;

	while (1)
	{
		cmd = single_cmd(mini);
		if (!cmd)
			break ;
		if (pipe(mini->fd) < 0)
			exit(error("pipe"));
		pid = fork();
		if (!pid)
		{
			close(mini->fd[0]);
			// dup2(mini->fd[1], STDOUT_FILENO);
			execute(mini->env, cmd, mini);
		}
		else
		{
			close(mini->fd[1]);
			// dup2(mini->fd[0], STDIN_FILENO);
			waitpid(pid, &mini->ext_st, 0);
		}
	}
}
