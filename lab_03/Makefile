CC := gcc
CFLAGS := -g -std=c99 -Wall -Werror -pedantic
UFLAGS := -lcheck -lpthread -lrt


TARGET := app.exe
UNIT_TARGET := unit_tests.exe

SRC_DIR := ./src
CFILES := $(wildcard $(SRC_DIR)/*.c)

HDRS_DIR := ./inc
HDRS := $(wildcard $(HDRS_DIR)/*.h)

OBJ_DIR := ./out
OBJS := $(CFILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

UNIT_DIR := ./unit_tests
UFILES := $(wildcard $(UNIT_DIR)/*.c)
UNIT_OBJS := $(UFILES:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJS += $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

.PHONY: unit clean


$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(UFLAGS) -c $< -o $@


$(UNIT_TARGET) : $(UNIT_OBJS)
	$(CC) $^ -o $@ $(UFLAGS)

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c $(HDRS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(UFLAGS) -c $< -o $@ 


unit: $(UNIT_TARGET)
	./$^

clean:
	$(RM) -rf $(OBJ_DIR) *.exe
