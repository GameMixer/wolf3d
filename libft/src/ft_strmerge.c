/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 14:20:48 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/07 14:22:13 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char *a, char *b)
{
	char *ret;

	ret = ft_strjoin(a, b);
	ft_strdel(&a);
	ft_strdel(&b);
	return (ret);
}
