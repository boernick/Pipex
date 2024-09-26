/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:48 by nboer             #+#    #+#             */
/*   Updated: 2024/09/26 18:24:24 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_ex(char *arg, char **path_env)
{
	int		i;
	// char	*path_ex;
	char	**path_split;

	i = 0;
	while (!(ft_strnstr(path_env[i], arg, ft_strlen(arg))))
		i++;
	ft_printf("path found %s\n", path_env[i]);
	path_split = ft_split(path_env[i], ':');
	ft_printf("after split %s", path_split[0]);
	return (path_split[0]);
}

int	run_child(char *arg)
{
	ft_printf("child opens %s", arg);
	find_ex(arg, getenv("PATH"));
	return (0);
}

int	run_parent(char *arg)
{
	ft_printf("parent reads %s", arg);
	// find_ex(arg);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid1;
	int		fd[2];

	argv[2] = NULL;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		pid1 = fork();
		if (pid1 < 0)
			str_error("FORK ERROR");
		if (pid1 == 0)
			run_child(argv[4]);
		waitpid(pid1, NULL, 0);
		run_parent(argv[1]);
		ft_printf(" FINISH %i \n", pid1);
	}
	else
	{
		ft_putstr_fd("Error: wrong argument input", 2);
		ft_putstr_fd("\nTo execute: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
