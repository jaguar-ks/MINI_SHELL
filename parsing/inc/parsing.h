/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 18:14:05 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"../../libtool/inc/libft.h"

# define EMPTY 0
# define HEREDOC 1
# define CMD 2
# define FL 3
# define APND 4
# define TRNC 5
# define INPT 6
# define FLG 7
# define ENV 8

/*Store the environment*/
t_list	*take_env(char **en);

#endif
