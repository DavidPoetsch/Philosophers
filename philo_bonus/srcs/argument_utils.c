/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:29:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 09:20:43 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_args(t_args *args, int argc, char *argv[])
{
	args->argc = argc;
	args->argv = argv;
	args->i = 0;
}
