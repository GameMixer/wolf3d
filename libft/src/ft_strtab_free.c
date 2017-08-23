/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 20:08:03 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/21 20:10:01 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtab_free(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}
