# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 12:08:33 by dpotsch           #+#    #+#              #
#    Updated: 2025/03/14 13:20:25 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# * RUN ./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP].
# *     OPTIONAL [number_of_times_each_philosopher_must_eat].

# Variables
ARGS := 5 800 200 200 3
VALG_FLAGS := --trace-children=yes --leak-check=full


run: all
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@./$(TARGET_EXEC) $(ARGS)

runv: all
	@printf "$(PINK)$(VALG_FLAGS) ./$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@valgrind $(VALG_FLAGS) $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)

runf: all
	@printf "$(PINK)funcheck -a $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@funcheck -a $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)

tests: all
	@printf "$(PINK)./$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@./$(TARGET_EXEC) $(ARGS) > out
	@printf "$(PINK)python3 ../testing/visualize.py$(NC)\n"
	@python3 ../testing/visualize.py

visu:
	@printf "$(PINK)python3 ../testing/visualize.py$(NC)\n"
	@python3 ../testing/visualize.py

tester: all
	@printf "$(PINK)../testing/philo_tester/test.sh ./$(TARGET_EXEC)$(NC)\n"
	@../testing/philo_tester/test.sh ./$(TARGET_EXEC)

.PHONY: run runv runf tests visu

-include ../colors.mk