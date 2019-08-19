/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:45:24 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/19 11:20:02 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perceptron.h"

void	initialize_weights(float *weights)
{
	weights[0] = (float)rand()/RAND_MAX;
	weights[1] = (float)rand()/RAND_MAX;
	weights[2] = (float)rand()/RAND_MAX;
}