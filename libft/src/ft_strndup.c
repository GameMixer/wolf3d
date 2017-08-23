/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:51:33 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 19:57:50 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	char	*cdst;

	if (!(dst = ft_strnew(n + 1)))
		return (0);
	cdst = dst;
	n++;
	while (--n > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (cdst);
}
