CC = gcc
CFLAGS = -o
FIC1 =
FIC2 =
SRC1 = sever.c
SRC2 = client.c
exe1 = sever
exe2 = client

$(exe1): $(SRC1)
	$(CC) $(SRC1) $(CFLAGS) $(exe1)

$(exe2): $(SRC2)
	$(CC) $(SRC2) $(CFLAGS) $(exe2)

start: $(exe1) $(exe2) $(FIC1)
	gnome-terminal -- ./$(exe1) $(FIC1)
	gnome-terminal -- ./$(exe2) $(FIC2)