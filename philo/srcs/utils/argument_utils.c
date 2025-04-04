/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:29:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/04 10:50:06 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Initialize arguments
 * 
 * - puts programm arguments into an args struct
 * 
 * @param args args struct
 * @param argc 
 * @param argv 
 */
void	init_args(t_args *args, int argc, char *argv[])
{
	args->argc = argc;
	args->argv = argv;
	args->i = 0;
}
