/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:15:54 by nboer             #+#    #+#             */
/*   Updated: 2024/10/13 20:24:11 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(char *filename, char *cmd, char **path_env)
{
	int		fd[2];
	int		file;
	pid_t	pid;
	
	if (pipe(fd) == -1)
		str_error("pipe error");
	pid = fork();
	if (pid < 0)
		str_error("false PID");
	if (pid > 0) //parent process 
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
		// means this is parent process
	if (pid == 0) // child process
	{
		close(fd[0]);  // Close unused write end of pipe
		dup2(fd[1], STDOUT_FILENO); // Redirect pipe's read end to stdin
		run(cmd, path_env); // Execute the command, reading from stdin
	}
}

int	handle_file(char *filename, int type)
{
	int	fd;

	if (type = 0)
		fd = open(filename, O_RDONLY | 0777);
	if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (type = 2)
		fd = open(filename, O_WRONLY | O_CREAT |O_APPEND, 0777);
	else
		str_error("wrong type argument to handle file");
	return (fd);
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	file;

	if (argc >= 5)
	{
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
		{	
			if (argc < 6) 
				str_error("too little args"); //voor >> want: ./pipex here_doc LIMITER cmd cmd1 file zijn 6 args
			i = 3;
			file = handle_file(argv[2], 0);
			// >> do function "here_doc"
		}
		else
		{
			i = 2;
			file = handle_file(argv[1], 0);
			dup2(file, STDIN_FILENO);
		}
		while (i < argc - 2)
		{
			create_pipe(argv[i], env);
			i++;
		}
		dup2(file, STDOUT_FILENO);
	}
	else
		ft_putstr_fd("input error. Use: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
