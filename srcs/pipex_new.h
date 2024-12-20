/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:07:34 by nick              #+#    #+#             */
/*   Updated: 2024/11/06 17:54:18 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_NEW_H
# define PIPEX_NEW_H

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
	int		index_pipe; // to track the pipe where to write in
	int		index_prev_pipe; // to track the pipe where to read from
	int		**pipe_arr;
	int		n_cmds; // to know how often i need to fork
	int		index_cmd;
	int		infile; //first file to read from
	int		outfile; // file to output
} t_execution;

char	*path_join(char *path_split, char *cmd_arg);
void	run_ex(char *arg, char **path_env);
int		str_error(char *error);
void	free_array(char **array);
int		handle_file(char *filename, int type);
void	exec_init(t_execution *pipex, int argc, char **argv);
void	update_exec(t_execution *pipex);
void	create_pipes(t_execution *pipex);
void	free_int_array(t_execution *pipex, int i);
pid_t	fork_child(void);
void	get_fd(t_execution *pipex);
void	clean_pipes(t_execution *pipex);
int		is_builtin(t_execution *pipex);
int		run_builtin(t_execution *pipex);
void	waitpids(pid_t *pids, int n);
char	*get_path_env(char **path_env);


#endif
