[Arrow Slide Puzzle Game](https://www.crazygames.com/game/arrow-slide-puzzle)
(introduced to me by my friend Rishit Ojha)

This is a simple algorithm which solves this game, that is, it returns an order in which to release the arrows.

Construct a directed graph G = (V, E) where V = the arrows, and put an edge from arrow a to arrow b if arrow a blocks the path of arrow b (ie it comes somewhere infront of the head of arrow b).
If there is any solution (ie a valid release order), G must be acylic (hence a DAG). And if G is a DAG, any topological order is a valid release order.
