/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:04:27 by yobenali          #+#    #+#             */
/*   Updated: 2023/01/30 17:38:18 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_mystrchr(const char *s, int c);
char	*ft_mystrjoin(char **s1, char *s2);
int		ft_mystrlen(const char *s);
char	*strline(char *str);
char	*to_save(char **saved, int size);
char	*ft_mystrdup(const char *s1);
void	*ft_mycalloc(int count, int size);

#endif
