/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:09:22 by nick              #+#    #+#             */
/*   Updated: 2024/11/06 18:28:08 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_new.h"

int	handle_file(char *filename, int type)
{
	int	fd;

	fd = 0;
	if (type == 0)
		fd = open(filename, O_RDONLY);
	else if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 2)
		fd = open(filename, O_WRONLY | O_CREAT |O_APPEND, 0644);
	else
		str_error("wrong type argument to handle file\n");
	if (fd == -1)
	{
		str_error("Cannot open file");
		exit(1);
	}
	return (fd);
}
// prepare exec struct for use
void	exec_init(t_execution *pipex, int argc, char **argv)
{
	pipex->infile = handle_file(argv[1], 0); // TO-DO BUT ONLY IF THE FIRST ARGUMENT IS A FILE!
	pipex->outfile = handle_file(argv[argc - 1], 1);
	pipex->n_cmds = argc - 3;
	pipex->n_pipes = pipex->n_cmds - 1;
	pipex->index_pipe = 0;
	pipex->index_cmd = 0;
	pipex->index_prev_pipe = -1;
}
// prepare exec struct for next call
void	update_exec(t_execution *pipex)
{
	pipex->index_prev_pipe = pipex->index_pipe;
	pipex->index_pipe++;
	pipex->index_cmd++;
}

// create an array of pointers to integers to store the total amount of pipes.
void	create_pipes(t_execution *pipex)
{
	int		i;

	if (pipex->n_pipes <= 0)
		str_error("Number of pipes must be greater than zero");	
	if (!(pipex->pipe_arr = malloc(sizeof(int *) * pipex->n_pipes + 1)))
		str_error("Malloc failure while creating array of pointers");
	pipex->pipe_arr[0] = NULL;
	i = 0;
	while (i < pipex->n_pipes)
	{
		if (!(pipex->pipe_arr[i] = malloc(sizeof(int) * 2)))
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
	pipex->pipe_arr[i] = NULL;
}
// free the pipe_array from the last index that was allocated in memory
void	free_int_array(t_execution *pipex, int	i)
{
	int		**array;

	array = pipex->pipe_arr;
	if (!array)
		return;
	while (i >= 0)
	{
		if (array[i])
			free(array[i]);
		i--;
	}
	free(array);
}
// fork a child process and return error if PID is false
pid_t	fork_child(void)
{
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		str_error("Error: false PID");
	return (pid);
}

void	get_fd(t_execution *pipex)
{
	if (pipex->index_pipe == 0) // for the first case
		dup2(pipex->infile, STDIN_FILENO);
	else 
		dup2(pipex->pipe_arr[pipex->index_prev_pipe][0], STDIN_FILENO);
	if (pipex->index_cmd == pipex->n_cmds - 1)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->pipe_arr[pipex->index_pipe][1], STDOUT_FILENO);

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
		i++;
	}
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
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

void	waitpids(pid_t *pids, int n)
{
	int	i;
	
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_execution	pipex;
	pid_t		*pids;
	int			i;
	
	if (argc < 5)
		str_error("input error. Use: ./pipex file1 cmd1 cmd2 file2\n");
	else 
	{
		exec_init(&pipex, argc, argv); // tellen hoeveel cmd args er zijn en het opslaan in struct
		create_pipes(&pipex);
		pids = malloc(pipex.n_cmds * sizeof(pid_t));
		i = 0;
		while (pipex.index_cmd < pipex.n_cmds)
		{	
			pids[i] = fork_child();
			if (pids[i++] == 0) //case child
			{
				if (is_builtin(&pipex))
				{
					run_builtin(&pipex);
					exit(EXIT_SUCCESS); //can be removed later, just safety not to get infinite loop
				}	
				else
				{
					get_fd(&pipex);
					clean_pipes(&pipex);
					run_ex(argv[pipex.index_cmd + 2], env);
					exit(EXIT_SUCCESS);
				}
			}
			else
				update_exec(&pipex);
		}
		clean_pipes(&pipex);
		waitpids(pids, pipex.n_cmds); // wait for child process, but WHY these inputs in function?
	}
	return (0);
}
