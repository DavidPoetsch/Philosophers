# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_bonus.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 13:23:49 by dpotsch           #+#    #+#              #
#    Updated: 2025/03/26 13:12:00 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFILE = test_bonus.mk

TARGET_EXEC = test_bonus

SRCS = srcs/test_bonus.c \
       srcs/close_semaphores.c \
       srcs/error_handler.c \
       srcs/utils/ft_itoa.c \
       srcs/utils/ft_strjoin.c \
       srcs/utils/philo_utils_1.c \
       srcs/utils/philo_utils_2.c \
       srcs/utils/time_utils.c \
       srcs/utils/argument_utils.c \
       srcs/utils/sem_value_utils.c \
       srcs/utils/sem_utils.c \
       srcs/utils/thread_utils.c \
       srcs/utils/void_ptr_wrapper.c \
       srcs/parse_arguments.c \
       srcs/init_philo_2.c \
       srcs/init_philo.c \
       srcs/init_semaphores.c \
       srcs/philo_free.c \
       srcs/philo_life.c \
       srcs/philo_life_utils.c \
       srcs/philo_life_utils_2.c \
       srcs/philo_monitoring.c \
       srcs/sim_monitoring.c \
       srcs/start_philo_processes.c \
       srcs/start_philo_threads.c \
       srcs/philo_state.c \
       srcs/wait_utils.c

# **************************************************************************** #
# * TEST CRITERION
LDFLAGS_TEST = -lcriterion
test_criterion:
	@echo "$(BLUE)Build    '$(TARGET_EXEC)'$(RESET)"
	@$(MAKE) -s -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=1 LDFLAGS="$(LDFLAGS_TEST)"
	@./test_bonus

-include ../colors.mk
-include ../general.mk
