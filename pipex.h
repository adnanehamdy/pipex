/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:36:50 by ahamdy            #+#    #+#             */
/*   Updated: 2022/02/24 17:36:50 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<stdio.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<stdlib.h>
# include<fcntl.h>

int		open_file(char *c);
int		fork_it(void);
void	duplicate_fd(int *fd, int file);
char	*find_path(char **envp, char *cmd);
char	**split_cmd(char *cmd);
void	duplicate_file(int *fd, int file);
void	error_exit(void);
int		open_fd(char *c);
void	duplicate_bonus(int *fd);
void	duplicate_fil(int fd, int file);
char	*get_next_line(int fd);
int		*ft_limiter(char **av);
int		mul_pipe(int index, char **av, char **evnp, int ac);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		find_path_line(char **envp);
#endif