DIR_INC = ./source
DIR_SRC = ./source
DIR_BUILD = ./Release
DIR_BIN = ./Release

CC = sdcc
PROJ_NAME = thermometer
CFLAGS = -mmcs51 --iram-size 256 --code-loc 0x0000 --code-size 0x2000 -I${DIR_INC}

SRCS = $(wildcard ${DIR_SRC}/*.c)  

RELS = $(patsubst %.c,${DIR_BUILD}/%.rel,$(notdir ${SRCS})) 

$(DIR_BIN)/$(PROJ_NAME).bin : $(DIR_BIN)/$(PROJ_NAME).hex
	objcopy -I ihex -O binary $< $@

$(DIR_BIN)/$(PROJ_NAME).hex : $(DIR_BIN)/$(PROJ_NAME).ihx
	packihx $< > $@

$(DIR_BIN)/$(PROJ_NAME).ihx : $(RELS) | $(DIR_BIN)
	$(CC) $^ -o $@

${DIR_BUILD}/%.rel : ${DIR_SRC}/%.c | $(DIR_BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BUILD) :
	mkdir $(DIR_BUILD)

$(DIR_BIN) :
	mkdir $(DIR_BIN)

.PHONY : clean print

clean :
	rm -f $(DIR_BUILD)/*

print:
	echo "debug"