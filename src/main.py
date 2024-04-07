import requests
import chess
import argparse

from time import sleep

def get_user_side():
    parser = argparse.ArgumentParser(description="Play chess against an AI")
    parser.add_argument('--userSide', help="black/white (b/w)")

    side = parser.parse_args().userSide

    if (side == None):
        print("No user side provided, defualting to white")
        side = "white"
    else:
        side = side.lower()

    if (side != "black" and side != "white" and side != "b" and side != "w"):
        if (side != None):
            raise SystemExit("Please input a valid side for the user: black/white (b/w)")
        
    if (side == "b"):
        side = "black"
    elif (side == "w"):
        side = "white"
        
    return side

# currState : fen string for current board state
def get_ai_move_from_api(currState : str):
    url = "https://chess-stockfish-16-api.p.rapidapi.com/chess/api"

    payload = { "fen": currState }
    headers = {
    	"content-type": "application/x-www-form-urlencoded",
    	"X-RapidAPI-Key": "UR-API-KEY", # TODO don't commit api key lmfao
    	"X-RapidAPI-Host": "chess-stockfish-16-api.p.rapidapi.com"
    }

    response = requests.post(url, data=payload, headers=headers).json()
    print(response)
    print(type(response))
    bestMove = response["bestmove"]

    return bestMove

def get_ai_move(board : chess.Board):
    # TODO : need to contact chess api to get move
    currState = board.fen()
    return get_ai_move_from_api(currState)

def get_positions_from_move_str(moveStr):
    return (moveStr[0 : 2], moveStr[2 : 4])

def get_to_pos_from_move_str(moveStr):
    return moveStr[2 : 4]

def print_move_made(wasPlayer, moveStr):
    fromPos, toPos = get_positions_from_move_str(moveStr)

    if wasPlayer:
        print(f"User made move from: {fromPos} to {toPos}")
    else:
        print(f"AI made move from: {fromPos} to {toPos}")

def get_player_colour_from_str(colourStr):
    return chess.WHITE if colourStr == "white" else chess.BLACK

def moved_ai_piece(board, moveStr, aiSide: str):
    fromPos = get_positions_from_move_str(moveStr)[0]

    pieceAtPos = board.piece_at(chess.parse_square(fromPos))

    if (pieceAtPos == None):
        return False

    aiColour = get_player_colour_from_str(aiSide) 

    return pieceAtPos.color == aiColour

def do_user_move(board, aiSide):
    while True:
        moveStr = input("Input move in form: fromto, i.e b2b4: ")

        if (moved_ai_piece(board, moveStr, aiSide)):
            print("Tried to move AI piece, please only move your own pieces")
            sleep(0.5)
        else:
            try:
                board.push_san(moveStr)
                print_move_made(True, moveStr)
                break
            except chess.IllegalMoveError:
                print("Tried to do an illegal move, please try again")
                sleep(0.5)


def do_ai_move(board):
    moveStr = get_ai_move(board)
    board.push_san(moveStr)

    print_move_made(False, moveStr)

def print_who_won(board, aiSide: str):
    winner = board.outcome().winner
    aiColour = get_player_colour_from_str(aiSide)

    if (winner == None):
        print("Draw between AI and user!")
    elif (winner == aiColour):
        print("AI won, too bad ;(")
    else:
        print("User won!")

if __name__ == "__main__":
    userSide = get_user_side()
    userStarted = True if userSide == "white" else False
    aiSide = "black" if userSide == "white" else "white"
    board = chess.Board()

    print("Board initalised to starting position")
    print(f"Playing as {userSide} against the machine")

    if (userSide == "white"):
        print("User is white, make the first move")

    while True:
        if userStarted:
            do_user_move(board, aiSide)
            do_ai_move(board)
        else:
            do_ai_move(board)
            do_user_move(board, aiSide)

        if (board.is_game_over()):
            print_who_won()
            break