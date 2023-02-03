/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:04:27 by yobenali          #+#    #+#             */
/*   Updated: 2021/12/05 15:47:22 by yobenali         ###   ########.fr       */
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
# include "../libft/libft.h"

char	*get_next_line(int fd);
// char	*ft_strchr(const char *s, int c);
char	*ft_mystrjoin(char **s1, char *s2);
// int		ft_strlen(const char *s);
char	*strline(char *str);
char	*to_save(char **saved, int size);
// char	*ft_strdup(const char *s1);
// void	*ft_calloc(int count, int size);

#endif
