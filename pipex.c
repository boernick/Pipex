/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:48 by nboer             #+#    #+#             */
/*   Updated: 2024/10/13 11:09:24 by nboer            ###   ########.fr       */
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
	while (path_split[i++])
	{
		temp = ft_strjoin(path_split[i], "/");
		check_path = ft_strjoin(temp, cmd_arg[0]);
		free(temp);
		if (!(access(check_path, F_OK)))
			if (execve(check_path, cmd_arg, path_env) == -1)
				str_error("exec error");
		free(check_path);
	}
	free_array(cmd_arg);
	free_array(path_split);
	str_error("cmd not found");
}

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
