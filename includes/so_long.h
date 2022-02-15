/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:34:21 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/15 01:27:29 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define ESC	0xff1b
# define LEFT	0x61
# define RIGHT	0x64
# define UP		0x77
# define DOWN	0x73

# define SPRITE_DIM	50

typedef struct s_window
{
	void	*win;
	int		width;
	int		height;
}				t_window;

typedef struct s_counter
{
	int		exit;
	int		collectible;
	int		player;
	int		steps;
}	t_counter;

typedef struct s_map
{
	int			max_x;
	int			max_y;
	char		**matrix;
	t_counter	counter;
}	t_map;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_sprite;

typedef struct s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct s_player
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
	t_pos	*pos;
}	t_player;





typedef struct s_game
{
	void		*mlx;
	t_window	*window;
	t_map		map;
	t_sprite	collectible;
	t_sprite	exit;
	t_sprite	floor;
	t_sprite	wall;
	t_player	player;
}	t_game;

void	check_args(int argc, char **argv);
int		open_fd(char **argv);
void	print_error(char *msg);
void	ft_free_ptr(void **ptr);
void	load_map(char **argv, t_game *game);
void	check_map(t_map *map);
void	free_map(char **map);
void	load_game(t_game *game);
int		key_hooks(int key, t_game *game);
int		end_game(t_game *game);


#endif