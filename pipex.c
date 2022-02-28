/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:46 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:23:46 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_cmd(char **envp, char *cmd)
{
	char	*path;
	char	**command;

	command = split_cmd(cmd);
	path = find_path(envp, command[0]);
	if (execve(path, command, envp) == -1)
		error_exit();
}

void	output_cmd(char **envp, char **av)
{
	char	*path;
	char	**command;

	command = split_cmd(av[3]);
	path = find_path(envp, command[0]);
	if (execve(path, command, envp) == -1)
		error_exit();
}

void	second_cmd(char **av, int *fd1, char **envp)
{
	int	fd;

	unlink(av[4]);
	fd = open_file(av[4]);
	duplicate_file(fd1, fd);
	output_cmd(envp, av);
	close(fd1[0]);
	close(fd1[1]);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid[2];
	int		fd;
	int		fd1[2];

	if (ac != 5)
	{
		write(2, "error check the arguments number\n", 33);
		exit(1);
	}
	pipe(fd1);
	pid[0] = fork_it();
	if (pid[0] == 0)
	{
		fd = open_fd(av[1]);
		duplicate_fd(fd1, fd);
		input_cmd(envp, av[2]);
	}
	pid[1] = fork_it();
	if (pid[1] == 0)
		second_cmd(av, fd1, envp);
	close(fd1[0]);
	close(fd1[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
