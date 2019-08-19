/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:39:13 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/19 15:17:48 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

//fonction sigmoide
double	sigmo(double a)
{
	double	aux = exp(a);

	return (1 / (aux + 1));
}

//operateur derive
double	deriv(double fa)
{
	return (fa * (1 - fa));
}

int		train(float **train_set, int *desired, float *weights)
{
	float	sum = 0;
	float	learning_rate = 0.1;
	int		result = 0;
	int		error = 0;
	int		nb_errors = 0;

	for (int i = 0; i < 40; i++)
	{
		sum = 0;
		sum += train_set[i][0] * weights[0];
		sum += train_set[i][1] * weights[1];
		sum += 1 * weights[2];
		// fonction d'activation : a seuil ou de Heaviside
		//result = sum < 0 ? 0 : 1;
		// fonction d'activation : sigmoide
		result = sigmo(sum) > 0.5 ? 0 : 1;
		error = desired[i] - result;
		if (error)
			nb_errors++;
		// fonction d'activation : a seuil ou de Heaviside
		weights[0] = weights[0] + (learning_rate * error * train_set[i][0]);
		weights[1] = weights[1] + (learning_rate * error * train_set[i][1]);
		weights[2] = weights[2] + (learning_rate * error);
		// fonction d'activation : sigmoide
		// -> calcul du gradient puis retour ?
	}
	return (nb_errors);
}

// SUPERVISED LEARNING - 2D inputs classifier
int		main(void)
{
	float	**train_set = (float**)malloc(sizeof(float*) * 40);
	float	*weights = (float*)malloc(sizeof(float) * 3);
	int		*desired = (int*)malloc(sizeof(int) * 40);
	int		try = 0;
	int		errors;

	initialize_train_set(train_set, desired);
	initialize_weights(weights);
	while ((errors = train(train_set, desired, weights)))
	{
		try++;
		printf("essai %d, nombres d'erreurs : %d\n", try, errors);
	}
	printf("SUCCES !\npoids finaux :\n");
	printf("wx : %f\n", weights[0]);
	printf("wy : %f\n", weights[1]);
	printf("wb : %f\n", weights[2]);
	return (0);
}
