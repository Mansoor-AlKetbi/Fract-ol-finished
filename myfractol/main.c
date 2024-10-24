/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-ketb <mal-ketb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:44:23 by mal-ketb          #+#    #+#             */
/*   Updated: 2024/08/01 01:19:03 by mal-ketb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	check_input(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1)
	{
		if (!(ft_isdigit(*s1) || *s1 == '.' || *s1 == '-' || *s1 == '+'))
			return (1);
		if (*s1 == '.' && (*(s1 + 1) == '\0' || !ft_isdigit(*(s1 + 1))))
			return (1);
		s1++;
	}
	while (*s2)
	{
		if (!((*s2 >= '0' && *s2 <= '9') || *s2 == '.' || *s2 == '-'
				|| *s2 == '+'))
			return (1);
		if (*s2 == '.' && (*(s2 + 1) == '\0' || !ft_isdigit(*(s2 + 1))))
			return (1);
		s2++;
	}
	return (0);
}

int	validate_arguments(int ac, char **av)
{
	if ((ac == 2 && ft_strncmp(av[1], "mandelbrot", 11) == 0) || (ac == 4
			&& ft_strncmp(av[1], "julia", 6) == 0 && !check_input(av[2],
				av[3])))
	{
		return (1);
	}
	return (0);
}

void	initialize_fractal(t_fractal *fractal, int ac, char **av)
{
	fractal->name = av[1];
	if (ac == 4 && ft_strncmp(av[1], "julia", 6) == 0)
	{
		fractal->julia_x = atoidbl(av[2]);
		fractal->julia_y = atoidbl(av[3]);
	}
	fractal_init(fractal);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (validate_arguments(ac, av))
	{
		initialize_fractal(&fractal, ac, av);
		fractal_render(&fractal);
		mlx_hook(fractal.mlx_window, 2, 0, key_handler, &fractal);
		mlx_hook(fractal.mlx_window, 17, 1L << 17, close_press, &fractal);
		mlx_hook(fractal.mlx_window, 4, 1L << 2, mouse_handler, &fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}
