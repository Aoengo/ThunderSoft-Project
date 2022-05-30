TARGET		:= ThunderSoft_Project

CC			:= gcc
LD			:= gcc
LIB_PATH	:= -lpthread

BUILD_DIR	:= ./build
SRC_DIR		:= ./src
OBJ_DIR		:= $(BUILD_DIR)/obj

SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJS 		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))




$(BUILD_DIR)/$(TARGET)	: $(OBJS)
	@echo LD	$^
	@$(LD) $(OBJS) -o $(BUILD_DIR)/$(TARGET) $(LIB_PATH)

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c
	@echo CC	$<
	@$(CC) -c $< -o $@ $(LIB_PATH)




clean: 
	@rm -rf build/obj/*.o build/ThunderSoft_Project
	@echo "Clean Successful"










