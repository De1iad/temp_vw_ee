/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:15:07 by obibby            #+#    #+#             */
/*   Updated: 2023/02/22 19:57:23 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		destlen;
	int		srclen;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	while (dest[i] != '\0')
	{
		if (i == size)
			return (size + srclen);
		i++;
	}
	while (src[i - destlen] != '\0' && i < size - 1 && size > 0)
	{
		dest[i] = src[i - destlen];
		i++;
	}
	dest[i] = '\0';
	return (destlen + srclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ptr = malloc(sizeof(char) * len);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, (ft_strlen(s1) + 1));
	ft_strlcat(ptr, s2, len);
	return (ptr);
}

int	charcount(long long x)
{
	int	i;

	i = 0;
	if (x == 0)
		return (1);
	if (x < 0)
	{
		i++;
		x = -x;
	}
	while (x != 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long long	x;
	int			i;
	char		*str1;
	int			sign;

	x = n;
	sign = 0;
	i = charcount(x);
	if (x < 0)
	{
		x = -x;
		sign = 1;
	}
	str1 = malloc(sizeof(char) * (i + 1));
	if (str1 == NULL)
		return (NULL);
	str1[i] = '\0';
	while (i-- > sign)
	{
		str1[i] = (x % 10) + '0';
		x /= 10;
	}
	if (n < 0)
		str1[i] = '-';
	return (str1);
}
