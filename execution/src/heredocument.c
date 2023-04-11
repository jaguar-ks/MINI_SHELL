/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/11 17:57:25 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_filename(t_data **data)
{
	char	*tmp;
	char	*name;
	int		i;

	i = -1;
	while (++i < 1000)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc_", tmp);
		free(tmp);
		ft_strlcpy((*data)->filename, name, ft_strlen(name) + 4);
		free(name);
		if (access((*data)->filename, F_OK) != 0)
			return ;
	}
	return ;
}

int	read_stdin(t_data data, int in_fd)
{
	char	*p;
	char	*tmp;

	in_fd = open(data.filename, O_CREAT | O_RDWR, 0644);
	if (in_fd < 0)
		msg("open", 2, 0);
	while (1)
	{
		p = get_next_line(0);
		tmp = ft_strtrim(p, "\n");
		if (ft_strncmp(data.av[2], tmp, ft_strlen(data.av[2]) + 1) == 0)
			break ;
		free(tmp);
		write(in_fd, p, ft_strlen(p));
		free(p);
	}
	free(tmp);
	free(p);
	close(in_fd);
	in_fd = open(data.filename, O_CREAT | O_RDWR, 0644);
	if (in_fd < 0)
		msg("open", 2, 0);
	return (in_fd);
}

// **	Reads from STDIN then writes to a file, which will be used later
// **		as the STDIN for the second command
void	here_document(t_data data, int fd[])
{
	char	**tmp;
	char	*path;
	int		in_fd;

	in_fd = 0;
	path = NULL;
	tmp = ft_split(data.av[3], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 1);
	in_fd = read_stdin(data, in_fd);
	ft_dup2(in_fd, STDIN_FILENO, "dup2");
	ft_dup2(fd[1], STDOUT_FILENO, "dup2");
	close(fd[0]);
	close(fd[1]);
	close(in_fd);
	path = path_is(data.env, data.av[3]);
	execve(path, tmp, data.env);
	msg("execve", 126, 0);
}
