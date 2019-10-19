
# Use the arm cross compiler (change this to your path)
CC = ../tools/gcc-arm-none-eabi-8-2019-q3-update/bin/arm-none-eabi-gcc

# Top level constants
RASPI_MODEL = 1
OUTPUT_IMAGE_NAME = kernel.img

# Set any constants based on the raspberry pi model.  Version 1 has some differences to 2 and 3
ifeq ($(RASPI_MODEL),1)
    CPU = arm1176jzf-s
    DIRECTIVES = -D RPI_MAJOR_VERSION=1
else
    CPU = cortex-a7
    DIRECTIVES = -D RPI_MAJOR_VERSION=2
endif

#c flags
CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES) -nostdlib
CSRCFLAGS = -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib


#locations of the files
SRC_DIR = src
HEADER_DIR = include
OBJ_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) \
			$(wildcard $(SRC_DIR)/drivers/*.c)

ASM_FILES = $(SRC_DIR)/boot.s

OBJECTS   = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJECTS  += $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_FILES))

HEADERS  = $(wildcard $(HEADER_DIR)/*.h)



# --------- TARGETS ----------

# Take object files and link the final image!
build : $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	mkdir -p $(@D)
	$(CC) -T linker.ld -o $(OUTPUT_IMAGE_NAME) $(LFLAGS) -I$(HEADER_DIR) $(OBJECTS)

# # Build 'driver' c files
$(OBJ_DIR)/%.o : $(SRC_DIR)/drivers/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR)/drivers -I$(HEADER_DIR) -c $< -o $@ $(CSRCFLAGS)

# Build the object files from the top level c files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(HEADER_DIR) -c $< -o $@ $(CSRCFLAGS)

#build object files from asm files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)
	rm $(OUTPUT_IMAGE_NAME)

#run the system emulator
run : build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel kernel.img
