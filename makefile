#===CONFIGURATION===
NAME = a.out

SRC =\
	main.cpp\
	Solver.cpp\
	Vec2f.cpp\
	Drawer.cpp\
	Ball.cpp\
	QuadTree.cpp
	
CFLAGS = -Wall -Werror -Wextra -g3
LFLAGS = -lSDL2 -lSDL2_ttf

INCLUDES = -Ilibft/ -I./

OBJ_DIR = obj

#===AUTOMATIC VARS===

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))

#===TARGETS===
all : $(NAME)

#===COMPILING===
$(OBJ_DIR) :
	$(shell mkdir -p $(OBJ_DIR))
$(OBJ_DIR)/%.o : %.cpp
	mkdir -p $(dir $@)
	g++ $(CFLAGS) -o $@ -c $< $(INCLUDES)

#===LINKING===
$(NAME) : $(OBJ_DIR) $(LIBS) $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LFLAGS)

#===CLEAN===
clean :
	rm -rf $(OBJ_DIR) || true

#===FCLEAN===
fclean : clean
	rm -f $(NAME) $(NAME_BONUS) || true

#===RE===
re : fclean all


.PHONY : re fclean clean all default bonus