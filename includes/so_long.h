/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:34:21 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/11 21:57:44 by acarneir         ###   ########.fr       */
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

typedef struct s_counter
{
	int		exit;
	int		collectible;
	int		player;
}	t_counter;

typedef struct s_map
{
	int			max_x;
	int			max_y;
	char		**matrix;
	t_counter	counter;
}	t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
}	t_game;

void	check_args(int argc, char **argv);
int		open_fd(char **argv);
void	print_error(char *msg);
void	ft_free_ptr(void **ptr);
void	load_map(char **argv, t_game *game);
void	check_map(t_map *map);
void	free_map(char **map);


#endif