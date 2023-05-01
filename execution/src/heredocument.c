/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:56:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/01 20:36:02 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// **	Returns a heredocument filename that doesn't exist yet
// static void	_heredoc_filename(t_exec **command)
// {
// 	char	*tmp;
// 	char	*name;
// 	int		i;

// 	i = -1;
// 	while (++i < INT_MAX)
// 	{
// 		tmp = ft_itoa(i);
// 		name = ft_strjoin(ft_strdup("/tmp/heredoc_"), tmp);
// 		ft_strlcpy((*command)->heredoc_filename, name, ft_strlen(name) + 1);
// 		free(name);
// 		if (access((*command)->heredoc_filename, F_OK) != 0)
// 			break ;
// 	}
// 	(*command)->in = open((*command)->heredoc_filename,
// 			O_CREAT | O_WRONLY, 0644);
// 	if ((*command)->in < 0)
// 		error((*command)->heredoc_filename, 1);
// 	return ;
// }

// **	Read from STDIN until encountring DELIMITER or NULL
// static void	_open_here_doc(t_minishell *mini, t_exec *node, t_list *rdrc)
// {
// 	char	*line;

// 	line = NULL;
// 	if (fork() == 0)
// 	{
// 		while (1)
// 		{
// 			line = readline("$> ");
// 			if (!line)
// 				exit(0);
// 			if (ft_strncmp(line, rdrc->pt, ft_strlen(rdrc->pt) + 1) == 0)
// 				return (free(line), close(node->in), exit(0));
// 			if (rdrc->acs)
// 				line = expand_var(mini, line);
// 			ft_putendl_fd(line, node->in);
// 			free(line);
// 		}
// 	}
// 	wait(NULL);
// 	close(node->in);
// 	node->in = open(node->heredoc_filename, O_RDONLY, 0644);
// 	if (node->in < 0)
// 		error(node->heredoc_filename, 1);
// 	return ;
// }

// ** Opens redirections '<' '>' '>>'
static inline int	_handle_redirections(t_minishell *mini, t_list *token,
	int *in, int *out)
{
	t_list	*tmp;

	tmp = token;
	if (tmp->wt == IN_F)
	{
		*in = open(tmp->pt, O_RDONLY);
		if (*in == -1)
			return (*mini->ext_st = error(tmp->pt, 1), g_ext_st);
		mini->open_fds[mini->fd_cnt++] = *in;
	}
	else if (tmp->wt == AP_F || tmp->wt == TR_F)
	{
		if (tmp->wt == TR_F)
			*out = open(tmp->pt, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
		else
			*out = open(tmp->pt, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY,
					0644);
		if (*out == -1)
			return (*mini->ext_st = error(tmp->pt, 1), g_ext_st);
		mini->open_fds[mini->fd_cnt++] = *out;
	}
	return (0);
}

/*	
	Opens redirections '<' '>' '>>', and heredoc '<<' which is stored 
	in a tmp file for later use in execute_pipeline()
*/
void	open_heredoc_and_redirections(t_minishell *mini, t_exec *pipeline)
{
	t_list	*tmp2;

	while (pipeline)
	{
		if (pipeline->redrc)
		{
			tmp2 = pipeline->redrc;
			while (tmp2)
			{
				if (!pipeline->rdrct_err)
					pipeline->rdrct_err = _handle_redirections(mini, tmp2,
							&pipeline->in, &pipeline->out);
				tmp2 = tmp2->next;
			}
		}
		pipeline = pipeline->next;
	}
	return ;
}
