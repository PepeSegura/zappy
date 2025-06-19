MAKEFLAGS	= --no-print-directory --silent

NAME := server

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror
DEBUG := -g3 -fsanitize=address

# Add hostname definition
HOSTNAME := $(shell hostname)
CPPFLAGS_EXTRA := -DHOSTNAME=\"$(HOSTNAME)\"

RM := rm -rf

BUILD_DIR := .objs/

SRC_DIR := srcs/
INC_DIR := inc/

PRESRC := 							\
			main.cpp				\
			TCPServer/TCPServer.cpp

SRCS := $(addprefix $(SRC_DIR), $(PRESRC))

OBJS := $(SRCS:$(SRC_DIR)%.cpp=$(BUILD_DIR)%.o)
DEPS := $(OBJS:.o=.d)

INC := $(INC_DIR) $(INC_DIR)User $(INC_DIR)TCPServer $(INC_DIR)Channel $(INC_DIR)Message $(INC_DIR)Cmd
INC_FLAGS := $(addprefix -I , $(INC))

CPPFLAGS := $(INC_FLAGS) -MMD -MP $(CPPFLAGS_EXTRA)

# BONUS sources
BONUS_DIR := bonus/
BONUS_SRCS := $(wildcard $(BONUS_DIR)*.cpp)
BONUS_OBJS := $(BONUS_SRCS:$(BONUS_DIR)%.cpp=$(BUILD_DIR)$(BONUS_DIR)%.o)
BONUS_DEPS := $(BONUS_OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) $(DEBUG) -o $@ && printf "Linking: $(NAME)\n"

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEBUG) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"


# BONUS compilation rules
$(BONUS_NAME): $(BONUS_OBJS)
	@$(CXX) $(BONUS_OBJS) $(DEBUG) -o $@ && printf "Linking: $(BONUS_NAME)\n"

$(BUILD_DIR)$(BONUS_DIR)%.o: $(BONUS_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEBUG) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

bonus: $(BONUS_NAME)

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)

re:: fclean
re:: $(NAME)

.PHONY: all clean fclean re valgrind bonus

-include $(DEPS)
