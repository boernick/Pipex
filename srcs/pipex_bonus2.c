/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:09:22 by nick              #+#    #+#             */
/*   Updated: 2024/11/02 23:26:41 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:15:54 by nboer             #+#    #+#             */
/*   Updated: 2024/11/02 21:24:46 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus2.h"

int	handle_file(char *filename, int type)
{
	int	fd;

	fd = 0;
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
	t_execution	*p_ex;
	int			i;
	int			infile;
	int			outfile;
	
	if (argc >= 5)
	{
		exec_init(&p_ex);
		infile = handle_file(argv[1], 0);
		outfile = handle_file(argv[argc - 1], 1);
		create_pipes(&p_ex);
		while (i < p_ex->n_cmds)
		{	
			fork_child()
			get_fd()
				if (isbuiltin)
					run_builtin()
				else
					run_ex();
			clean_pipes();
			wait_pid();
		}
	}
	else
		ft_putstr_fd("input error. Use: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
