# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 12:08:33 by dpotsch           #+#    #+#              #
#    Updated: 2024/12/06 11:46:38 by dpotsch          ###   ########.fr        #
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
	@$(MAKE) debug -s -C $(TARGET_EXEC)

re: fclean all


# **************************************************************************** #
# * RUN
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
