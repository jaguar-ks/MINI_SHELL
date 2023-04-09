/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:22:04 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/09 01:22:50 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*merge_star(char *str)
{
	char	**splt;
	char	*r;
	int		i;

	i = -1;
	r = NULL;
	if (str[0] == '*')
		r = ft_strjoin(r, ft_strdup("*"));
	splt = ft_split(str, '*');
	while (splt[++i])
	{
		r = ft_strjoin(r, ft_strdup(splt[i]));
		if (splt[i + 1])
			r = ft_strjoin(r, ft_strdup("*"));
		else if (str[ft_strlen(str) - 1] == '*')
			r = ft_strjoin(r, ft_strdup("*"));
	}
	deallocate(splt);
	return (r);
}

int	is_a_match(char *name, char *pattren)
{
	if (!name[0] && !pattren[0])
		return (1);
	if (pattren[0] == '*' && pattren[1] && !name[0])
		return (0);
	if (pattren[0] == name[0])
		return (is_a_match(&name[1], &pattren[1]));
	if (pattren[0] == '*')
		return (is_a_match(&name[0], &pattren[1])
			|| is_a_match(&name[1], &pattren[0]));
	return (0);
}

void	extract_and_add_to_list(t_list **new_lst, char *ex)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*ptrn;

	dir = opendir(".");
	if (!dir)
		return ((void)perror("Opendir :"));
	ptrn = merge_star(ex);
	entry = readdir(dir);
	if (!entry)
		return ((void)perror("Readdir : "));
	while (entry)
	{
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
		{
			entry = readdir(dir);
			continue ;
		}
		if ((ptrn[0] == '*' && ptrn[1] == '\0')
			|| is_a_match(entry->d_name, ptrn))
			ft_lstadd_back(new_lst, ft_lstnew(entry->d_name, ARG));
		entry = readdir(dir);
	}
	free(ptrn);
	closedir(dir);
}

void	extract_wild_card(t_minishell *mini)
{
	t_list	*tmp;
	t_list	*new_cmd_lst;

	tmp = mini->cmd;
	new_cmd_lst = NULL;
	while (tmp)
	{
		if (tmp->wt == ARG && ft_strchr(tmp->pt, '*'))
			extract_and_add_to_list(&new_cmd_lst, tmp->pt);
		else
			ft_lstadd_back(&new_cmd_lst, dup_node(tmp));
		tmp = tmp->next;
	}
	ft_lstclear(&mini->cmd);
	mini->cmd = new_cmd_lst;
}
