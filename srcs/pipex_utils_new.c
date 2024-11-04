/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:06:35 by nick              #+#    #+#             */
/*   Updated: 2024/11/04 22:53:47 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_new.h"

char	*path_join(char *path_split, char *cmd_arg)
{
	char	*temp;
	char	*joined_path;

	temp = ft_strjoin(path_split, "/");
	joined_path = ft_strjoin(temp, cmd_arg);
	free(temp);
	return (joined_path);
}

void	run_ex(char *arg, char **path_env)
{
	int		i;
	char	**path_split;
	char	*check_path;
	char	**cmd_arg;

	i = 0;
	while (path_env[i] && ft_strncmp(path_env[i], "PATH=", 5) != 0)
		i++;
	cmd_arg = ft_split(arg, ' ');
	path_split = ft_split(path_env[i] + 5, ':');
	i = 0;
	while (path_split[i])
	{
		check_path = path_join(path_split[i], cmd_arg[0]);
		ft_putstr_fd(check_path, 2);
		ft_putstr_fd("\n", 2);
		if (!(access(check_path, F_OK)))
			if (execve(check_path, cmd_arg, path_env) == -1)
				str_error("exec error");
		i++;
		free(check_path);
	}
	free_array(cmd_arg);
	free_array(path_split);
	str_error("cmd not found\n");
}

int	str_error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(2);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
