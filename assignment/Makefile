# Makefile variables
SERVER = tcpInfoServer
CLIENT = tcpInfoClient
EXT = .c

SRCDIR = src
SERVERSRCDIR = src/server
CLIENTSRCDIR = src/client

OBJDIR = obj
SERVEROBJDIR = obj/server
CLIENTOBJDIR = obj/client

BINDIR = bin
HEADERDIR = src/include

# Compiler settings
CC = gcc
CXXFLAGS = -std=c99 -Wall
LDFLAGS = -I$(HEADERDIR)

SRC 	  = $(wildcard $(SRCDIR)/*$(EXT))
SERVERSRC = $(wildcard $(SERVERSRCDIR)/*$(EXT))
CLIENTSRC = $(wildcard $(CLIENTSRCDIR)/*$(EXT))

SOBJ 	  = $(SRC:$(SRCDIR)/%$(EXT)=$(SERVEROBJDIR)/%.o)
COBJ 	  = $(SRC:$(SRCDIR)/%$(EXT)=$(CLIENTOBJDIR)/%.o)
SERVEROBJ = $(SERVERSRC:$(SERVERSRCDIR)/%$(EXT)=$(SERVEROBJDIR)/%.o)
CLIENTOBJ = $(CLIENTSRC:$(CLIENTSRCDIR)/%$(EXT)=$(CLIENTOBJDIR)/%.o)

RM = rm -r
########################################################################
####################### Targets beginning here #########################
########################################################################
server: $(BINDIR)/$(SERVER)
$(BINDIR)/$(SERVER): $(SERVEROBJ) $(SOBJ)
	$(CC) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
$(SERVEROBJDIR)/%.o: src/server/*.c src/*.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

client: $(BINDIR)/$(CLIENT)
$(BINDIR)/$(CLIENT): $(CLIENTOBJ) $(COBJ)
	$(CC) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
$(CLIENTOBJDIR)/%.o: src/client/*.c src/*.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) ./obj/server/* ./obj/client/* ./bin/*

.PHONY: dir
dir:
	mkdir -p $(SRCDIR)/include $(SERVEROBJDIR) $(CLIENTOBJDIR) $(BINDIR)

.PHONY: rdir
rdir:
	rm -rf $(OBJDIR) $(BINDIR)