CC =	g++

RM =	rm -f

CFLAGS +=	-W -Wall -Wextra
CFLAGS +=	-I./

CPPFLAGS +=	-W -Wall -Wextra
CPPFLAGS +=	-I. -I./include -std=c++11 -g3

LDFLAGS = `pkg-config --static --libs glfw3` -lsfml-audio -lsfml-system

NAME = nano-swarm

SRCS_C = gl3w.c

SRCS_CPP = 	source/main.cpp \
		source/my_opengl.cpp \
		source/display.cpp \
		source/fps_counter.cpp \
		source/callback.cpp \
		source/nanobot.cpp \
		source/scrap.cpp \
		source/logic.cpp \
		source/main_loop.cpp \
		source/render_context.cpp \
		source/render_texture.cpp \
		source/number_texture.cpp \

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
