/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:23:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/16 23:21:38 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	is_map_rectangular(t_map *map)
{
	int	row;
	int	len;

	row = 0;
	len = ft_strlen(map->matrix[row]);
	while (map->matrix[row])
	{
		if (len != (int)ft_strlen(map->matrix[row]))
		{
			len = -1;
			break ;
		}
		row++;
	}
	if (len == -1)
	{
		free_map(map->matrix);
		print_error("Map must be rectangular");
	}
	map->max_x = len - 1;
	map->max_y = row - 1;
}

static void	is_map_surrounded(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y <= map->max_y)
	{
		x = 0;
		while (x <= map->max_x)
		{
			if ((x == 0 || x == map->max_x || y == 0
					|| y == map->max_y) && map->matrix[y][x] != '1')
			{
				free_map(map->matrix);
				print_error("Map must be surrounded by walls");
			}
			x++;
		}
		y++;
	}
}

static void	is_map_valid(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y <= map->max_y)
	{
		x = 0;
		while (x <= map->max_x)
		{
			if (map->matrix[y][x] != '0' && map->matrix[y][x] != '1'
				&& map->matrix[y][x] != 'C'
				&& map->matrix[y][x] != 'E'
				&& map->matrix[y][x] != 'P')
			{
				free_map(map->matrix);
				print_error("Map must be composed with only 0, 1, C, E, P.");
			}
			x++;
		}
		y++;
	}
}

static void	get_map_counters(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y <= map->max_y)
	{
		x = 0;
		while (x <= map->max_x)
		{
			if (map->matrix[y][x] == 'E')
				map->counter.exit++;
			if (map->matrix[y][x] == 'C')
				map->counter.collectible++;
			if (map->matrix[y][x] == 'P')
				map->counter.player++;
			x++;
		}
		y++;
	}
	if (map->counter.exit != 1 || map->counter.player != 1
		|| map->counter.collectible < 1)
	{
		free_map(map->matrix);
		print_error("Map must contain one exit, one player and collectibles.");
	}
}

void	check_map(t_map *map)
{
	is_map_rectangular(map);
	is_map_surrounded(map);
	is_map_valid(map);
	map->counter.exit = 0;
	map->counter.collectible = 0;
	map->counter.player = 0;
	map->counter.steps = 0;
	get_map_counters(map);
}
