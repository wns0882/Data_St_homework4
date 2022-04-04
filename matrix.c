#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //����� ����� �Լ�
void print_matrix(int** matrix, int row, int col);//����� ����ϴ� �Լ�
int free_matrix(int** matrix, int row, int col);//����� �����Ҵ��� ����
int fill_data(int** matrix, int row, int col);//��Ŀ� 1~19 ������ ä��� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);//����� ���� ���ϴ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//����� ���� ���ϴ� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);//��ġ����� ���ϴ� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);//����� ���� ���ϴ� �Լ�

int main()
{

    char command; //char ���� ����
    printf("[----- [���ؿ�]  [2019038010] -----]\n");//�̸��� �й��� ���

    int row, col; // ��,�� ���� ����
    srand(time(NULL));//srand�Լ��� ����ϸ� ���� ������ �׻� �ٸ� ���� �����Ѵ�

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);//��� ���� �Է�
    int** matrix_a = create_matrix(row, col);//��� a�� �����Ҵ�
    int** matrix_b = create_matrix(row, col);//��� b�� �����Ҵ�
    int** matrix_a_t = create_matrix(col, row);//��� a_t�� �����Ҵ�

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //���a,b�� ���� �������� ������ ����

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
        scanf(" %c", &command);//��Ŀ� ������ �ɼ��� �Է� �޴´�.

        switch(command) {
        case 'z': case 'Z': //z�� �Է� ���� �� ��� a,b�� 1~19�� ������ ä���
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P'://p�� �Է� ���� �� ��� a,b�� ���
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a�� �Է¹��� �� ��� a,b�� ���Ͽ� ����Ѵ�
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //s�� �Է¹��� �� ��� a,b�� ���� ����Ѵ�
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T'://t�� �Է¹��� �� ��� a�� ��ġ����� ����Ѵ�
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M'://m�� �Է¹��� �� ��� a,b�� ���� ����Ѵ�
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q'://q�� �Է¹��� �� ��� ����� �޸𸮸� �����Ѵ�
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);

            break;
        default: //case�� ���� ���� �Է¹޾��� ��� ���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');//q�� �ԷµǸ� ����

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)//��Ŀ� �����Ҵ��ϴ� �Լ�
{
    int **matrix = (int**)malloc(sizeof(int*)*row);//����� �����Ҵ��Ѵ�

    for(int i=0; i<row; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int)*col);  //matrix[i], row,col ũ���� ��Ŀ� �����Ҵ�
    }
    return matrix;
}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //����� ����Ѵ�
{
    for(int i=0; i<row; i++) //����� ��� ���� ����Ѵ�
    {
        for(int j=0;j<col;j++)
        {
            printf("%d\t",(matrix[i][j]));
        }
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)//��� �޸����� �Լ�
{
    for(int i=0;i<row;i++) //��� ��Ŀ� �׿� �޸� ������ ���ش�
    {
        free(*matrix);
    }
    free(matrix);
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //��Ŀ� ������ ä��� �Լ�
{
    for(int i=0; i<row; i++) //��Ŀ� ��� �׿� 1~19�� ������ ä���
    {
        for(int j=0;j<col;j++)
        {
           matrix[i][j] = rand()%20;
        }
        
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)//����� ���� ���ϴ� �Լ�
{
    int i = 0;
    int j = 0;
    int **matrix_sum = create_matrix(row,col); //matrix_sum�� �����Ҵ�
    for(i=0;i<row;i++)//��� a ,b�� ���� ���Ѵ�
    {
        for(j=0;j<col;j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    print_matrix(matrix_sum,i,j);//����� ���� ����Ѵ�
    free_matrix(matrix_sum,i,j);//����� �޸� �����Ѵ�
    return 1;
    
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//����� ���� ���ϴ� �Լ�
{
    int i,j = 0;
    int **matrix_sub = create_matrix(row,col);//matrix_sub�� �����Ҵ�
    for(i=0;i<row;i++)//��� a,b�� ���� ���Ѵ�
    {
        for(j=0;j<col;j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    print_matrix(matrix_sub,i,j);//����� ���� ���Ѵ�
    free_matrix(matrix_sub,i,j);//����� �޸� �����Ѵ�
    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)//��ġ����� ���ϴ� �Լ�
{
    
    for(int i=0;i<row;i++)//��� ���� �ٲ㼭 ��ġ����� �����
    {
        for(int j=0;j<col;j++)
        {
            matrix_t[i][j] = matrix[j][i];
        }
    }
    return 1;
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//����� ���� ���ϴ� �Լ�
{
    int i,j,k =0;
    int **matrix_axt = create_matrix(row,row); //��ġ��Ŀ� ���ؼ� �����Ҵ�
    for(i=0;i<row;i++)//matrix_axt�� �ʱ�ȭ �Ѵ�
    {
        for(j=0; j<row; j++)
        {
           matrix_axt[i][j] = 0;   
        }
    }
    for(i = 0;i<row;i++)//��Ŀ� �������� �����ϴ� �ݺ���
    {
        for(j =0;j<row;j++)
        {
          for(k=0;k<col;k++)
          {
              matrix_axt[i][j]  += (matrix_a[i][k] * matrix_t[k][j]);
          }
        }
    }
    print_matrix(matrix_axt,row,row);//����� ���� ����Ѵ�
    free_matrix(matrix_axt,row,row);//����� �޸� �����Ѵ�
    return 1;    
}