/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:52:42 by ahamdy            #+#    #+#             */
/*   Updated: 2022/03/15 12:36:59 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(char **envp, char *cmd)
{
	char	*path;
	char	**command;

	command = split_cmd(cmd);
	if (!find_char(command[0], '/'))
		path = find_path(envp, command[0]);
	else
		path = command[0];
	if (execve(path, command, envp) == -1)
		error_exit(ft_strjoin("pipex : no such file or directory : ",
				command[0]), 127);
}

void	output_cmd(char **envp, char *c, char **av, int outfile)
{
	char	*path;
	char	**command;
	int		fd;

	if ((!ft_strncmp(av[1], "here_doc", ft_strlen(av[1]))))
		fd = open_fd(av[outfile], 1);
	else
		fd = open_fd(av[outfile], 0);
	if (fd == -1)
		error_exit("can't create file discriptor", 1);
	dup2(fd, 1);
	close(fd);
	command = split_cmd(c);
	if (!find_char(command[0], '/'))
		path = find_path(envp, command[0]);
	else
		path = command[0];
	if (execve(path, command, envp) == -1)
		error_exit(ft_strjoin("pipex : no such file or directory : ",
				command[0]), 127);
}

void	mul_pipe(int *index, char **av, char **envp, int ac)
{
	int		fd2[2];
	pid_t	pid;
	int		outfile;

	outfile = ac - 1;
	if (pipe(fd2))
		error_exit("can't create file descriptor", 1);
	pid = fork_it();
	if (pid == -1)
		error_exit("can't fork", 1);
	if ((*index != ac - 2) && pid == 0)
	{
		duplicate_bonus(fd2);
		run_cmd(envp, av[*index]);
	}
	else if (pid == 0)
		output_cmd(envp, av[*index], av, outfile);
	dup2(fd2[0], 0);
	close(fd2[0]);
	close(fd2[1]);
}

void	first_cmd_input(int *index, char **av)
{
	int		fd_in;
	int		fd[2];
	char	*msg;

	fd_in = open(av[*index], O_RDONLY);
	if (fd_in == -1)
	{
		msg = fd_fail_msg(av[*index]);
		ft_putstr(msg);
		ft_putstr("\n");
		free(msg);
		*index = 3;
		pipe(fd);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		*index = 2;
		dup2(fd_in, 0);
	}
	close(fd_in);
}

int	main(int ac, char **av, char **envp)
{
	int	index;

	index = 1;
	if (ac < 5 || (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac < 6))
		error_exit("invalid number of arguments\n", 1);
	if ((!ft_strncmp(av[1], "here_doc", ft_strlen(av[1]))))
		here_doc_cmd(&index, av);
	else
		first_cmd_input(&index, av);
	while (index != ac - 1)
	{
		mul_pipe(&index, av, envp, ac);
		index++;
	}
	while (wait(NULL) != -1)
		;
}
