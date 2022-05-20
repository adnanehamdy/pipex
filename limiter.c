/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:18:14 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:18:14 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_cmd(int *index, char **av)
{
	int	*fd_limit;

	fd_limit = ft_limiter(av);
	*index = 3;
	dup2(fd_limit[0], 0);
	close(fd_limit[1]);
	close(fd_limit[0]);
}

void	read_from_stdin(char *buff, int *fd, char **av)
{
	while (buff)
	{
		if (!(ft_strncmp(buff, av[2], ft_strlen(av[2])))
			&& (ft_strlen(av[2]) == (ft_strlen(buff) - 1)))
			break ;
		write(1, "heredoc>", 8);
		buff = get_next_line(0);
		if (((ft_strncmp(buff, av[2], ft_strlen(av[2])))
				&& !(ft_strlen(av[2]) == (ft_strlen(buff) - 1))))
			write(fd[1], buff, ft_strlen(buff));
	}
}

int	*ft_limiter(char **av)
{
	char	*buff;
	int		*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (pipe(fd) == -1)
		error_exit("can't create file descriptor", 1);
	write(1, "heredoc>", 8);
	buff = get_next_line(0);
	if ((((ft_strncmp(buff, av[2], ft_strlen(av[2])))
				&& !(ft_strlen(av[2]) == (ft_strlen(buff) - 1)))))
		write(fd[1], buff, ft_strlen(buff));
	read_from_stdin(buff, fd, av);
	free(buff);
	return (fd);
}
