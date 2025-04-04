# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 13:23:49 by dpotsch           #+#    #+#              #
#    Updated: 2025/04/04 12:07:27 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFILE = Makefile

TARGET_EXEC := philo_bonus

SRCS = srcs/philosophers.c \
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

# Colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
PINK   := \033[0;35m
RESET  := \033[0m

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror
CFLAGS_DEBUG = -O3 -Wall -Wextra -Werror -g
CFLAGS_DEBUG_ASAN = -O3 -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS_DEBUG_TSAN = -O3 -Wall -Wextra -Werror -g -fsanitize=thread
CFLAGS_DEBUG_HELG = -O3 -Wall -Wextra -Werror -g
DEBUG = 0

BUILD_DIR = ./build

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
#OBJS := $(SRCS:srcs/%.c=$(BUILD_DIR)/srcs/%.o)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every include dir will need to be passed to CC so it can find header files.
INC_DIRS := ./includes
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA.
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate 'Makefiles' for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# -L specifies the library search path.
# -l tells the linker to link against a specific library.
# ft refers to the library name. 
LDFLAGS := ""
LDFLAGS_ASAN = -fsanitize=address
LDFLAGS_TSAN = -fsanitize=thread

# **************************************************************************** #
# * BUILD
all:
	@$(MAKE) -s -f $(MAKEFILE) $(TARGET_EXEC)
	@echo "$(GREEN)Finished '$(TARGET_EXEC)'$(RESET)"

$(TARGET_EXEC): $(OBJS)
	@echo "$(BLUE)Build    '$(TARGET_EXEC)'$(RESET)"
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
# $(dir ...) is a Make function that extracts the directory of a file path.
# $@ represents the target file in a rule (the file being built).
# $< gets the first prerequiste.
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
ifeq ($(DEBUG), 0)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
endif

re: 
	@$(MAKE) -s -f $(MAKEFILE) fclean
	@$(MAKE) -s -f $(MAKEFILE) all


# **************************************************************************** #
# * DEBUG
debug: clean
	@echo "$(PINK)Compiling with debug information$(RESET)"
ifeq ($(DEBUG), 1)
	$(MAKE) -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=1 CFLAGS="$(CFLAGS_DEBUG_ASAN)" LDFLAGS="$(LDFLAGS_ASAN)"
else ifeq ($(DEBUG), 2)
	$(MAKE) -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=1 CFLAGS="$(CFLAGS_DEBUG_TSAN)" LDFLAGS="$(LDFLAGS_TSAN)"
else ifeq ($(DEBUG), 3)
	$(MAKE) -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=2 CFLAGS="$(CFLAGS_DEBUG_HELG)"
else
	$(MAKE) -f $(MAKEFILE) $(TARGET_EXEC) DEBUG=1 CFLAGS="$(CFLAGS_DEBUG)"
endif
	@echo "$(GREEN)Finished '$(TARGET_EXEC)'$(RESET)"


# **************************************************************************** #
# * CLEAN

clean:
	@echo "$(YELLOW)Clean    '$(TARGET_EXEC)'$(RESET)"
	@rm -rf $(BUILD_DIR)/srcs

fclean:
	@echo "$(YELLOW)F-Clean  '$(TARGET_EXEC)'$(RESET)"
	@$(MAKE) -f $(MAKEFILE) -s clean
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET_EXEC)
	@rm -rf out
	@rm -rf fails
	@rm -rf test
	@rm -rf test_bonus

.PHONY: all clean fclean re bonus debug

# Include the .d dependencies. The - at the front suppresses the errors of 
# missing dependencies. Initially, all the .d files will be missing, 
# and we don't want those errors to show up.
-include $(DEPS)

# -include ../testing/Makefile
