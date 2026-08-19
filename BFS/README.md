Breadth-First Search (BFS) algorithm is used to find path from origin to point A in Coordinate plane. It explores points level by level based on their distance from origin. Since all moves have the same distance so path from origin to A is also as the shortest path.

What BFS does are:

- Start from origin, mark it as visited & put it into queue
- Dequeue a point & find its reachable neighboring points. This generates next level
- For each unvisited neighboring point mark as visited and set its relationship with current point
- Enqueue unvisited neighboring points and continue to processing the next level until point A is founded
- When A found, follow from A to origin to construct the path

Illustration of levels in BFS

```
Level 0: (0,0)
Level 1: (0,1) ; (1,0)
Level 2: (1,1) ; (0,2) ; (2,0)
Level 3: (2,1) ; (1,2) ; (0,3) ; (3,0)
..
Level n: (x,y)
```

##Input

Program receives coordinate of destination point.
Example:
Starting point: (0,0).
Destination point is created from user: (6,6).

##Output

Program displays the path from starting point to destination point.
Example:
Duong di tu O(0,0) den A(6,6) co do dai la 13 o:
(0,0), (1,0), (1,1), (2,1), (3,1), (3,2), (4,2), (5,2), (6,2), (6,3), (6,4), (6,5), (6,6),
Duong di ngan nhat tu O(0,0) den A(6,6) có do dai la 13 o:
(0,0) -> (1,0) -> (1,1) -> (2,1) -> (3,1) -> (3,2) -> (4,2) -> (5,2) -> (6,2) -> (6,3) -> (6,4) -> (6,5) -> (6,6)
