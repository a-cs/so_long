/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:17:40 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/16 23:49:25 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	find_player(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y <= game->map.max_y)
	{
		x = 0;
		while (x <= game->map.max_x)
		{
			if (game->map.matrix[y][x] == 'P')
			{
				game->player.pos->x = x;
				game->player.pos->y = y;
			}
			x++;
		}
		y++;
	}
}

void	move(t_game *game, int delta_x, int delta_y)
{
	char	next_char;

	find_player(game);
	next_char = game->map.matrix[game->player.pos->y + delta_y]
	[game->player.pos->x + delta_x];
	game->map.counter.steps++;
	printf("Steps: %d\n", game->map.counter.steps);
	if (next_char != '1')
	{
		if (game->map.counter.collectible == 0 && next_char == 'E')
		{
			printf("You won!\n");
			end_game(game);
		}
		if (next_char == 'C')
			game->map.counter.collectible--;
		if (next_char == 'E')
			printf("To be able to exit, you must collect all collectibles!\n");
		else
		{
			game->map.matrix[game->player.pos->y][game->player.pos->x] = '0';
			game->map.matrix[game->player.pos->y + delta_y]
			[game->player.pos->x + delta_x] = 'P';
		}
	}
}

int	key_hooks(int key, t_game *game)
{
	if (key == ESC)
		end_game(game);
	if (key == UP || key == AROW_UP)
	{
		game->player.orientation = 0;
		move(game, 0, -1);
	}
	if (key == DOWN || key == AROW_DOWN)
	{
		game->player.orientation = 2;
		move(game, 0, +1);
	}
	if (key == LEFT || key == AROW_LEFT)
	{
		game->player.orientation = 1;
		move(game, -1, 0);
	}
	if (key == RIGHT || key == AROW_RIGHT)
	{
		game->player.orientation = 3;
		move(game, +1, 0);
	}
	return (0);
}
