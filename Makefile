CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Wno-unused-parameter -pedantic
LDFLAGS = -L./lib/rbc_lib -lrbc -lcrypto -O3

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
EXEC = abepke
MAIN = src/main.c

BUILD_DIR = build

TEST_SRC = $(filter-out $(MAIN), $(SRC)) tests/test_main.c
TEST_OBJ = $(patsubst src/%.c, build/%.o, $(filter-out $(MAIN), $(SRC)))
TEST_EXEC = tests/test_runner


all: check_install_rbc $(BUILD_DIR) $(EXEC)

check_install_rbc:
	@if [ ! -f lib/rbc_lib/librbc.a ] || [ ! -f lib/rbc_lib/librbc-nist.a ]; then \
		echo "RBC library not found, install it with: make install_rbc"; \
		exit 1; \
	fi

install_rbc:
	chmod +x install_rbc.sh
	./install_rbc.sh

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)

build/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

keygen: all
	@read -p "Enter filename for the public key (default: public.key): " pub; \
	 read -p "Enter filename for the private key (default: private.key): " priv; \
	 pub=$${pub:-public.key}; \
	 priv=$${priv:-private.key}; \
	 echo "Generating keys..."; \
	 ./$(EXEC) keygen $$pub $$priv; \
	 echo "Keys generated: $$pub (public), $$priv (private)"

test: $(TEST_OBJ) build/test_main.o
	$(CC) $(CFLAGS) $(TEST_OBJ) build/test_main.o -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

build/test_main.o: tests/test_main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c tests/test_main.c -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(EXEC) $(TEST_EXEC)

.PHONY: clean install_rbc maybe_install_rbc
