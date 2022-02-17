/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:47:59 by acarneir          #+#    #+#             */
/*   Updated: 2022/02/16 23:33:15 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		ft_free_ptr((void *)&map[i]);
		i++;
	}
	ft_free_ptr((void *)&map);
}

void	load_map(char **argv, t_game *game)
{
	int		fd;
	char	*line;
	char	*old_map;
	char	*map;

	fd = open_fd(argv);
	map = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		old_map = map;
		map = ft_strjoin(old_map, line);
		ft_free_ptr((void *)&old_map);
		ft_free_ptr((void *)&line);
	}
	game->map.matrix = ft_split(map, '\n');
	ft_free_ptr((void *)&map);
	close(fd);
	check_map(&game->map);
}
