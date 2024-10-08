/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:48 by nboer             #+#    #+#             */
/*   Updated: 2024/10/08 20:47:05 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_ex(char *arg, char **path_env)
{
	int		i;
	char	**path_split;
	char	*check_path;
	char	**cmd_arg;
	char	*temp;

	i = 0;
	while (!(ft_strnstr(path_env[i], "PATH", 4)))
		i++;
	cmd_arg = ft_split(arg, ' ');
	path_split = ft_split(path_env[i] + 5, ':');
	i = 0;
	while (path_split[i] != NULL)
	{
		temp = ft_strjoin(path_split[i], "/");
		check_path = ft_strjoin(temp, cmd_arg[0]);
		free(temp);
		if (!(access(check_path, X_OK)))
			if (execve(check_path, cmd_arg, path_env) == -1)
				str_error("exec error");
		free(check_path);
		i++;
	}
	free_array(cmd_arg);
	free_array(path_split);
	str_error("cmd not found");
}

int	first_child(char **arg, int *fd1, char **path_env) // open infile arg[1] and read through with arg[2]
{
	int		fileread;
	
	fileread = open(arg[1], O_RDONLY, 0777);
	write(1, "OP1", 3);
	if (fileread < 0)
		str_error("Could not open file");
	dup2(fileread, STDIN_FILENO); // redirect input from FILEREAD
	dup2(fd1[1], STDOUT_FILENO); // write to pipe (left)
	// close(fd1[0]);
	close(fd1[1]);
	write(1, "start", 5);
	run_ex(arg[2], path_env);
	exit(EXIT_FAILURE);
}

int	second_child(char **arg, int *fd1, char **path_env)
{
	int		filewrite;

	filewrite = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write(1, "OP2", 3);
	dup2(fd1[0], STDIN_FILENO); // redirect input from read end of the pipe (right)
	dup2(filewrite, STDOUT_FILENO); // copy STDOUT into outfile
	// close(fd1[0]); //close read start of the first pipe
	close(fd1[1]);
	write(1, "yes", 3);
	run_ex(arg[3], path_env);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env) // how do i acces this information? **env
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd1[2];

	if (argc == 5)
	{
		if (pipe(fd1) == -1)
			str_error("pipe make error");
		pid1 = fork();
		if (pid1 < 0)
			str_error("FORK ERROR");
		if (pid1 == 0)
		{
			write(1, "CH1", 3);
			first_child(argv, fd1, env);
		}
		pid2 = fork();
		if (pid2 < 0)
			str_error("FORK ERROR");
		if (pid2 == 0)
		{
			write(1, "CH2", 3);
			second_child(argv, fd1, env);
		}
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		close(fd1[0]);
		close(fd1[1]);
		ft_printf(" FINISH %i \n", pid1);
	}
	else
	{
		ft_putstr_fd("Error: wrong argument input", 2);
		ft_putstr_fd("\nTo execute: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}