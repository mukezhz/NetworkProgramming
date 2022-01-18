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

OBJ 	  = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
SERVEROBJ = $(SERVERSRC:$(SERVERSRCDIR)/%$(EXT)=$(SERVEROBJDIR)/%.o)
CLIENTOBJ = $(CLIENTSRC:$(CLIENTSRCDIR)/%$(EXT)=$(CLIENTOBJDIR)/%.o)

RM = rm -r
########################################################################
####################### Targets beginning here #########################
########################################################################
server: $(BINDIR)/$(SERVER)
$(BINDIR)/$(SERVER): $(SERVEROBJ) $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
$(SERVEROBJDIR)/%.o: $(SERVERSRCDIR)/*.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/*.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

client: $(BINDIR)/$(CLIENT)
$(BINDIR)/$(CLIENT): $(CLIENTOBJ) $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
$(CLIENTOBJDIR)/%.o: $(CLIENTSRCDIR)/*.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/*.c
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