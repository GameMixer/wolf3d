/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:42:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/10 15:39:44 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupfree(const char *src)
{
	char	*result;
	char	*newsrc;
	char	*dest;
	int		i;

	i = 0;
	newsrc = (char *)src;
	while (src[i] != '\0')
		i++;
	if ((result = (char *)malloc(sizeof(*src) * (i + 1))) == NULL)
		return (NULL);
	dest = result;
	while (*newsrc != '\0')
	{
		*dest = *newsrc;
		dest++;
		newsrc++;
	}
	*dest = '\0';
	free((void *)src);
	return (result);
}
