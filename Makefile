# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 12:08:33 by dpotsch           #+#    #+#              #
#    Updated: 2024/12/16 17:05:08 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET_EXEC := philo
TARGET_DIR := ./$(TARGET_EXEC)/build
LIBS_DIR := ./$(TARGET_EXEC)/libs

# Colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
PINK   := \033[0;35m
NC  := \033[0m

all:
	@$(MAKE) -s -C $(TARGET_EXEC)

$(TARGET_EXEC):
	@$(MAKE) -s -C $(TARGET_EXEC)

bonus:
	@$(MAKE) bonus -s -C $(TARGET_EXEC)

clean:
	@$(MAKE) clean -s -C $(TARGET_EXEC)

fclean:
	@$(MAKE) fclean -s -C $(TARGET_EXEC)

debug:
	@$(MAKE) debug -C $(TARGET_EXEC)

re: fclean all


# **************************************************************************** #
# * RUN ./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP].
# *     OPTIONAL [number_of_times_each_philosopher_must_eat].

# Variables
ARGS := 5 10000 1000 1000 1
run: all
	@printf "$(PINK)$(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@$(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)

VALG_FLAGS := --trace-children=yes --leak-check=full
runv: all
	@printf "$(PINK)$(VALG_FLAGS) $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@valgrind $(VALG_FLAGS) $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)

runf: all
	@printf "$(PINK)funcheck -a $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)$(NC)\n"
	@funcheck -a $(TARGET_DIR)/$(TARGET_EXEC) $(ARGS)

tests: $(TARGET_EXEC)
	@printf "$(PINK)"
	../testing/tester.sh
	@printf "$(NC)"

.PHONY: all $(TARGET_EXEC) clean fclean re bonus run runv runf
