/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:42:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:14:36 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	int		len;

	len = -1;
	while (s1[++len])
		;
	c = (char *)malloc(len * sizeof(char) + 1);
	if (c != NULL)
		ft_strcpy(c, s1);
	*(c + len) = '\0';
	return (c);
}
