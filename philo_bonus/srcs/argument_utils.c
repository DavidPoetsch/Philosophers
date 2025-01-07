/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:29:34 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 09:31:33 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	init_args(t_args *args, int argc, char *argv[])
{
	args->argc = argc;
	args->argv = argv;
	args->i = 0;
}
