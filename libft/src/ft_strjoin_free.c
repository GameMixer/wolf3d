/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:52:14 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/15 19:52:45 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	strfree(char *s1, char *s2, int type)
{
	if (type == 'L' || type == 'l')
		free(s1);
	else if (type == 'R' || type == 'r')
		free(s2);
	else if (type == 'B' || type == 'b')
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strjoin_free(char *s1, char *s2, char type)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*result;

	if (s1 && s2)
	{
		i = 0;
		j = 0;
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
		if ((result = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return (NULL);
		while (s1[j] != '\0')
			result[i++] = s1[j++];
		j = 0;
		while (s2[j] != '\0')
			result[i++] = s2[j++];
		result[i] = '\0';
		strfree(s1, s2, type);
		return (result);
	}
	return (NULL);
}
