/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:07:34 by nick              #+#    #+#             */
/*   Updated: 2024/11/02 23:10:46 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS2_H
# define PIPEX_BONUS2_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "../includes/ft_printf/ft_printf.h"
# include "../includes/Libft/libft.h"

typedef struct	s_execution
{
	int		n_pipes; // to know when i reach the last pipe
	int		current_pipe; // to track which FD's i need to open/close
	int		n_cmds; // to know how often i need to fork
	int		current_cmd;
	
	
} t_execution;

int		str_error(char *error);
void	free_array(char **array);
char	*path_join(char *path_split, char *cmd_arg);
void	run_ex(char *arg, char **path_env);
int		handle_file(char *filename, int type);


#endif
