ARCH ?= x86

ifeq ($(ARCH),x86)
	CC=gcc
else
	CC=arm-linux-gnueabihf-gcc
endif

TARGET=mysql
BUILD_DIR=build
SRC_DIR=.
INC_DIR=.
CFLAGS=$(patsubst %,-I%,$(INC_DIR))
INCLUDES=$(foreach dir,$(INC_DIR),$(wildcard $(dir)/*.c))

SOURCE=$(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))
OBJS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCE)))
VPATH=$(SRC_DIR)

$(BUILD_DIR)/$(TARGET):$(OBJS)
	$(CC) $^ -o $@ -lmysqlclient

$(BUILD_DIR)/%.o:%.c $(INCLUDES) | create_build
	$(CC) -c $< -o $@ -lmysqlclient

.PHONY:clean create_build copy

clean:
	rm -r $(BUILD_DIR)

create_build:
	mkdir -p $(BUILD_DIR)

copy:
	cp $(BUILD_DIR)/$(TARGET) /home/qrs/workdir/test/

