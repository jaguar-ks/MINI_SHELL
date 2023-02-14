/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_cmd_ln.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:12:55 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 19:40:09 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

char	*get_path(t_list *en, char *cm)
{
	char	**pth;
	char	*r;
	char	*cmd;
	int		i;

	i = 0;
	while (ft_strncmp((en->pt), "PATH", 4))
		en = en->next;
	pth = ft_split((en->pt + 5), ':');
	i = -1;
	cmd = ft_strjoin("/", cm);
	while (pth[++i])
	{
		r = ft_strjoin(pth[i], cmd);
		if (!access(r, (X_OK)))
			break ;
		free(r);
		r = NULL;
	}
	return (deallocate(pth), free(cmd), r);
}

int	type_of_wrd(char *wrd, t_list *env, int prv)
{
	if (!ft_strncmp(wrd, "", 1))
		return (EMPTY);
	else if (!ft_strncmp(wrd, "|", 2))
		return (PP);
	else if (!ft_strncmp(wrd, ">", 2))
		return (TRNC);
	else if (!ft_strncmp(wrd, ">>", 3))
		return (APND);
	else if (!ft_strncmp(wrd, "<", 2))
		return (INPT);
	else if (!ft_strncmp(wrd, "<<", 3))
		return (HEREDOC);
	else if (prv == HEREDOC)
		return (LM);
	else if (!ft_strncmp(wrd, "$", 1) && ft_strlen(wrd) > 1)
		return (VRB);
	else if (get_path(env, wrd) && prv == -1)
		return (CMD);
	else
		return (ARG);
}

t_list	*take_cmd_ln(char *cmd_ln, t_list *env)
{
	char 	**cm_ln;
	t_list	*cl;
	int		i;
	int		tp;

	cm_ln = ft_split(cmd_ln, ' ');
	i = -1;
	tp = i;
	while (cm_ln[++i])
	{
		tp = type_of_wrd(cm_ln[i], env, tp);
		ft_lstadd_back(&cl, ft_lstnew(cm_ln[i], tp));
		if (tp == PP)
			tp = -1;
	}
}
