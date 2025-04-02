# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 13:23:49 by dpotsch           #+#    #+#              #
#    Updated: 2025/04/02 08:39:25 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFILE = test.mk

TARGET_EXEC = test

SRCS = srcs/test.c \
       srcs/utils/argument_utils.c \
       srcs/utils/mutex_utils.c \
       srcs/utils/mutex_value_utils.c \
       srcs/utils/thread_utils.c \
       srcs/utils/time_utils.c \
       srcs/utils/philo_utils_2.c \
       srcs/utils/philo_utils.c \
       srcs/init_philo_2.c \
       srcs/init_philo.c \
       srcs/join_philo_threads.c \
       srcs/start_philo_threads.c \
       srcs/philo_life.c \
       srcs/philo_life_utils.c \
       srcs/philo_monitoring_utils.c \
       srcs/philo_monitoring.c \
       srcs/philo_state.c \
       srcs/parse_arguments.c \
       srcs/philo_free.c

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
