/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:38:28 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:38:28 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	duplicate_fd(int *fd, int file)
{
	close(fd[0]);
	dup2(file, 0);
	close(file);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	error_exit(char *c, int num_code)
{
	ft_putstr(c);
	ft_putstr("\n");
	exit(num_code);
}

int	open_fd(char *c, int here_doc)
{
	int	fd;

	if (here_doc)
		fd = open(c, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(c, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (fd);
}

void	duplicate_bonus(int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	duplicate_file(int *fd, int file)
{
	close(fd[1]);
	dup2(file, 1);
	dup2(fd[0], 0);
	close(file);
	close(fd[0]);
}
