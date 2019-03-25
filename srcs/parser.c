/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:59:51 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/12 14:04:53 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		convert(t_map *f)
{
	f->xbegin = f->x * 100;
	f->ybegin = f->y * 100;
	f->xend = f->xbegin + 100;
	f->yend = f->ybegin + 100;
}

int			fill_map(char value, int x, int y, t_map **f)
{
	t_map	*tmp;

	if (!(*f))
	{
		if (!(*f = (t_map *)malloc(sizeof(t_map))))
			return (-1);
		(*f)->x = x;
		(*f)->y = y;
		(*f)->value = value;
		(*f)->next = NULL;
		convert(*f);
	}
	else
	{
		tmp = *f;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_map *)malloc(sizeof(t_map))))
			return (-1);
		tmp = tmp->next;
		tmp->x = x;
		tmp->y = y;
		tmp->value = value;
		tmp->next = NULL;
		convert(tmp);
	}
	return (0);
}

t_map		*parser(int fd)
{
	t_map	*ret;
	char	*line;
	int		x;
	int		y;

	y = 0;
	ret = NULL;
	while (get_next_line(fd, &line))
	{
		x = 0;
		while (line[x])
		{
			if (fill_map(line[x], x, y, &ret) == -1)
				return (NULL);
			x++;
		}
		y++;
	}
	return (ret);
}
