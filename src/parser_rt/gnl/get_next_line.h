/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:33 by natrodri          #+#    #+#             */
/*   Updated: 2024/10/25 09:15:14 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

size_t	ft_strlen2(const char	*s);
size_t	ft_strlcpy2(char	*dest, const char	*src, size_t	size);

char	*get_next_line(int fd);
char	*ft_strdup2(const char *s);
char	*ft_strchr2(const char *s, int c);
void	*ft_memcpy2(void *dest, const void *src, size_t n);
char	*ft_strjoin2(char *s1, char const *s2);

#endif
