CC = gcc
CFLAGS = -Wall -g -I. -I./metodos -I./metodos/Quicksort
BIN = ./bin
OBJ = $(BIN)/obj
METODOS = ./metodos
QUICKSORT = $(METODOS)/Quicksort
INPUT = ./input
EXEC = exe

# Object files
OBJS = $(OBJ)/main.o \
       $(OBJ)/quickSort.o \
       $(OBJ)/fMaisUm.o \
       $(OBJ)/doisF.o \
       $(OBJ)/validacaoEntrada.o \
	   $(OBJ)/area.o \
	   $(OBJ)/funcoesRegistro.o \
	   $(OBJ)/funcoesOrdenacao.o 
	  
# Main target
all: $(EXEC)

# Create directories
$(BIN) $(OBJ):
	mkdir -p $@

# Linking
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilation
$(OBJ)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/validacaoEntrada.o: $(INPUT)/validacaoEntrada.c $(INPUT)/validacaoEntrada.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/funcoesRegistro.o: funcoesRegistro.c funcoesRegistro.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/funcoesOrdenacao.o: funcoesOrdenacao.c funcoesOrdenacao.h
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ)/quickSort.o: $(QUICKSORT)/quickSort.c $(QUICKSORT)/quickSort.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/area.o: $(QUICKSORT)/area.c $(QUICKSORT)/area.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/fMaisUm.o: $(METODOS)/fMaisUm.c $(METODOS)/fMaisUm.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/doisF.o: $(METODOS)/doisF.c $(METODOS)/doisF.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean targets
clean:
	rm -f $(OBJS)

clean-all: clean
	rm -f $(EXEC)

# Make sure the binary directory exists before compiling
$(OBJS): | $(OBJ)
