/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:24:39 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/15 01:08:42 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// int	handle_no_event(void *data)
// {
// 	if(data)
// 	{
		
// 	}
// 	/* This function needs to exist, but it is useless for the moment */
// 	return (0);
// }

int	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window->win);
	game->window->win = NULL;
	if (game->floor.img != NULL)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->wall.img != NULL)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->exit.img != NULL)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->collectible.img != NULL)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->player.img != NULL)
		mlx_destroy_image(game->mlx, game->player.img);
	free_map(game->map.matrix);
	ft_free_ptr((void *)&game->window);
	ft_free_ptr((void *)&game->player.pos);
	mlx_destroy_display(game->mlx);
	ft_free_ptr(&game->mlx);
	exit(0);
}

void	put_image(t_game *game, int x, int y)
{
	if (game->map.matrix[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->window->win, game->floor.img,
			x * game->floor.width, y * game->floor.height);
	if (game->map.matrix[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->window->win, game->wall.img,
			x * game->wall.width, y * game->wall.height);
	if (game->map.matrix[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window->win, game->exit.img,
			x * game->exit.width, y * game->exit.height);
	if (game->map.matrix[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->window->win,
			game->collectible.img, x * game->collectible.width,
			y * game->collectible.height);
	if (game->map.matrix[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->window->win, game->player.img,
			x * game->player.width, y * game->player.height);
}

void	load_sprites(t_game *game)
{
	game->floor.img = mlx_xpm_file_to_image(game->mlx, "./assets/floor.xpm",
			&game->floor.width, &game->floor.height);
	game->floor.addr = mlx_get_data_addr(game->floor.img, &game->floor.bpp,
			&game->floor.line_length, &game->floor.endian);
	game->collectible.img = mlx_xpm_file_to_image(game->mlx,
			"./assets/collectible.xpm", &game->collectible.width,
			&game->collectible.height);
	game->collectible.addr = mlx_get_data_addr(game->collectible.img,
			&game->collectible.bpp,	&game->collectible.line_length,
			&game->collectible.endian);
	game->exit.img = mlx_xpm_file_to_image(game->mlx, "./assets/exit.xpm",
			&game->exit.width, &game->exit.height);
	game->exit.addr = mlx_get_data_addr(game->exit.img, &game->exit.bpp,
			&game->exit.line_length, &game->exit.endian);
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "./assets/wall.xpm",
			&game->wall.width, &game->wall.height);
	game->wall.addr = mlx_get_data_addr(game->wall.img, &game->wall.bpp,
			&game->wall.line_length, &game->wall.endian);
	game->player.img = mlx_xpm_file_to_image(game->mlx, "./assets/w1.xpm",
			&game->player.width, &game->player.height);
	game->player.addr = mlx_get_data_addr(game->player.img, &game->player.bpp,
			&game->player.line_length, &game->player.endian);
}

int	render_game(t_game	*game)
{
	int		x;
	int		y;

	if (game->window->win != NULL)
	{
		y = 0;
		while (y <= game->map.max_y)
		{
			x = 0;
			while (x <= game->map.max_x)
			{
				put_image(game, x, y);
				// printf("X= %d, Y= %d\n", x, y);
				x++;
			}
			y++;
		}
	}
	return (0);
}

void	load_game(t_game *game)
{
	game->window = ft_calloc(1, sizeof(t_window));
	game->player.pos = ft_calloc(1, sizeof(t_pos));
	game->mlx = mlx_init();
	// game->window = mlx_new_window(game->mlx, (game->map.max_x + 1) * SPRITE_DIM,
	// 		(game->map.max_y + 1) * SPRITE_DIM, "so_long");
	game->window->width = SPRITE_DIM * (game->map.max_x + 1);
	game->window->height = SPRITE_DIM * (game->map.max_y + 1);
	game->window->win = mlx_new_window(game->mlx,
			game->window->width,
			game->window->height,
			"so_long");
	load_sprites(game);
	mlx_hook(game->window->win, 17, 0, &end_game, game);
	mlx_hook(game->window->win, 2, 1L << 0, key_hooks, game);
	mlx_loop_hook(game->mlx, &render_game, game);
	mlx_loop(game->mlx);
	
	// end_game(game);
	// free(game->mlx);
}