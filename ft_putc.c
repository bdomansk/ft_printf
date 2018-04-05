/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdomansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:57:31 by bdomansk          #+#    #+#             */
/*   Updated: 2018/03/12 16:57:34 by bdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*ft_unicode_check(int c, int *len)
{
	char	*buf;

	buf = (char*)malloc(5);
	if ((c <= 0x7F || MB_CUR_MAX == 1) && ((*len) = 1))
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

static char		*ft_putc_width(t_specifiers *s, char *part, int *k, int len)
{
	char	*new;
	char	iszero;
	int		i;
	int		j;

	i = 0;
	new = (char*)malloc(s->width + 1);
	iszero = (s->zero == 1 && s->minus == 0) ? '0' : ' ';
	while (i < s->width)
		new[i++] = iszero;
	i = (s->minus == 1) ? 0 : s->width - len;
	j = 0;
	while (j < len)
		new[i++] = part[j++];
	new[s->width] = '\0';
	(*k) = (*k) + s->width;
	free(part);
	return (new);
}

char			*ft_putc(t_specifiers *s, int ch, int *k)
{
	char	*part;
	char	c;
	int		len;

	if (s->type == 'c' && s->l != 1)
	{
		len = 1;
		part = (char*)malloc(2);
		part[0] = (char)ch;
		part[1] = '\0';
	}
	else
		part = ft_unicode_check(ch, &len);
	c = (char)ch;
	if (s->width > len)
		return (ft_putc_width(s, part, k, len));
	(*k) += len;
	return (part);
}
