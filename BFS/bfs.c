//Khai báo các thư viện
#include<stdio.h>
#include<stdbool.h>
//Định nghĩa các macro cho các hằng số
#define MAX_ROW 9 //số hàng
#define MAX_COLUMN 9 //số cột
#define MAX 100 //số nút tối đa thêm vào hàng đợi

//1.
//Khai báo các thành phần
//khai báo cấu trúc POINT cho một nút trong ma trận
typedef struct POINT {
  int row; //tọa độ x
  int column; //tọa độ y
  int value; //giá trị 0 hoặc 1 của nút
  bool visited; //đánh dấu nút đã được đi qua
  struct POINT *prev; //con trỏ trỏ đến nút liền trước đó trước khi đến nút hiện tại
} point_t;
//khai báo kiểu cấu trúc Queue để lưu các nút sẽ đươc xử lý
typedef struct QUEUE {
  point_t data[MAX]; //mảng chứa các nút
  int front; //chỉ số đầu của hàng đợi
  int rear; //chỉ số cuối của hàng đợi
} Queue;
//khai báo mảng hai chiều chứa các tọa độ
point_t matrix[MAX_ROW][MAX_COLUMN];

//Viết hàm: khởi tạo hàng đợi
void initQueue(Queue *q) {
  q->front = 0;
  q->rear = -1;
  return;
}

//Viết hàm: kiểm tra hàng đợi có rỗng không
int isEmpty(Queue q) {
  return(q.rear < q.front); //nếu chỉ số đầu hàng lớn hơn chỉ số cuối
}

//Viết hàm: kiểm tra hàng đợi đã đầy chưa còn chỗ trống không
int isFull(Queue q) {
  if(q.rear - q.front == MAX -1) {
    return 1;
  } else {
    return 0;
  }
}

//Viết hàm: thêm phần tử vào (rear) cuối của hàng đợi
void enQueue(Queue *q, point_t x) {
  //kiểm tra hàng đầy chưa nếu chưa đầy thực hiện tiếp 
  if(!isFull(*q)) {
    //nếu chỉ số cuối đang ở cuối mảng
    if(q->rear == MAX - 1) {
      //dịch phần tử về đầu mảng
      for(int i = q->front; i <= q->rear; i++) {
        q->data[i - q->front] = q->data[i];
      }
      //cập nhật lại chỉ số đầu và cuối
      q->rear = MAX - q->front - 1;
      q->front = 0;
    }
    //thêm phần tử vào sau chỉ số cuối
    q->rear = q->rear + 1;
    q->data[q->rear] = x;
  }
  return;
}

//Viết hàm: lấy phần tử (front) ra khỏi hàng đợi
point_t deQueue(Queue *q) {
  point_t d;
  //kiểm tra hàng có rỗng không nếu không rỗng thì thực hiện tiếp
  if(!isEmpty(*q)) {
    //lấy phần tử đầu
    d = q->data[q->front];
    //dịch chỉ số đầu ra sau
    q->front = q->front + 1;
  }
  //nếu sau khi lấy phần tử hàng đợi rỗng thì khởi tạo tại
  if(q->front > q->rear) {
    initQueue(q);
  }
  return d;
}

//2.
//Viết hàm: kiểm tra tọa độ có nằm trong ma trận đã khai báo không
bool checkCoordinate(int row, int column) {
  //khởi tạo biến kiểm tra ban đầu là false
  bool check = false;
  //nếu điểm có tọa độ trong khoảng 0 đến 8
  if((0 <= row && row < MAX_ROW) && (0 <= column && column < MAX_COLUMN)) {
    check = true;
  }
  return check;
}

//Viết hàm: tìm các điểm xung quanh của điểm xuất phát mà có giá trị là 1
void findSurroundingPoint(int row, int column, point_t *surroundingPnt[4], int *count){
  //khởi tạo biến đếm số các nút có thể đi được quanh một vị trí
  int tempCnt = 0;
  //kiểm tra nút bên phải có đi được không
  if((checkCoordinate(row, column + 1) == true) && (matrix[row][column + 1].value == 1)) {
    //thêm nút vào mảng
    surroundingPnt[tempCnt] = &matrix[row][column + 1];
    tempCnt++;
  }
  //kiểm tra nút bên dưới có đi được không
  if((checkCoordinate(row + 1, column) == true) && (matrix[row + 1][column].value == 1)) {
    //thêm nút vào mảng
    surroundingPnt[tempCnt] = &matrix[row + 1][column];
    tempCnt++;
  }
  //kiểm tra nút bên trái có đi được không
  if((checkCoordinate(row, column - 1) == true) && (matrix[row][column - 1].value == 1)) {
    //thêm nút vào mảng
    surroundingPnt[tempCnt] = &matrix[row][column - 1];
    tempCnt++;
  }
  //kiểm tra nút bên trên có đi được không
  if((checkCoordinate(row - 1, column) == true) && (matrix[row - 1][column].value == 1)) {
    //thêm nút vào mảng
    surroundingPnt[tempCnt] = &matrix[row - 1][column];
    tempCnt++;
  }
  *count = tempCnt;
}

//Viết hàm: hiển thị các điểm đi từ O(0,0) đến A(row,column)
int findPath(int row, int column, point_t path[MAX]) {
  int length_OA = 0; //số điểm trên đường từ O đến A
  int length_bfs = 0; //số điểm được bfs xét 
  point_t bfs[MAX]; //mảng lưu các điểm đượcc xét trên đường đi O đến A
  //cài lại visited và con trỏ prev
  for(int i = 0; i < MAX_ROW; i++) {
    for(int j = 0; j < MAX_COLUMN; j++) {
      matrix[i][j].visited = false;
      matrix[i][j].prev = NULL;
    }
  }
  //khai báo một hàng đợi
  Queue queue;
  //khởi tạo hàng đợi
  initQueue(&queue);
  //đánh dấu tọa độ (0,0) là đã đi qua
  matrix[0][0].visited = true;
  bfs[0] = matrix[0][0];
  ++length_bfs;
  //cho nút có tọa độ (0,0) vào hàng đợi 
  enQueue(&queue, matrix[0][0]);
  //khởi tạo biến tìm thấy A
  bool found = false;
  //nếu hàng đợi không rỗng và chưa tìm thấy nút A
  while((isEmpty(queue) == false) && (found == false)) {
    //lấy nút p đầu tiên của hàng đợi
    point_t p = deQueue(&queue);
    //tìm các nút xung quanh nút p vừa lấy ra 
    point_t *pp[4];
    int count;
    findSurroundingPoint(p.row, p.column, pp, &count);
    //duyệt qua từng nút 
    for(int i = 0 ; i < count; i++) {
      //nếu nút đó chưa được đi qua
      if(!pp[i]->visited) {
        //đánh dấu nút đó là đã đi qua
        pp[i]->visited = true;
        //ghi nhận nút trước đó là p
        pp[i]->prev = &matrix[p.row][p.column];
        //đưa vào mảng path
        bfs[length_bfs] = *pp[i];
        ++length_bfs;
        //nếu đây là nút A thì thoát vòng lặp
        if(pp[i]->row == row && pp[i]->column == column){
          found = true;
          break;
        } else{ //nếu không phải nút A thì cho vào hàng đợi
          enQueue(&queue, *pp[i]);
        }
      }
    }
  }
  //nếu tìm đến nút A thì in ra các nút đã đi qua từ O(0,0) đến A
  if(found == true) {
    //tìm các điểm trên đường đi từ A về O
    point_t *p = &bfs[length_bfs - 1]; //p trỏ đến điểm A
    int i = 0; 
    while(p != NULL) {
      path[i] = *p; //lưu điểm từ A về O
      p = p->prev; //trỏ đến trước điểm A
      i++;
      length_OA++;
    }
    //in ra các điểm đó
    printf("Duong di tu O(0,0) den A(%d,%d) co do dai la %d o:\n", row, column, length_OA);
    for(int i = (length_OA - 1); i>=0; i--) {
      printf("(%d,%d)", path[i].row, path[i].column);
      if(i >= 0) {
        printf(", ");
      }
    }
  }
  return length_OA;
}

//3.Yêu cầu nâng cao
//Viết hàm: tìm đường đi ngắn nhất từ điểm O(0,0) đến điểm A(row,column)
int findShortestPath(int row, int column) {
  //cài lại visited và con trỏ prev
  for(int i = 0; i < MAX_ROW; i++) {
    for(int j = 0; j < MAX_COLUMN; j++) {
      matrix[i][j].visited = false;
      matrix[i][j].prev = NULL;
    }
  }
  //khai báo một hàng đợi
  Queue queue;
  //khởi tạo hàng đợi
  initQueue(&queue);
  //đánh dấu tọa độ (0,0) là đã đi qua
  matrix[0][0].visited = true;
  //cho nút có tọa độ (0,0) vào hàng đợi 
  enQueue(&queue, matrix[0][0]);
  //khởi tạo biến tìm thấy A
  bool found = false;
  //nếu hàng đợi không rỗng và chưa tìm thấy nút A
  while((isEmpty(queue) == false) && (found == false)) {
    //lấy nút p đầu tiên của hàng đợi
    point_t p = deQueue(&queue);
    //tìm các nút xung quanh nút p vừa lấy ra 
    point_t *pp[4];
    int count;
    findSurroundingPoint(p.row, p.column, pp, &count);
    //duyệt qua từng nút 
    for(int i = 0 ; i < count; i++) {
      //nếu nút đó chưa được đi qua
      if(!pp[i]->visited) {
        //đánh dấu nút đó là đã đi qua
        pp[i]->visited = true;
        //ghi nhận nút trước đó là p
        pp[i]->prev = &matrix[p.row][p.column];
        //nếu đây là nút A thì thoát vòng lặp
        if(pp[i]->row == row && pp[i]->column == column){
          found = true;
          break;
        } else{ //nếu không phải nút A thì cho vào hàng đợi
          enQueue(&queue, *pp[i]);
        }
      }
    }
  }
  //nếu tìm đến nút A thì in ra các nút trên đường đi ngắn nhất từ O đến A
    if(found) {
      point_t *shortestPath[100];
      int length = 0;
      //bắt đầu từ A
      point_t *target = &matrix[row][column];
      //theo prev về O
      while(target != NULL) {
        shortestPath[length] = target;
        target = target->prev;
        ++length;
      }
      printf("\n\nDuong di ngan nhat tu O(0,0) den A(%d,%d) có do dai la %d o:\n", row, column, length);
      for(int i = length - 1; i >= 0; i--) {
        printf("(%d,%d)", shortestPath[i]->row, shortestPath[i]->column);
        if(i > 0) {
          printf(" -> ");
        } else {
          printf("\n\n");
        }
      }
      return length;
    } else {
    printf("Khong co duong di tu O(0,0) den A\n\n");
    return 0;
  }
}

//Hàm main
int main() {
  printf("CHUONG TRINH TIM DUONG DI NGAN NHAT TU O(0,0) DEN A(dong, cot)\n\n");
  //in ra ma trận
  printf("Ma tran 9x9 bieu dien cho mat phang 2 chieu:\n");
  int value[9][9] = {
    {1,0,0,0,1,0,1,1,0},
    {1,1,0,1,1,1,0,0,1},
    {0,1,0,1,1,0,1,0,1},
    {0,1,1,0,0,1,0,1,1},
    {0,0,1,0,1,0,1,0,0},
    {1,1,1,0,0,0,0,1,1},
    {1,0,1,1,1,1,1,0,0},
    {1,1,1,0,0,0,1,0,1},
    {0,0,0,1,1,1,1,1,0}
  };
  for(int i = 0; i < MAX_ROW; i++) {
    for(int j = 0; j < MAX_COLUMN; j++) {
      matrix[i][j].row = i;
      matrix[i][j].column = j;
      matrix[i][j].visited = false;
      matrix[i][j].prev = NULL;
      matrix[i][j].value = value[i][j];
      printf("%d ", matrix[i][j].value);
    }
    printf("\n");
  }
  printf("\nToa do cua o xuat phat là O(0,0).\n\n");
  //nhập ô đích đến
  int row;
  int column;
  while(1){
    printf("Hay nhap vao toa do cua o dich den A:\n");
    printf("Nhap dong: ");
    scanf("%d", &row);
    printf("Nhap cot: ");
    scanf("%d", &column);
    printf("\n");
    if(!checkCoordinate(row, column)) {
      printf("Gia tri cua dong phai tu 0 den 8!\n");
      printf("Gia tri cua cot  phai tu 0 den 8!\n\n");
    } else {
      break;
    }
  }
  //
  point_t path[100];
  findPath(row, column, path);
  //hiển thị số lượng và các ô thành đường đi ngắn nhất đến A
  findShortestPath(row, column);
  return 0;
}