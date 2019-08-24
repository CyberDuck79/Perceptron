/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_perceptron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:18:54 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/24 10:32:48 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

//fonction sigmoide
static double	sigmo(double a)
{
	if (a < -20.0)
	{
		return 0.0;
	}
	else if (a > 20.0)
	{
		return 1.0;
	}
	return (1.0 / (1.0 + exp(-a)));
}


static float		activate(int **matrix, float *weights)
{
	float	sum = 0;

	for (int y = 0; y < X; y++)
			for (int x = 0; x < X; x++)
				sum += matrix[x][y] * weights[x + (y*5)];
	sum += weights[X*X];
	// fonction d'activation : a seuil ou de Heaviside
	//return (sum < 0 ? 0 : 1);
	// fonction d'activation : sigmoide
	return (sigmo(sum));
}

void			reco_perceptron(weights **alphabet, int **matrix)
{
	int		l = 0;
	float	err;
	float	err_max = 0.0;

	for (int i = 0; i < N; i++)
	{
		if ((err = activate(matrix, alphabet[i]->weights)) > err_max)
		{
			err_max = err;
			l = i;
		}
	}
	printf("Lettre reconnue : %c\n", alphabet[l]->letter);
}