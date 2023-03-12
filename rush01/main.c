/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:04:33 by lde-cast          #+#    #+#             */
/*   Updated: 2023/03/12 08:33:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct s_game	t_game;
struct s_game{
	char	puzzle[4][4];
	char	border[4][4];
};

void	verification(t_game *game, char *command, int axis[2], int mem);
void	sort(t_game *game);
void	show(t_game *game);

void	input_game(char *str, t_game *game)
{
	int		mem;
	int		axis[2];
	char	*command;

	system("cls");
	mem = 0;
	axis[0] = 0;
	axis[1] = 0;
	command = &str[0];
	while (*str && mem < 31)
	{
		if (*str == ' ')
		{
			str++;
			if (!*str)
				break ;
			mem++;
			*(command + mem) = *str;
		}
		if (mem == 0)
			*(command + 0) = *str;
		verification(game, command, axis, mem);
		mem++;
		str++;
	}
}

int	main(int argc, char **argv)
{
	char	*command;
	t_game	game;

	if (argc > 1)
	{
		command = argv[1];
		input_game(command, &game);
		sort(&game);
		show(&game);
	}
	return (0);
}

void	verification(t_game *game, char *command, int axis[2], int mem)
{
	if (game && command && *(command + mem) > 48 && *(command + mem) < 53)
	{
		game->border[axis[1]][axis[0]] = *(command + mem) - 48;
		//printf("(%i %i)%i ",axis[1], axis[0] , game->border[axis[1]][axis[0]]);
		axis[0]++;
		if (axis[0] > 3)
		{
			axis[0] = 0;
			axis[1]++;
			//printf("\n");
		}
	}
}

void	sort(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			if (game->border[y][x] == 4)
			{
				if(y == 0 || y == 1)
				{
					int i;

					i = 0;
					while(i < 4)
					{
						game->puzzle[y + i][x] = i + 1;
						i++;
					}
				}
				else
				{
					int i;
					int j;

					i = 0;
					j = y;
					while(i < 4)
					{
						//printf("*%i %i", 2 - y, i);
						game->puzzle[j][i] = i + 1;
						i++;
					}
					printf("\n");
				}
			}
			if (game->border[y][x] == 1)
			{
				game->puzzle[y][x - 2] = 5;
			}
			if (game->border[y][x] == 3 && game->border[y][x + 1] == 2)
			{
				//printf("**%i %i\n", x, y);
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	show(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			printf("%i ", game->puzzle[y][x]);
			//printf("%i ", game->border[y][x]);
			x++;
		}
		printf("\n");
		y++;
		x = 0;
	}
}
