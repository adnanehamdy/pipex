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

void	output_cmd(char **envp, char *av)
{
	char	*path;
	char	**command;

	command = split_cmd(av);
	path = find_path(envp, command[0]);
	if (execve(path, command, envp) == -1)
		error_exit();
}

int	mul_pipe(int index, char **av, char **envp, int ac)
{
	int		fd2[2];
	pid_t	pid;

	while (--ac)
	{
		index++;
		if (pipe(fd2))
			error_exit();
		pid = fork_it();
		if (pid == -1)
			error_exit();
		if (pid == 0)
		{
			duplicate_bonus(fd2);
			input_cmd(envp, av[index]);
		}
		close(fd2[1]);
		dup2(fd2[0], 0);
		close(fd2[0]);
	}
	return (index);
}

void	first_input(char **av, int *ac, int *index)
{
	int	fd_in;
	int	*fd_limit;

	fd_in = 0;
	if ((!ft_strncmp(av[1], "here_doc", ft_strlen(av[1]))))
	{
		fd_limit = ft_limiter(av);
		*ac -= 4;
		*index = 3;
		dup2(fd_limit[0], 0);
		close(fd_limit[1]);
		close(fd_limit[0]);
	}
	else
	{
		fd_in = open_fd(av[*index]);
		dup2(fd_in, 0);
		close(fd_in);
		*ac -= 3;
	}
}

int	main(int ac, char **av, char **envp)
{
	int		index;
	int		fd;
	int		arg_number;
	int		pid;

	index = 1;
	arg_number = ac - 1;
	if (ac < 5)
	{
		write(2, "error check the arguments number\n", 33);
		exit(1);
	}
	first_input(av, &ac, &index);
	index = mul_pipe(index, av, envp, ac);
	unlink(av[arg_number]);
	fd = open_file(av[arg_number]);
	dup2(fd, 1);
	close(fd);
	pid = fork_it();
	if (pid == 0)
		output_cmd(envp, av[arg_number - 1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
