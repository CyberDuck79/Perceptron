/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:39:13 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/18 14:02:35 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "perceptron.h"

// SUPERVISED LEARNING - 2D inputs classifier
int		main(void)
{
	float	**train_set;
	float	*weights;
	float	sum = 0;
	float	result = 0;
	float	error = 0;
	float	success = 0;

	train_set = (float**)malloc(sizeof(float*) * 30);
	weights = (float*)malloc(sizeof(float) * 3);
	for (int i = 0; i < 30; i++)
		train_set[i] = (float*)malloc(sizeof(float) * 3);
	initialize_train_set(train_set);
	weights[0] = (float)rand()/RAND_MAX;
	weights[1] = (float)rand()/RAND_MAX;
	weights[2] = (float)rand()/RAND_MAX;

	while (success < 30)
	{
		success = 0;
		for (int j = 0; j < 30; j++)
		{
			sum = 0;
			printf("set     -> x : %f, y : %f, result : %f\n", train_set[j][0], train_set[j][1], train_set[j][2]);
			printf("weights -> 1 : %f, 2 : %f, 3 : %f\n", weights[0], weights[1], weights[2]);
			for (int i = 0; i < 2; i++)
					sum += train_set[j][i] * weights[i];
			sum += 1 * weights[2];
			result = sum < 0 ? -1 : 1;
			error = train_set[j][2] - result;
			if (error == 0)
				success++;
			printf("result  -> %f error : %f\n", result, error);
			weights[0] = weights[0] + (error * train_set[j][0]);
			weights[1] = weights[1] + (error * train_set[j][1]);
			weights[2] = weights[2] + error;
			printf("new Wgt -> 1 : %f, 2 : %f, 3 : %f\n", weights[0], weights[1], weights[2]);
		}
	}
	return (0);
}
/*
	float	*inputs;
	float	*weights;
	float	sum = 0;

	inputs = (float*)malloc(sizeof(float) * 3);
	weights = (float*)malloc(sizeof(float) * 3);
	if (argc == 1 || argc > 3)
		write(1, "USAGE : x, y\n", 26);
	else
	{
		
		initialization(inputs, weights, atof(argv[1]), atof(argv[2]));

		for (int i = 0; i < nb_inputs; i++)
			sum += inputs[i] * weights[i];
		sum < 0 ? write(1, "1\n", 2) : write(1, "-1\n", 3);
	}
	return (0);
}
*/ 
