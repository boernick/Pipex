/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:07:34 by nick              #+#    #+#             */
/*   Updated: 2024/11/03 18:46:18 by nboer            ###   ########.fr       */
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
	pid_t	pid; //process ID to check if its child or not
	int		n_pipes; // to know when i reach the last pipe
	int		index_pipe; // to track which FD's i need to open/close
	int		**pipe_arr;
	int		n_cmds; // to know how often i need to fork
	int		index_cmd;
	int		infile; //first file to read from
	int		outfile; // file to output

} t_execution;

int		str_error(char *error);
void	free_array(char **array);
char	*path_join(char *path_split, char *cmd_arg);
void	run_ex(char *arg, char **path_env);
int		handle_file(char *filename, int type);


#endif
