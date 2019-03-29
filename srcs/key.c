/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:45:13 by adjouber          #+#    #+#             */
/*   Updated: 2019/03/26 15:30:47 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		close_prog(t_wolf *w)
{
	mlx_destroy_image(w->ptr, w->img);
	mlx_destroy_window(w->ptr, w->win);
	exit(0);
	return (0);
}

int		keyboard(int key, t_wolf *w)
{
	if (key == 53)
		close_prog(w);
	return (0);
}

int		move(int key, t_wolf *w)
{
	if (key == 13)
		w->p->y -= 20;
	else if (key == 1)
		w->p->y += 20;
	else if (key == 2)
		w->p->x += 20;
	else if (key == 0)
		w->p->x -= 20;
	minimap(w, 75, 75);
	wolf(w);
	return (0);
}
