# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    general.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 13:23:49 by dpotsch           #+#    #+#              #
#    Updated: 2025/03/14 16:47:57 by dpotsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS_DEBUG = -Wall -Wextra -Werror -g
CFLAGS_DEBUG_ASAN = -Wall -Wextra -Werror -g -fsanitize=address,undefined,bounds,float-divide-by-zero -fno-omit-frame-pointer
CFLAGS_DEBUG_TSAN = -Wall -Wextra -Werror -g -fsanitize=thread,undefined,bounds,float-divide-by-zero -fno-omit-frame-pointer
CFLAGS_DEBUG_HELG = -Wall -Wextra -Werror -g -O0
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
LDFLAGS_ASAN = -fsanitize=address,undefined,bounds,float-divide-by-zero -fno-omit-frame-pointer
LDFLAGS_TSAN = -fsanitize=thread,undefined,bounds,float-divide-by-zero -fno-omit-frame-pointer

# **************************************************************************** #
# * BUILD
all:
	@$(MAKE) -s $(TARGET_EXEC)
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

re: fclean all


# **************************************************************************** #
# * DEBUG
debug: clean
	@echo "$(PINK)Compiling with debug information$(RESET)"
ifeq ($(DEBUG), 1)
	$(MAKE) $(TARGET_EXEC) DEBUG=1 CFLAGS="$(CFLAGS_DEBUG_ASAN)" LDFLAGS="$(LDFLAGS_ASAN)"
else ifeq ($(DEBUG), 2)
	$(MAKE) $(TARGET_EXEC) DEBUG=1 CFLAGS="$(CFLAGS_DEBUG_TSAN)" LDFLAGS="$(LDFLAGS_TSAN)"
else ifeq ($(DEBUG), 3)
	$(MAKE) $(TARGET_EXEC) DEBUG=2 CFLAGS="$(CFLAGS_DEBUG_HELG)"
else
	$(MAKE) $(TARGET_EXEC) DEBUG=0 CFLAGS="$(CFLAGS_DEBUG)"
endif
	@echo "$(GREEN)Finished '$(TARGET_EXEC)'$(RESET)"


# **************************************************************************** #
# * CLEAN

clean:
	@echo "$(YELLOW)Clean    '$(TARGET_EXEC)'$(RESET)"
	@rm -rf $(BUILD_DIR)/srcs

fclean:
	@echo "$(YELLOW)F-Clean  '$(TARGET_EXEC)'$(RESET)"
	@$(MAKE) -s clean
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET_EXEC)
	@rm -rf out
	@rm -rf fails

.PHONY: all clean fclean re bonus debug

# Include the .d dependencies. The - at the front suppresses the errors of 
# missing dependencies. Initially, all the .d files will be missing, 
# and we don't want those errors to show up.
-include $(DEPS)
-include colors.mk
