/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:36:03 by adjouber          #+#    #+#             */
/*   Updated: 2019/03/12 15:40:46 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	test(int x, int y, t_prc *p)
{
	t_map	*tmp;

	if (y % 100	== 0)
	{
		tmp = p->m;
		while (tmp != NULL)
		{
			if ((y == tmp->ybegin || y == tmp->yend) && x > tmp->xbegin
						&& tmp->value == '2')
				return (1);
			tmp = tmp->next;
		}
	}
	else if (x % 100 == 0)
	{
		tmp = p->m;
		while (tmp != NULL)
		{
			if ((x == tmp->xbegin || x == tmp->xend) && y > tmp->ybegin
					&& tmp->value == '2')
				return (1);
			tmp = tmp->next;
		}	
	}
	return (0);
}

static void	cast_draw2(t_brese_para *param, int *ret, t_prc *p)
{
	int		cumul;
	int		x;
	int		y;

	x = param->x1;
	y = param->y1;
	cumul = param->dy;
	while (y != param->y2)
	{
		(*ret)++;
		y += param->yinc;
		cumul -= param->dx * 2;
		if (cumul <= 0)
		{
			cumul += param->dy * 2;
			x += param->xinc;
		}
		if (test(x, y, p))
			return ;
	}
}

static void	cast_draw(t_brese_para *param, int *ret, t_prc *p)
{
	int		cumul;
	int		x;
	int		y;

	x = param->x1;
	y = param->y1;
	if (param->dx > param->dy)
	{
		cumul = param->dx;
		while (x != param->x2)
		{
			printf("%d\n", x);
			(*ret)++;
			x += param->xinc;
			cumul -= param->dy * 2;
			if (cumul <= 0 && ((y += param->yinc) || !(y)))
				cumul += param->dx * 2;
			if (test(x, y, p))
				return ;
		}
	}
	else
		cast_draw2(param, ret, p);
}

int		cast(t_prc *p)
{
	t_brese_para	*param;
	int				ret;

	if (!(param = (t_brese_para *)malloc(sizeof(t_brese_para))))
		exit(0);
	ret = 0;
	param->dx = p->x2 - p->x1;
	param->dy = p->y2 - p->y1;
	param->xinc = (param->dx > 0) ? 1 : -1;
	param->yinc = (param->dy > 0) ? 1 : -1;
	param->dx = abs(param->dx);
	param->dy = abs(param->dy);
	param->x1 = p->x1;
	param->x2 = p->x2;
	param->y1 = p->y1;
	param->y2 = p->y2;
	cast_draw(param, &ret, p);
	return (ret);
}
