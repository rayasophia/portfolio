# Main Author: Raya Sophia Casas

# Import necessary functions
from a1_partc import Queue
from a1_partd import get_overflow_list, overflow

# This function duplicates and returns the board. You may find this useful
def copy_board(board):
        """
        Creates a deep copy of the board.
        Parameters:
            board (list of lists): A 2D list representing the game board.
        Returns:
            list of lists: A new 2D list that is an independent copy of the input board.
        """
        current_board = []
        height = len(board)
        for i in range(height):
            current_board.append(board[i].copy())
        return current_board

# This function is your evaluation function for the board
def evaluate_board(board, player):
    """
    Evaluates the current game board and returns a score for the specified player.
    Parameters:
        board (list of lists): A 2D list representing the game board.
        player (int): The player for whom the board is evaluated. 1 for Player 1 and -1 for Player 2.

    Returns:
        int: A score representing the game state:
         - 100 if the player wins,
         - -100 if the player loses,
         - 0 for a draw,
         - A percentage score based on the player's gem value contribution to the total gems otherwise.
    """
    winPoint = 100
    losePoint = -100
    drawPoint = 0
    value = 0
    total = 0
    gem = 0

    # Check each cell in the board for points
    for row in board:
        for cell in row:
            if cell != 0:
                if cell < 0:
                    value = -cell
                else:
                    value = cell
                total += value
                if player == 1 and cell > 0:
                    gem += value
                if player == -1 and cell < 0:
                    gem += value
    
    # Return corresponding scores
    if gem == total:
        return winPoint
    if gem == 0:
        return losePoint
    if total == 0:
        return drawPoint

    # Calculate and return the percentage score
    score = (gem * 100) // total
    
    return score

# GameTree Class
class GameTree:
    """
    A class to represent the game tree for a two-player game. 
    The tree is used to evaluate moves using the minimax algorithm.
    """
    # Node class within GameTree
    class Node:
        """
        A class representing a single node in the game tree.

        Attributes:
            board (list of lists): The game board at this node.
            depth (int): The depth of this node in the game tree.
            player (int): The player who made the move leading to this node.
            children (list): A list of child nodes representing possible moves.
            score (int): The score of the node, computed during the minimax process.
            move: The move (row, column) that led to this node.
        """
        def __init__(self, board, depth, player, tree_height = 4):
            # Node of the board after a move is done
            self.board = board
            # Depth to determine whether it is min or max
            self.depth = depth
            # Player who played the node
            self.player = player
            # Array for the possible outcomes of the opponent's play
            self.children = []
            # Stores the min or max of the children
            self.score = None
            # Move of the player at the node
            self.move = None

    def __init__(self, board, player, tree_height = 4):
        """
        Initializes the game tree with the specified root board and player.

        Parameters:
            board (list of lists): The initial game board.
            player (int): The player who is making the first move (1 or -1).
            tree_height (int): The maximum depth of the game tree. Default is 4.
        """
        self.player = player
        self.board = copy_board(board)
        # you will need to implement the creation of the game tree here.  After this function completes,
        # a full game tree will be created.
        # hint: as with many tree structures, you will need to define a self.root that points to the root
        # of the game tree.  To create the tree itself, a recursive function will likely be the easiest as you will
        # need to apply the minimax algorithm to its creation.

        # Create the board at the root with depth of 0 and the player will start
        self.root = GameTree.Node(board, 0, player)
        # Define the height of the tree
        self.tree_height = tree_height
        # Build tree based on height and given root node
        self.build_tree(self.root, tree_height)

    # This function builds the GameTree at a given height
    def build_tree(self, node, height):
        """
        Recursively builds the game tree up to a specified height.

        Parameters:
            node (Node): The current node from which to expand the tree.
            height (int): The remaining height to build.
        """
        # No need to build if the height is already reached
        if height == 0:
            return
        
        # Traverses through the board and finds the playable moves
        for i in range(len(node.board)):
            for j in range(len(node.board[0])):
                # Find playable branches
                if node.board[i][j] == 0 or node.board[i][j] * node.player > 0:
                    new_board = copy_board(node.board)
                    new_board[i][j] += node.player

                    # Perform overflow if needed
                    if get_overflow_list(new_board):
                            a_queue = Queue()
                            a_queue.enqueue(new_board)
                            overflow(new_board, a_queue)
                            new_board = a_queue.dequeue()
                    
                    # Node for the opposing player's plays
                    child_node = GameTree.Node(new_board, node.depth + 1, -node.player)
                    # Assign the move to each child from the move
                    child_node.move = (i, j)
                    node.children.append(child_node)
                    # Build subtree with child node
                    self.build_tree(child_node, height - 1)

    # This function returns the best or worst score in the children nodes depending on who is making the move
    def minimax(self, node):
        """
        Implements the minimax algorithm to evaluate the game tree.

        Parameters:
            node (Node): The current node to evaluate.

        Returns:
            int: The best score for the current node, depending on whether it is a maximizing or minimizing player's turn.
        """
        if not node.children:
            # Calculate the score
            node.score = evaluate_board(node.board, node.player)
            return node.score
        
        # Maximizer for the player who starts at depth 0 and makes moves for the even levels (0, 2, 4)
        if node.depth % 2 == 0:  
            # Find the maximum score
            node.score = max(self.minimax(child) for child in node.children)
            return node.score
        
        # Minimizer for the player who starts at depth 1 and makes moves for the odd levels (1, 3)
        else:  
            # Find the minimum score
            node.score = min(self.minimax(child) for child in node.children)
            return node.score

    # Returns the best move for the player
    def get_move(self):
        """
        Finds and returns the best move for the current player.

        Returns:
            best_move: The (row, column) of the best move.
        """
        best_score = float('-inf')
        best_move = None
        # Search and find the best move
        for child in self.root.children:
            score = self.minimax(child)
            if score > best_score:
                best_score = score
                best_move = child.move
        return best_move
   
    def clear_tree(self):
        """
        Clears the game tree by deleting all nodes.
        """
        self.delete_nodes(self.root)     

    # Helper function to delete nodes starting at the given node as the root
    def delete_nodes(self, node):
        """
        Helper function to delete nodes starting from a given node.

        Parameters:
            node (Node): The root node to delete.
        """
        if not node:
            return
        for child in node.children:
            self.delete_nodes(child)
        del node
    
