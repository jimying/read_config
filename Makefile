APP		   := test
BUILD      := obj
PATH_3RD   := thirdparty
CFLAGS := -Wall
CFLAGS += -DPJ_AUTOCONF
CFLAGS += -g
#CFLAGS += -DNDEBUG

INC = -I./ -I $(PATH_3RD)/pjsip/include
LIBS = $(PATH_3RD)/pjsip/lib/libpjlib-util.a $(PATH_3RD)/pjsip/lib/libpj.a
LIBS += -lm -pthread
#LIBS += -framework Cocoa
#LIBS += -luuid

SRCS = main.c
OBJS = $(addprefix $(BUILD)/, $(addsuffix .o,$(basename $(SRCS))))

all: $(APP)
clean:
	@rm -rf $(APP) $(BUILD)

$(BUILD): Makefile
	@mkdir -p $(BUILD)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^  $(LIBS)

$(BUILD)/%.o: %.c Makefile | $(BUILD)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(DFLAGS)

