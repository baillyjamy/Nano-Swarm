CC =	g++

RM =	rm -f

CFLAGS +=	-W -Wextra -Wall
CFLAGS +=	-I./

CPPFLAGS +=	-W -Wextra -Wall
CPPFLAGS +=	-I./include -I. -std=c++11 -Ofast

LDFLAGS = `pkg-config --static --libs glfw3`

NAME = nano-swarm

SRCS_C = gl3w.c

SRCS_CPP = 	source/main.cpp \
		source/my_opengl.cpp \
		source/display.cpp \
		source/fps_counter.cpp \
		source/input.cpp \

OBJS = 	$(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
