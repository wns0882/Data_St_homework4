#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //행렬을 만드는 함수
void print_matrix(int** matrix, int row, int col);//행렬을 출력하는 함수
int free_matrix(int** matrix, int row, int col);//행렬의 동적할당을 해제
int fill_data(int** matrix, int row, int col);//행렬에 1~19 난수를 채우는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬의 합을 구하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬의 차를 구하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);//전치행렬을 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);//행렬의 곱을 구하는 함수

int main()
{

    char command; //char 변수 선언
    printf("[----- [박준용]  [2019038010] -----]\n");//이름과 학번을 출력

    int row, col; // 행,열 변수 선언
    srand(time(NULL));//srand함수를 사용하면 난수 생성시 항상 다른 수를 생성한다

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);//행과 열을 입력
    int** matrix_a = create_matrix(row, col);//행렬 a에 동적할당
    int** matrix_b = create_matrix(row, col);//행렬 b에 동적할당
    int** matrix_a_t = create_matrix(col, row);//행렬 a_t에 동적할당

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬a,b에 값이 존재하지 않으면 종료

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);//행렬에 수행할 옵션을 입력 받는다.

        switch(command) {
        case 'z': case 'Z': //z를 입력 받을 시 행렬 a,b를 1~19의 난수로 채운다
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P'://p를 입력 받을 시 행렬 a,b를 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a를 입력받을 시 행렬 a,b를 합하여 출력한다
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //s를 입력받을 시 행렬 a,b를 빼서 출력한다
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T'://t를 입력받을 시 행렬 a의 전치행렬을 출력한다
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M'://m을 입력받을 시 행렬 a,b의 곱을 출력한다
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q'://q를 입력받을 시 모든 행렬의 메모리를 해제한다
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);

            break;
        default: //case에 없는 값을 입력받았을 경우 출력
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');//q가 입력되면 종료

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)//행렬에 동적할당하는 함수
{
    int **matrix = (int**)malloc(sizeof(int*)*row);//행렬을 동적할당한다

    for(int i=0; i<row; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int)*col);  //matrix[i], row,col 크기의 행렬에 동적할당
    }
    return matrix;
}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //행렬을 출력한다
{
    for(int i=0; i<row; i++) //행렬의 모든 항을 출력한다
    {
        for(int j=0;j<col;j++)
        {
            printf("%d\t",(matrix[i][j]));
        }
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)//행렬 메모리해제 함수
{
    for(int i=0;i<row;i++) //모든 행렬에 항에 메모리 해제를 해준다
    {
        free(*matrix);
    }
    free(matrix);
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //행렬에 난수를 채우는 함수
{
    for(int i=0; i<row; i++) //행렬에 모든 항에 1~19의 난수를 채운다
    {
        for(int j=0;j<col;j++)
        {
           matrix[i][j] = rand()%20;
        }
        
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)//행렬의 합을 구하는 함수
{
    int i = 0;
    int j = 0;
    int **matrix_sum = create_matrix(row,col); //matrix_sum에 동적할당
    for(i=0;i<row;i++)//행렬 a ,b에 합을 구한다
    {
        for(j=0;j<col;j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    print_matrix(matrix_sum,i,j);//행렬의 합을 출력한다
    free_matrix(matrix_sum,i,j);//행렬을 메모리 해제한다
    return 1;
    
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//행렬의 차를 구하는 함수
{
    int i,j = 0;
    int **matrix_sub = create_matrix(row,col);//matrix_sub을 동적할당
    for(i=0;i<row;i++)//행렬 a,b의 차를 구한다
    {
        for(j=0;j<col;j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    print_matrix(matrix_sub,i,j);//행렬의 차를 구한다
    free_matrix(matrix_sub,i,j);//행렬을 메모리 해제한다
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)//전치행렬을 구하는 함수
{
    
    for(int i=0;i<row;i++)//행과 열을 바꿔서 전치행렬을 만든다
    {
        for(int j=0;j<col;j++)
        {
            matrix_t[i][j] = matrix[j][i];
        }
    }
    return 1;
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//행렬의 곱을 구하는 함수
{
    int i,j,k =0;
    int **matrix_axt = create_matrix(row,row); //전치행렬에 대해서 동적할당
    for(i=0;i<row;i++)//matrix_axt를 초기화 한다
    {
        for(j=0; j<row; j++)
        {
           matrix_axt[i][j] = 0;   
        }
    }
    for(i = 0;i<row;i++)//행렬에 곱연산을 실행하는 반복문
    {
        for(j =0;j<row;j++)
        {
          for(k=0;k<col;k++)
          {
              matrix_axt[i][j]  += (matrix_a[i][k] * matrix_t[k][j]);
          }
        }
    }
    print_matrix(matrix_axt,row,row);//행렬의 곱을 출력한다
    free_matrix(matrix_axt,row,row);//행렬을 메모리 해제한다
    return 1;    
}