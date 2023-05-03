/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:05:30 by faksouss          #+#    #+#             */
/*   Updated: 2023/05/02 20:05:41 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

static char	*expand_hd(t_minishell *mini, char *old_str)
{
	int		i;
	int		s;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (1)
	{
		s = i;
		while (old_str[i])
		{
			if (old_str[i] == '$')
				break ;
			i++;
		}
		if (i > s)
			new_str = ft_strjoin(new_str, ft_substr(old_str, s, i - s));
		if (old_str[i] == '$')
			new_str = ft_strjoin(new_str, take_dollar(mini, old_str, &i));
		if (old_str[i] == '\0')
			break ;
	}
	return (free(old_str), new_str);
}

static char	*_heredoc_filename(void)
{
	char	*tmp;
	char	*name;
	int		i;

	i = -1;
	while (++i < INT_MAX)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin(ft_strdup("/tmp/heredoc_"), tmp);
		if (access(name, F_OK) != 0)
			break ;
		else
			free(name);
	}
	return (name);
}

static void	read_heredoc(t_minishell *mini, t_list *hd)
{
	char	*line;
	char	*name;
	int		fd;

	line = NULL;
	name = _heredoc_filename();
	if (!fork())
	{
		signal(SIGINT, handl_segint_child);
		fd = open(name, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			exit(error(name, 1));
		while (1)
		{
			line = readline("$> ");
			if (!line || ft_strncmp(line, hd->pt, ft_strlen(hd->pt) + 1) == 0)
				return (free(line), exit(EXIT_SUCCESS));
			if (hd->acs)
				line = expand_hd(mini, line);
			ft_putendl_fd(line, fd);
			free(line);
		}
	}
	hd->wt = (wait(NULL), free(hd->pt), hd->pt = name, IN_F);
}

void	take_heredoc(t_minishell *mini)
{
	t_exec	*tmp;
	t_list	*tmp_rdrct;

	tmp = mini->exc;
	while (tmp)
	{
		tmp_rdrct = tmp->redrc;
		while (tmp_rdrct)
		{
			if (tmp_rdrct->wt == LMTR)
				read_heredoc(mini, tmp_rdrct);
			tmp_rdrct = tmp_rdrct->next;
		}
		tmp = tmp->next;
	}
}
