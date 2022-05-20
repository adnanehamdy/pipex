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

void	input_cmd(char **envp, char *cmd, int *fd1, char *file)
{
	char	*path;
	char	**command;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (!access(file, F_OK))
			error_exit(ft_strjoin("pipex : permission denied :",
					file), 1);
		error_exit(ft_strjoin("pipex : no such file or directory :",
				file), 1);
	}
	duplicate_fd(fd1, fd);
	command = split_cmd(cmd);
	if (!find_char(command[0], '/'))
		path = find_path(envp, command[0]);
	else
		path = command[0];
	if (execve(path, command, envp) == -1)
		error_exit(ft_strjoin("pipex : no such file or directory :",
				*command), 127);
}

void	output_cmd(char **envp, char **av)
{
	char	*path;
	char	**command;

	command = split_cmd(av[3]);
	if (!find_char(command[0], '/'))
		path = find_path(envp, command[0]);
	else if (*command[0] != '/')
		path = ft_strjoin("/", command[0]);
	else
		path = command[0];
	if (execve(path, command, envp) == -1)
		error_exit(ft_strjoin("pipex : no such file or directory : ",
				*command), 127);
}

void	second_cmd(char **av, int *fd1, char **envp)
{
	int	fd;

	fd = open_fd(av[4], 0);
	if (fd == -1)
		error_exit("can't create file descriptor\n", 1);
	duplicate_file(fd1, fd);
	output_cmd(envp, av);
	close(fd1[0]);
	close(fd1[1]);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid[2];
	int		fd1[2];
	int		cmd_num;

	cmd_num = 2;
	if (ac != 5)
	{
		write(2, "error check the arguments number\n", 33);
		exit(1);
	}
	pipe(fd1);
	pid[0] = fork_it();
	if (pid[0] == 0)
		input_cmd(envp, av[cmd_num], fd1, av[1]);
	pid[1] = fork_it();
	if (pid[1] == 0)
		second_cmd(av, fd1, envp);
	close(fd1[0]);
	close(fd1[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
