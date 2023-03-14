/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 02:39:28 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/14 11:52:28 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

char	*get_path(char **pth, char *cm)
{
	char	*r;
	char	*cmd;
	int		i;

	i = -1;
	cmd = ft_strjoin(ft_strdup("/"), ft_strdup(cm));
	while (pth[++i])
	{
		r = ft_strjoin(ft_strdup(pth[i]), ft_strdup(cmd));
		if (access(r, (X_OK)) == 0)
			break ;
		free(r);
		r = NULL;
	}
	return (deallocate(pth), free(cmd), r);
}

char	**take_env_pths(t_list *en)
{
	t_list	*tmp;
	char	**pths;

	pths = NULL;
	tmp = en;
	while (tmp)
	{
		if (!ft_strncmp(tmp->pt, "PATH=", 5))
			if (tmp->acs)
				break ;
		tmp = tmp->next;
	}
	if (tmp)
		pths = ft_split(tmp->pt + 5, ':');
	return (pths);
}

char	*find_path(char	*cm, t_list *en)
{
	char	*cm_pth;
	char	**env_pths;

	if (!cm || !ft_strlen(cm))
		return (NULL);
	env_pths = NULL;
	cm_pth = NULL;
	env_pths = take_env_pths(en);
	if (!env_pths)
		return (NULL);
	cm_pth = get_path(env_pths, cm);
	return (cm_pth);
}

char	*take_path(char *cm, t_minishell *mini)
{
	if (ft_strchr(cm, '/'))
	{
		if (!access(cm, X_OK))
			return (ft_strdup(cm));
		else
			return (NULL);
	}
	else
		return (find_path(cm, mini->env));
}
