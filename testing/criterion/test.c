/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:37:36 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 15:21:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <criterion/criterion.h>

Test(main, args_error)
{
	// ERROR
	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 1;
		char *argv[] = {"./philo"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 2;
		char *argv[] = {"./philo", "1"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 3;
		char *argv[] = {"./philo", "1", "2"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 4;
		char *argv[] = {"./philo", "1", "2", "3"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "-1", "2", "3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "-2", "3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2", "-3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2", "3", "-4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "3", "4" , "-5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "2147483648", "2", "3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2147483648", "3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2", "2147483648", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2", "3", "2147483648"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "3", "4" , "2147483648"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "0", "2", "3", "4", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "0", "3", "4", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "0", "4", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "3", "0", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "3", "4", "0"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "2147483647", "2", "3", "4", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == ERROR);
	}
}

//# SUCCESS
Test(main, init_success)
{
	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 5;
		char *argv[] = {"./philo", "1", "2", "3", "4"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == SUCCESS);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "1", "2", "3", "4", "5"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == SUCCESS);
	}

	{
		t_args			args;
		t_philo_handler	ph;
		int argc = 6;
		char *argv[] = {"./philo", "5", "2147483647", "2147483647", "2147483647", "2147483647"};
		memset(&ph, 0, sizeof(t_philo_handler));
		init_args(&args, argc, argv);
		cr_assert(init_philos(args, &ph) == SUCCESS);
	}
}
