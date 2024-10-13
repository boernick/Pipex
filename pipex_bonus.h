/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:59:34 by nboer             #+#    #+#             */
/*   Updated: 2024/10/13 20:24:12 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
// # include "/home/nick/42Berlin/Pipex/includes/ft_printf/ft_printf.h"
// # include "/home/nick/42Berlin/Pipex/includes/Libft/libft.h"
# include "/home/nboer/git/Pipex/includes/ft_printf/ft_printf.h"
# include "/home/nboer/git/Pipex/includes/Libft/libft.h"

int		str_error(char *error);
void	free_array(char **array);
char	*path_join(char *path_split, char *cmd_arg);
void	run_ex(char *arg, char **path_env);

#endif
