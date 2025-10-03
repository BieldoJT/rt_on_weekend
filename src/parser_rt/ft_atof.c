/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/03 15:02:44 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init(int *i, double *int_part, double *frac_part, double *divisor)
{
	*i = 0;
	*int_part = 0;
	*frac_part = 0;
	*divisor = 1;
}

double	ft_atof(char *str)
{
	int		i;
	int		sig;
	double	int_part;
	double	divisor;
	double	frac_part;

	sig = 1;
	init(&i, &int_part, &frac_part, &divisor);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sig = -1;
	while (str[i] >= '0' && str[i] <= '9')
		int_part = int_part * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			frac_part = frac_part * 10 + (str[i++] - '0');
			divisor *= 10;
		}
	}
	return (sig * (int_part + frac_part / divisor));
}
