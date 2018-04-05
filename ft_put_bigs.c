/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_bigs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:06:36 by bdomansk          #+#    #+#             */
/*   Updated: 2018/04/04 16:06:38 by bdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_puts_flags(t_specifiers *s, char *part, int *k, int len)
{
	char	*new;
	int		i;
	int		j;
	int		size;
	char	iszero;

	i = 0;
	size = (s->width > len) ? s->width : len;
	new = (char*)malloc(size + 1);
	iszero = (s->minus == 0 && s->zero == 1) ? '0' : ' ';
	while (i < size)
	{
		new[i] = iszero;
		i++;
	}
	new[i] = '\0';
	(*k) += size;
	i = 0;
	j = (s->minus > 0) ? 0 : size - len;
	while (i < len)
		new[j++] = part[i++];
	return (new);
}

static char	*ft_unicode_check(int c, int *len)
{
	char	*buf;

	buf = (char*)malloc(5);
	if (c <= 0x7F && ((*len) = 1))
		buf[0] = c;
	else if (c <= 0x7FF && ((*len) = 2))
	{
		buf[0] = (c >> 6) + 0xC0;
		buf[1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF && ((*len) = 3))
	{
		buf[0] = (c >> 12) + 0xE0;
		buf[1] = ((c >> 6) & 0x3F) + 0x80;
		buf[2] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF && ((*len) = 4))
	{
		buf[0] = (c >> 18) + 0xF0;
		buf[1] = ((c >> 12) & 0x3F) + 0x80;
		buf[2] = ((c >> 6) & 0x3F) + 0x80;
		buf[3] = (c & 0x3F) + 0x80;
	}
	buf[*len] = '\0';
	return (buf);
}

static char	*ft_parse_array(t_specifiers *s, int *str, int *size)
{
	char	*need_to_add;
	char	*part;
	int		len_need_to_add;
	int		i;

	i = 0;
	while (str[i])
	{
		len_need_to_add = 0;
		need_to_add = ft_unicode_check(str[i], &len_need_to_add);
		if (s->accuracy && s->accuracy_value < (*size) + len_need_to_add)
		{
			if (len_need_to_add)
				free(need_to_add);
			break ;
		}
		part = ft_add(part, need_to_add, (*size), len_need_to_add);
		(*size) += len_need_to_add;
		if (len_need_to_add)
			free(need_to_add);
		i++;
	}
	return (part);
}

char		*ft_put_bigs(t_specifiers *s, int *str, int *k)
{
	char	*part;
	int		size;

	if (!str && (s->type = 's'))
		return (ft_puts(s, "(null)", k));
	if (!str[0])
		return (NULL);
	size = 0;
	part = ft_parse_array(s, str, &size);
	if (s->minus || s->width)
		return (ft_puts_flags(s, part, k, size));
	(*k) = (*k) + size;
	return (part);
}
