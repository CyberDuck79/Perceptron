/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perceptron.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:59:58 by fhenrion          #+#    #+#             */
/*   Updated: 2019/08/20 18:11:02 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct
{
	char	letter;
	int		matrix[5][5];
}			letter;

void		perceptron(letter **alphabet, int let_i, int len);