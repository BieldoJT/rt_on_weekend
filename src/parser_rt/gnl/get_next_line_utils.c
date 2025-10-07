/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:33 by natrodri          #+#    #+#             */
/*   Updated: 2024/10/25 08:07:36 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup2(const char *s)
{
	size_t		size;
	size_t		i;
	char		*cp_str;

	i = 0;
	while (s[i])
		i++;
	size = (i + 1);
	cp_str = (char *)malloc(size * sizeof(char));
	if (!cp_str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		cp_str[i] = s[i];
		i++;
	}
	return (cp_str);
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	int		c1;
	int		c2;
	int		i;
	char	*str;

	if (!s1)
		s1 = ft_strdup2("");
	if (!s1 || !s2)
		return (NULL);
	c1 = ft_strlen2(s1);
	c2 = ft_strlen2(s2);
	str = (char *)malloc((c1 + c2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[c1++] = s2[i];
	str[c1] = '\0';
	free(s1);
	return (str);
}

void	*ft_memcpy2(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
