/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:24:39 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/16 23:32:27 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	end_game(t_game *game)
{
	int	i;

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
	i = -1;
	while (++i < 4)
	{
		if (game->player.img[i] != NULL)
			mlx_destroy_image(game->mlx, game->player.img[i]);
	}
	free_map(game->map.matrix);
	ft_free_ptr((void *)&game->window);
	ft_free_ptr((void *)&game->player.pos);
	ft_free_ptr((void *)&game->player.img);
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
		mlx_put_image_to_window(game->mlx, game->window->win,
			game->player.img[game->player.orientation], x * game->player.width,
			y * game->player.height);
}

void	load_sprites(t_game *game)
{
	game->floor.img = mlx_xpm_file_to_image(game->mlx, "./assets/floor.xpm",
			&game->floor.width, &game->floor.height);
	game->collectible.img = mlx_xpm_file_to_image(game->mlx,
			"./assets/collectible.xpm", &game->collectible.width,
			&game->collectible.height);
	game->exit.img = mlx_xpm_file_to_image(game->mlx, "./assets/exit.xpm",
			&game->exit.width, &game->exit.height);
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "./assets/wall.xpm",
			&game->wall.width, &game->wall.height);
	game->player.img[0] = mlx_xpm_file_to_image(game->mlx, "./assets/w1.xpm",
			&game->player.width, &game->player.height);
	game->player.img[1] = mlx_xpm_file_to_image(game->mlx, "./assets/a1.xpm",
			&game->player.width, &game->player.height);
	game->player.img[2] = mlx_xpm_file_to_image(game->mlx, "./assets/s1.xpm",
			&game->player.width, &game->player.height);
	game->player.img[3] = mlx_xpm_file_to_image(game->mlx, "./assets/d1.xpm",
			&game->player.width, &game->player.height);
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
	game->player.img = ft_calloc(4, sizeof(void *));
	game->player.orientation = 0;
	game->mlx = mlx_init();
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
}
