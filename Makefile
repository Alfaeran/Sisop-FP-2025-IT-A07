CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGETS=server client
SRC_DIR=src
SCRIPTS_DIR=scripts

.PHONY: all clean demo

all: $(TARGETS)

server: $(SRC_DIR)/server.c
	$(CC) $(CFLAGS) -o server $(SRC_DIR)/server.c

client: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -o client $(SRC_DIR)/client.c

clean:
	del /Q server.exe client.exe history.log 2>nul || echo "Cleaned"

demo: all
	@echo "Running demo..."
	@chmod +x $(SCRIPTS_DIR)/demo.sh
	@./$(SCRIPTS_DIR)/demo.sh

install: all
	@echo "Making scripts executable..."
	@chmod +x $(SCRIPTS_DIR)/*.sh

help:
	@echo "Available targets:"
	@echo "  all    - Build server and client"
	@echo "  clean  - Remove built files and logs"
	@echo "  demo   - Run automated demo"
	@echo "  install- Make scripts executable"
	@echo "  help   - Show this help"
