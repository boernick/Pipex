/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:48 by nboer             #+#    #+#             */
/*   Updated: 2024/10/13 15:25:43 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(char **arg, int *fd1, char **path_env)
{
	int		fileread;

	fileread = open(arg[1], O_RDONLY, 0777);
	if (fileread < 0)
		str_error("Could not open filein");
	dup2(fileread, STDIN_FILENO);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[0]);
	run_ex(arg[2], path_env);
	return (0);
}

int	second_child(char **arg, int *fd1, char **path_env)
{
	int		filewrite;

	filewrite = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (filewrite < 0)
		str_error("Could not open fileout");
	dup2(fd1[0], STDIN_FILENO);
	dup2(filewrite, STDOUT_FILENO);
	close(fd1[1]);
	run_ex(arg[3], path_env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid[2];
	int		fd1[2];

	if (argc == 5)
	{
		if (pipe(fd1) == -1)
			str_error("pipe make error");
		pid[0] = fork();
		if (pid[0] < 0)
			str_error("FORK ERROR");
		if (pid[0] == 0)
			first_child(argv, fd1, env);
		waitpid(pid[0], NULL, 0);
		pid[1] = fork();
		if (pid[1] < 0)
			str_error("FORK ERROR");
		if (pid[1] == 0)
			second_child(argv, fd1, env);
		close(fd1[0]);
		close(fd1[1]);
		waitpid(pid[1], NULL, 0);
	}
	else
		ft_putstr_fd("input error. Use: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
