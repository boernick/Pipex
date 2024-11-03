/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:09:22 by nick              #+#    #+#             */
/*   Updated: 2024/11/03 22:27:30 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_new.h"

int	handle_file(char *filename, int type)
{
	int	fd;

	fd = 0;
	if (type == 0)
		fd = open(filename, O_RDONLY | 0777);
	else if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (type == 2)
		fd = open(filename, O_WRONLY | O_CREAT |O_APPEND, 0777);
	else
		str_error("wrong type argument to handle file\n");
	return (fd);
}
// prepare exec struct for use
void	exec_init(t_execution *pipex, int argc, char **argv)
{
	ft_putstr_fd("setting infile\n", 2);
	pipex->infile = handle_file(argv[1], 0); // TO-DO BUT ONLY IF THE FIRST ARGUMENT IS A FILE!
	ft_putstr_fd("setting outfile\n", 2);
	pipex->outfile = handle_file(argv[argc - 1], 1);
	pipex->n_cmds = argc - 2;
	pipex->n_pipes = argc - 3;
	pipex->index_pipe = 0;
	pipex->index_cmd = 0;
}
// prepare exec struct for next call
void	update_exec(t_execution *pipex)
{
	pipex->index_pipe++;
	pipex->index_cmd++;
}

// create an array of pointers to integers to store the total amount of pipes.
void	create_pipes(t_execution *pipex)
{
	ft_putstr_fd("creating pipes\n", 2);

	int		i;

	if (pipex->n_pipes <= 0)
		str_error("Number of pipes must be greater than zero");	
	if (!(pipex->pipe_arr = (int **) malloc(sizeof(int *) * pipex->n_pipes)))
		str_error("Malloc failure while creating array of pointers");
	i = 0;
	while (i < pipex->n_pipes)
	{
		if (!(pipex->pipe_arr[i] = (int *) malloc(sizeof(int) * 2)))
		{
			free_int_array(pipex, i + 1);
			str_error("Malloc failure while creating pipes");
		}
		if (pipe(pipex->pipe_arr[i]) == -1)
		{
			free_int_array(pipex, i + 1);
			str_error("Error creating pipes");
		}
		i++;
	}
}
// free the pipe_array from the last index that was allocated in memory
void	free_int_array(t_execution *pipex, int	i)
{
	int		**array;

	array = pipex->pipe_arr;
	if (!array)
		return;
	while (i > 0)
		free(array[--i]);
	free(array);
}
// fork a child process and return error if PID is false
void	fork_child(t_execution *pipex)
{
	ft_putstr_fd("forking child\n", 2);
	pipex->pid = fork();
	if (pipex->pid < 0)
		str_error("Error: false PID");
	
}

void	get_fd(t_execution *pipex)
{
	if (pipex->pid > 0) 												// case parent
	{
		if (pipex->index_cmd == 0)										// case first command
			dup2(pipex->infile, STDIN_FILENO);								// redirect reading from STDIN to reading from input file.
		else
			dup2(pipex->pipe_arr[pipex->index_pipe][0], STDIN_FILENO); 		// case any other
	}
	if (pipex->pid == 0)												// case child
	{
		if (pipex->index_cmd == pipex->n_cmds)
			dup2(pipex->outfile, STDOUT_FILENO);
		else
			dup2(pipex->pipe_arr[pipex->index_pipe][1], STDOUT_FILENO);
	}
}

void	clean_pipes(t_execution *pipex)
{
	int	i;

	i = 0;
	if (!pipex->pipe_arr)
		return;
	while (i < pipex->n_pipes)
	{
		close(pipex->pipe_arr[i][0]);
		close(pipex->pipe_arr[i][1]);
		free(pipex->pipe_arr[i]);
		i++;
	}
	free(pipex->pipe_arr);
}

int	is_builtin(t_execution *pipex)
{
	(void) pipex;
	return (0);
}

int	run_builtin(t_execution *pipex)
{
	(void) pipex;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_execution	pipex;
	
	if (argc < 5)
		str_error("input error. Use: ./pipex file1 cmd1 cmd2 file2\n");
	else 
	{
		exec_init(&pipex, argc, argv); // tellen hoeveel cmd args er zijn en het opslaan in struct
		create_pipes(&pipex); 
		while (pipex.index_cmd <= pipex.n_cmds)
		{	
			get_fd(&pipex);
			fork_child(&pipex);
			if (pipex.pid == 0)
			{
				if (is_builtin(&pipex))
					run_builtin(&pipex);
				else
					run_ex(argv[pipex.index_cmd + 2], env);
				exit(EXIT_SUCCESS);
			}
			else
				update_exec(&pipex);
			pipex.index_cmd++;
		}
		ft_putstr_fd("parent waiting....\n", 2);
		waitpid(pipex.pid, NULL, 0); // wait for child process, but WHY these inputs in function?
		clean_pipes(&pipex);
	}
	return (0);
}
