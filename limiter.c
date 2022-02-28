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

void	read_from_stdin(char *buff, int *fd, char **av)
{
	while (buff)
	{
		if (!(ft_strncmp(buff, av[2], ft_strlen(buff) - 1)
				|| (ft_strlen(buff) != (ft_strlen(av[2]) + 1))))
			break ;
		write(1, "heredoc>", 8);
		buff = get_next_line(0);
		if (!buff)
		{
			free(buff);
			error_exit();
		}
		write(fd[1], buff, ft_strlen(buff));
	}
}

int	*ft_limiter(char **av)
{
	char	*buff;
	int		*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (pipe(fd) == -1)
		error_exit();
	write(1, "heredoc>", 8);
	buff = get_next_line(0);
	if (!buff)
		error_exit();
	write(fd[1], buff, ft_strlen(buff));
	read_from_stdin(buff, fd, av);
	//free(buff);
	return (fd);
}
