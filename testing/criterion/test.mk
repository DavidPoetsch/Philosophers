# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 13:23:49 by dpotsch           #+#    #+#              #
#    Updated: 2025/03/20 14:08:01 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFILE = test.mk

TARGET_EXEC = test

SRCS = srcs/test.c \
       srcs/argument_utils.c \
       srcs/init_philo_2.c \
       srcs/init_philo.c \
       srcs/join_philo_threads.c \
       srcs/start_philo_threads.c \
       srcs/philo_life.c \
       srcs/philo_life_utils.c \
       srcs/philo_monitoring_utils.c \
       srcs/philo_monitoring.c \
       srcs/philo_state.c \
       srcs/philo_utils_2.c \
       srcs/philo_utils.c \
       srcs/time_utils.c \
       srcs/mutex_utils.c \
       srcs/mutex_value_utils.c \
       srcs/parse_arguments.c \
       srcs/philo_free.c \
       srcs/debug.c \
       srcs/thread_utils.c

# **************************************************************************** #
# * TEST CRITERION
LDFLAGS_TEST = -lcriterion
test_criterion:
	@echo "$(BLUE)Build    '$(TARGET_EXEC)'$(RESET)"
	@$(MAKE) -s -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=1 LDFLAGS="$(LDFLAGS_TEST)"
	@./test

-include ../colors.mk
-include ../general.mk
-include ../testing/Makefile
