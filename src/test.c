/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:33:55 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/07 21:13:11 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

typedef struct s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

int	handle_no_event(void *data)
{
	if(data)
	{
		
	}
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_input(int key, t_game *game)
{
	if(game)
	{
		
	}
	if (key == ESC)
		exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
}

int	main(void)
{
	t_game	game;
	t_img	img;
	int		x;
	int		y;
	char	*path = "./assets/floor.xpm";

	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "Hello world!");
	// img.img = mlx_new_image(game.mlx_ptr, 800, 600);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 		&img.endian);

	// x = 0;
	// while (x < 200){
	// 	y = 0;
	// 	while (y < 150){
	// 		my_mlx_pixel_put(&img, 400 + x, 300 + y, 0x00FF0000);
	// 		// printf("X= %d, Y= %d\n", x, y);
	// 		y++;
	// 	}
	// 	x++;
	// }
	// my_mlx_pixel_put(&img, 400, 300, 0x00FF0000);
	img.img = mlx_xpm_file_to_image(game.mlx_ptr, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,&img.line_length, &img.endian);
	 x = 0;
	while (x < 20){
		y = 0;
		while (y < 15){
			mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, img.img, x*img.width, y*img.height);
			// printf("X= %d, Y= %d\n", x, y);
			y++;
		}
		x++;
	}
	// mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, img.img, 400-(img.width/2), 300-(img.height/2));
	printf("%d\n",img.width);
	

	printf("entrou\n");
	mlx_loop_hook(game.mlx_ptr, &handle_no_event, &game);
	mlx_key_hook(game.win_ptr, &handle_input, &game);
	
	mlx_loop(game.mlx_ptr);
	
	end_game(&game);
	free(game.mlx_ptr);
}
