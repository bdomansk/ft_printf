/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:37:56 by bdomansk          #+#    #+#             */
/*   Updated: 2018/02/23 11:37:59 by bdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_add(char *buf, const char *need_add, int size1, int size2)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = (char*)malloc(size1 + size2 + 1);
	while (i < size1)
	{
		temp[i] = buf[i];
		i++;
	}
	while (k < size2)
	{
		temp[i] = need_add[k];
		i++;
		k++;
	}
	temp[i] = '\0';
	if (size1 != 0)
		free(buf);
	return (temp);
}
