MAKEFLAGS	= --no-print-directory --silent

NAME := server

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror
DEBUG := -g3 -fsanitize=address

# Add hostname definition
HOSTNAME := $(shell hostname)
CPPFLAGS_EXTRA := -D HOSTNAME=\"$(HOSTNAME)\"

RM := rm -rf

BUILD_DIR := .objs/

SRC_DIR := srcs/
INC_DIR := inc/

PRESRC := 							\
			main.cpp				\
			Parser/FlagParser.cpp	\
			Parser/Parser.cpp		\
			TCPServer/TCPServer.cpp

SRCS := $(addprefix $(SRC_DIR), $(PRESRC))

OBJS := $(SRCS:$(SRC_DIR)%.cpp=$(BUILD_DIR)%.o)
DEPS := $(OBJS:.o=.d)

INC := $(INC_DIR) $(INC_DIR)Parser $(INC_DIR)TCPServer $(INC_DIR)Game
INC_FLAGS := $(addprefix -I , $(INC))

CPPFLAGS := $(INC_FLAGS) -MMD -MP $(CPPFLAGS_EXTRA)


all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) $(DEBUG) -o $@ && printf "Linking: $(NAME)\n"

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEBUG) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"


clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re:: fclean
re:: $(NAME)

.PHONY: all clean fclean re valgrind bonus

-include $(DEPS)
