/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:59:51 by jubeal            #+#    #+#             */
/*   Updated: 2019/03/26 14:15:58 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		convert(t_map *tmp, t_map *f)
{
	tmp->xbegin = tmp->x * 100;
	tmp->ybegin = tmp->y * 100;
	tmp->xend = tmp->xbegin + 100;
	tmp->yend = tmp->ybegin + 100;
	if (tmp->y > 0)
	{
		while (f->x != tmp->x || f->y != tmp->y - 1)
			f = f->next;
		f->next_line = tmp;
	}
}

int			fill_map(char value, int x, int y, t_map **f)
{
	t_map	*tmp;

	if (!(*f))
	{
		if (!(*f = (t_map *)malloc(sizeof(t_map))))
			return (-1);
		(*f)->next = NULL;
		tmp = *f;
	}
	else
	{
		tmp = *f;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(tmp->next = (t_map *)malloc(sizeof(t_map))))
			return (-1);
		tmp = tmp->next;
	}
	tmp->x = x;
	tmp->y = y;
	tmp->value = value;
	tmp->next = NULL;
	tmp->next_line = NULL;
	convert(tmp, *f);
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
