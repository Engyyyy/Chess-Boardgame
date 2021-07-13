/***********************The following are functions definitions for chess pieces*************************************/
/*
parameters of these functions:
x1: the row number of the first square.
y1: the column number of the first square.
x2: the row number of the second square.
y2: the column number of the second square.
turn: a flag indicates which player is moving. It can either be 0 or 1.
Return of these functions:
0: If the movement is illegal.
1: If the movement is legal.
*/
//This function checks if the movement is valid for a bishop.
//A bishop moves diagonally and can't jump over pieces.
int bishop(int x1, int y1, int x2, int y2, int turn){
    if((abs(x1 - x2) == abs(y1 - y2)) && x1 != x2){ //if the move is diagonal
        //each loop checks that there are no pieces between the first and the second squares.
        if(x1 > x2 && y1 > y2){
            for(int i = x1-1, j = y1-1; i > x2 && j > y2; j--, i--){
                if(board[i][j] != '.' && board[i][j] != '-') return 0;
            }
        }
        else if(x1 > x2 && y1 < y2){
            for(int i = x1-1, j = y1+1; i > x2 && j < y2; i--, j++){
                if(board[i][j] != '.' && board[i][j] != '-') return 0;
            }
        }
        else if(x1 < x2 && y1 > y2){
            for(int i = x1+1, j = y1-1; i < x2 && j > y2; i++, j--){
                if(board[i][j] != '.' && board[i][j] != '-') return 0;
            }
        }
        else{
            for(int i = x1+1, j = y1+1; i < x2 && j < y2; i++, j++){
                if(board[i][j] != '.' && board[i][j] != '-') return 0;
            }
        }
        if(turn == 0){
            if(board[x2][y2] > 'a' && board[x2][y2] < 'z') return 0;
        }
        else{
            if(board[x2][y2] > 'A' && board[x2][y2] < 'Z') return 0;
        }
        return 1; //A legal move
    }
    else return 0; //An illegal move.
}
//This function checks if the movement is valid for a king.
int king(int x1, int y1, int x2, int y2, int turn){
    if(x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) return 0; //If one of the squares is out of the board.
    //If the movement is diagonally, forward, backward, left or right.
    if((abs(x1 - x2) == 1 && y1 == y2) || (abs(y1 - y2) == 1 && x1 == x2) || (abs(x1 - x2) == 1 && abs(y1 - y2) == 1)){
        if(turn == 0){ //if the moving player is player 1.
            //If the second square contains a white piece, it is an illegal movement.
            if(board[x2][y2] > 'a' && board[x2][y2] < 'z') return 0;
        }
        else{ //If the moving player is player 2.
            //If the second square contains a black piece, it is an illegal movement.
            if(board[x2][y2] > 'A' && board[x2][y2] < 'Z') return 0;
        }
        //It is a valid movement.
        return 1;
    }
    //Else it is an illegal movement.
    else return 0;
}
//This function checks if the movement is valid for a knight.
//A knight moves in L shape and can jump over pieces.
int knight(int x1, int y1, int x2, int y2, int turn){
    if((abs(y2-y1)==2&&abs(x2-x1)==1)||(abs(y2-y1)==1&&abs(x2-x1)==2)){ //if the move is in L shape.
        if(turn == 0){
            if(board[x2][y2] > 'a' && board[x2][y2] < 'z') return 0;
        }
        else{
           if(board[x2][y2] > 'A' && board[x2][y2] < 'Z') return 0;
        }
        return 1; //A legal move.
    }
    else return 0; //An illegal move.
}
//This function checks if the movement is valid for a pawn.
int pawn(int x1, int y1, int x2, int y2, int turn){
    char x, z;
    if(turn == 0){ //If the moving player is player 1.
        if((x2 == x1 - 1) && (y2 == y1 - 1 || y2 == y1 + 1)){ //if the movement is one square diagonally
            //If the second square is empty or contains a white piece, it is an illegal movement.
            if(board[x2][y2] == '.' || board[x2][y2] == '-') return 0;
            else if(board[x2][y2] > 'a' && board[x2][y2] < 'z') return 0;
        }
        else{
            if(y1 != y2) return 0; //If the y-position is varying, it is an illegal movement.
            //If the second square is not empty, it is an illegal movement.
            if(board[x2][y2] != '.' && board[x2][y2] != '-') return 0;
            //If the pawn moves one square forward, it is a legal movement.
            if(x1 - x2 == 1) return 1;
            //If the pawn moves two squares forward and the first square forward is empty, it is a legal movement.
            if(x1 == 6 && x1 - x2 == 2 && (board[x1-1][y1] == '.' || board[x1-1][y1] == '-')) return 1;
            return 0; //Else it is an illegal movement.
        }
    }
    else if(turn == 1){ //If the moving player is player 2.
        //If the square moves one square diagonally
        if((x2 == x1 + 1 && y2 == y1 - 1) || (x2 == x1 + 1 && y2 == y1 + 1)){
            //If the second square is empty or contains a black piece, it is an illegal movement.
            if(board[x2][y2] == '.' || board[x2][y2] == '-') return 0;
            else if(board[x2][y2] > 'A' && board[x2][y2] < 'Z') return 0;
        }
        else{
            if(y1 != y2) return 0; //If the y-position is varying, it is an illegal movement.
            //If the second square is no empty, it is an illegal movement.
            if(board[x2][y2] != '.' && board[x2][y2] != '-') return 0;
            //If the pawn moves one square forward, it is a legal movement.
            if(x2 - x1 == 1) return 1;
            //If the pawn moves two squares forward and the first square forward is empty, it is a legal movement.
            if(x1 == 1 && x2 - x1 == 2 && (board[x1+1][y1] == '.' || board[x1+1][y1] == '-')) return 1;
            return 0; //Else it is an illegal movement.
        }
    }

    return 1; //Else it is a legal movement.
}
//This function checks if the movement is valid for a rook.
int rook(int x1, int y1, int x2, int y2, int turn){
    //If both the x-position and the y-position are varying or constant, it is an illegal movement.
    if((x1 != x2 && y1 != y2) || (x1 == x2 && y1 == y2)) return 0;
    //If the second square contains a white piece and the moving player is player 1.
    //OR if the second square contains a black piece and the moving player is player 2.
    //This movement is illegal.
    if((board[x2][y2] > 'a' && board[x2][y2] < 'z' && turn == 0) || (board[x2][y2] > 'A' && board[x2][y2] < 'Z' && turn == 1))
       return 0;
    //If the rook moves vertically
    if(x1 == x2){
        int a, b;
        if(y1 < y2){
            a = y1;
            b = y2;
        }
        else{
            a = y2;
            b = y1;
        }
        //This loop checks if all the squares between the first square and the second square are empty.
        for(int i = a+1; i < b; i++){
            if(board[x1][i] != '.' && board[x1][i] != '-'){
                return 0; //If one square is not empty, it is an illegal movement.
            }
        }
    }
    else{ //If the rook moves horizontally
        int a, b;
        if(x1 < x2){
            a = x1;
            b = x2;
        }
        else{
            a = x2;
            b = x1;
        }
        //This loop checks if all the squares between the first and the second square are empty.
        for(int i = a+1; i < b; i++){
            //If one square is not empty, it is an illegal movement.
            if(board[i][y1] != '.' && board[i][y1] != '-') return 0;
        }
    }
    return 1; //else it is a legal movement.
}
//This function checks if the movement is valid for a queen.
//A queen can move like a rook and a bishop, so we call both functions.
int queen(int x1, int y1, int x2, int y2, int turn){
    if(x1 == x2 || y1 == y2){ //If it is a rook movement.
        return rook(x1, y1, x2, y2, turn);
   }
    else if(abs(x2 - x1) == abs(y2 - y1)){ //if it is a bishop movement.
        return bishop(x1, y1, x2, y2, turn);
   }
   else return 0;
}
