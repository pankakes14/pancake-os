
# Use the arm cross compiler (change this to your path)
CC = ../tools/gcc-arm-none-eabi-8-2019-q3-update/bin/arm-none-eabi-gcc

# Top level constants
RASPI_MODEL = 1
OUTPUT_IMAGE_NAME = pancake_os.img

# Set any constants based on the raspberry pi model.  Version 1 has some differences to 2 and 3
ifeq ($(RASPI_MODEL),1)
    CPU = arm1176jzf-s
    DIRECTIVES = -D MODEL_1
else
    CPU = cortex-a7
endif

#c flags
CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES) 
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
OBJECTS  += $(patsubst $(SRC_DIR)/drivers/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJECTS  += $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_FILES))

HEADERS  = $(wildcard $(HEADER_DIR)/*.h)



# --------- TARGETS ----------

# Take object files and link the final image!
build : $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	$(CC) -T linker.ld -o $(OUTPUT_IMAGE_NAME) $(LFLAGS) $(OBJECTS)


# Build the object files from the top level c files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

# Build 'driver' c files
$(OBJ_DIR)/%.o : $(SRC_DIR)/drivers/%.c
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

#build object files from asm files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)
	rm $(OUTPUT_IMAGE_NAME)

#this doesn't work right meow
run : build
	qemu-system-arm -m 256 -M raspi1 -serial stdio -kernel kernel.img