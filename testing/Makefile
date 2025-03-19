# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 12:08:33 by dpotsch           #+#    #+#              #
#    Updated: 2025/03/19 13:56:06 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# * RUN ./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP].
# *     OPTIONAL [number_of_times_each_philosopher_must_eat].

# Variables
ARGS := 5 800 200 200 3
VALG_FLAGS := --trace-children=yes \
							--errors-for-leak-kinds=all \
							--leak-check=full \
							--read-var-info=yes \
							--show-error-list=yes \
							--show-leak-kinds=all \
							--track-origins=yes

HELGRINDFLAGS	=	--tool=helgrind \
					--read-var-info=yes \
					--show-error-list=yes

DRDFLAGS		=	--tool=drd \
					--read-var-info=yes \
					--show-error-list=yes

run: all
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS) $(RESET)\n"
	@./$(TARGET_EXEC) $(ARGS)

runv:
	$(MAKE) debug
	@printf "$(PINK)valgrind $(VALG_FLAGS) ./$(TARGET_EXEC) $(ARGS)$(RESET)\n"
	@valgrind $(VALG_FLAGS) ./$(TARGET_EXEC) $(ARGS)

run_asan:
	$(MAKE) debug DEBUG=1
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS) $(RESET)\n"
	@./$(TARGET_EXEC) $(ARGS)

run_tsan:
	$(MAKE) debug DEBUG=2
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS)$(RESET)\n"
	@TSAN_OPTIONS="die_after_fork=0" ./$(TARGET_EXEC) $(ARGS)

runh:
	$(MAKE) debug DEBUG=3
	@printf "$(PINK)valgrind $(HELGRINDFLAGS) ./$(TARGET_EXEC) $(ARGS)$(RESET)\n"
	@valgrind $(HELGRINDFLAGS) ./$(TARGET_EXEC) $(ARGS)

runf: all
	@printf "$(PINK)funcheck -a ./$(TARGET_EXEC) $(ARGS)$(RESET)\n"
	@funcheck -a ./$(TARGET_EXEC) $(ARGS)

tests: all
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS)$(RESET)\n"
	@./$(TARGET_EXEC) $(ARGS) > out
	@printf "$(PINK)python3 ../testing/visualize.py$(RESET)\n"
	@python3 ../testing/visualize.py

visu:
	@printf "$(PINK)python3 ../testing/visualize.py$(RESET)\n"
	@python3 ../testing/visualize.py

tester: all
	@printf "$(PINK)../testing/philo_tester/test.sh ./$(TARGET_EXEC)$(RESET)\n"
	@../testing/philo_tester/test.sh ./$(TARGET_EXEC)

.PHONY: run runv runf tests visu

-include ../colors.mk
