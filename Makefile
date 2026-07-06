CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/main.c
OUT = lain

# --- OS detection ---
ifeq ($(OS),Windows_NT)
    OUT := $(OUT).exe
    LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
    RM = del /f /q
    RUN = $(OUT)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    endif
    RM = rm -f
    RUN = ./$(OUT)
endif

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	$(RM) $(OUT)

run: $(OUT)
	$(RUN)

.PHONY: clean run