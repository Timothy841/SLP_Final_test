#include "networking.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  int player = 2;
  char board[6][7];//create board
  clear_board(board);//clear it
  print_board(board);//print clean board
  while (1) {
  	if (player == 1){
  		read(server_socket, buffer, sizeof(buffer));//read opponent move
  		int move = convert_int(buffer);//convert to int
  		place_piece(board, player, move);//place piece
  		print_board(board);
  		player = 2;
  	}
  	else{
  		int move = get_int(buffer, player);//get input to write
  		int fail = place_piece(board, player, move-1);//see if move fails
  		if (fail){
  			continue;//start over, new move
  		}
  		print_board(board);
    		write(server_socket, buffer, sizeof(buffer));//give input to opponent
  		player = 1;
  	}
  
  
  
  
  /*
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);*/
  }
}
