/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_perceptron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:18:54 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/21 15:50:17 by fhenrion         ###   ########.fr       */
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


static int		activate(int **matrix, float *weights)
{
	float	sum = 0;

	for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				sum += matrix[x][y] * weights[x + (y*5)];
	sum += weights[25];
	// fonction d'activation : a seuil ou de Heaviside
	//return (sum < 0 ? 0 : 1);
	// fonction d'activation : sigmoide
	return (sigmo(sum) > 0.5 ? 1 : 0);
}

void			reco_perceptron(weights **alphabet, int **matrix)
{
	for (int i = 0; i < 26; i++)
		if (activate(matrix, alphabet[i]->weights))
			printf("Lettre reconnue : %c\n", alphabet[i]->letter);
}