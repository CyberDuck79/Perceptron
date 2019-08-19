/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:31:39 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/19 14:39:45 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERCEPTRON_H
# define PERCEPTRON_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

void	initialize_train_set(float **train_set, int *desired);
void	initialize_weights(float *weights);

#endif