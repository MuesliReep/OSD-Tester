

CC = gcc #TODO: ARM

###
###  CFLAGS
###

CFLAGS  = -std=c99

CFLAGS += -Ilib/opencv/include/


###
###  Libs
###

LIBS  = -Llib/opencv/lib/
LIBS += -lm
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
#LIBS += -lcv -lhighgui

###
###  Dirs & Files
###

SRCDIR = src
BLDDIR = bld
MKBLDDIR = @mkdir -p $(BLDDIR)
BIN  = OSD-Tester
ALLTARGETS = OSD-Tester

SRC_FILES  = main.c
SRC_FILES += output.c
SRC_FILES += ArrayHelper.c
SRC_FILES += DataStream.c
SRC_FILES += OSD.c
SRC_FILES += Graphics.c
SRC_FILES += Telemetry.c

ifndef V
  QUIET_CC   = @echo ' CC   ' $<;
  QUIET_LINK = @echo ' LINK ' $@;
  QUIET_TEST = >/dev/null 2>&1
endif

SRC  := $(patsubst %,$(SRCDIR)/%,$(SRC_FILES))
SRC  := $(sort $(SRC))
OBJ  := $(patsubst $(SRCDIR)/%.c,$(BLDDIR)/%.o,$(SRC))
DEPS := $(patsubst $(SRCDIR)/%.c,$(BLDDIR)/%.d,$(SRC))

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	$(MKBLDDIR)
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@

OSD-Tester: $(OBJ)
	$(QUIET_LINK)$(CC) $(LDOPTS) -o $(BIN) $(OBJ) $(LIBS)

# do not move the following line:
-include $(DEPS)

###
###  Common
###

all: $(ALLTARGETS)

clean:
	rm -f $(ALLTARGETS) *~ gmon*
	rm -rf $(BLDDIR)