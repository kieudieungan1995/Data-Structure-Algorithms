Breadth-First Search (BFS) algorithm is used to find path from origin to point A in Coordinate plane. It explores points level by level based on their distance from origin. Since all moves have the same distance so path from origin to A is also as the shortest path. 

What BFS does are: 

* Start from origin, mark it as visited & put it into queue
* Dequeue a point & find its reachable neighboring points. This generates next level
* For each unvisited neighboring point mark as visited and set its relationship with current point
* Enqueue unvisited neighboring points and continue to processing the next level until point A is founded
* When A found, follow from A to origin to construct the path

Illustration of levels in BFS 

```
Level 0: (0,0)
Level 1: (0,1) ; (1,0)
Level 2: (1,1) ; (0,2) ; (2,0)
Level 3: (2,1) ; (1,2) ; (0,3) ; (3,0)
..
Level n: (x,y)
```
