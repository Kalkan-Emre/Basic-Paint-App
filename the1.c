#include <stdio.h>
#define MAX 25
#define MIN 0

int coordinates[MAX][MAX];



int paint_contiguous(int x, int y, int initial_color, int painting_color, int base_x, int base_y)
{
    if(coordinates[y][x] != initial_color)
    {
        return 0;
    }
    else
    {
        int i,j;
        coordinates[y][x]= painting_color;


        /* Checks neighboring pixels */
        

        for(j=y-1;j<=y+1;j++)
        {
            for(i=x-1;i<=x+1;i++)
            {
                if ((i>=MIN && i<MAX) && (j>=MIN && j<MAX))
                {
                    if (coordinates[j][i]==initial_color)
                    {
                        if(!(j==y && i==x) || (!(j==base_y && i==base_x)))
                        {
                            paint_contiguous(i,j,initial_color,painting_color, x, y);
                        }
                    }
                    else continue;
                }
                else continue;
            }
        }
        return 1;
    }
}


void bucket_fill()
{
    int x,y;
    int color;
    int initial_x,initial_y;
    int initial_color;
    int i,j;

    scanf("%d %d",&y,&x);


    /* Selecting Color */

    if ((x>=MIN && x<MAX) && (y>=MIN && y<MAX))
    {
        color = coordinates[y][x];
    } 
    else
    {
        if(x>=MAX)
        {
            if(y<MIN)
            {
                color = 2;
            }
            else if (y<MAX)
            {
                color = 3;
            }
            else if (y>=MAX)
            {
                color = 4;
            }
        }
        else if (x<MAX && x>=MIN)
        {
            if(y<MIN)
            {
                color = 1;
            }
            else if (y>=MAX)
            {
                color = 5;
            }
        }
        else if (x<MIN)
        {
            if (y<MIN)
            {
                color = 0;
            }
            else if (y<MAX && y>=MIN)
            {
                color = 7;
            }
            else if (y>=MAX)
            {
                color = 6;
            }
        }
    }

    scanf("%i %i",&initial_y, &initial_x);

    initial_color = coordinates[initial_y][initial_x];
    if (initial_color != color)
    {
        paint_contiguous(initial_x, initial_y, initial_color, color ,initial_x, initial_y);
    }


    /* Printing result*/

    for(j=MIN;j<MAX;j++)   
    {
        for(i=MIN;i<MAX;i++)
        {
            printf("%i ",coordinates[j][i]);
        }
        printf("\n");
    }
}


void copy_paste()
{
    int copy_row_1, copy_col_1, copy_row_2, copy_col_2;
    int paste_row_1, paste_col_1, paste_row_2, paste_col_2;
    int i,j;
    int changed_pixels=0;

    scanf("%i %i %i %i",&copy_row_1, &copy_col_1, &copy_row_2, &copy_col_2);
    scanf("%i %i %i %i",&paste_row_1, &paste_col_1, &paste_row_2, &paste_col_2);

    if(copy_col_1>copy_col_2)
    {
        int t;
        t = copy_col_1;
        copy_col_1 = copy_col_2;
        copy_col_2 = t;
    }

    if(copy_row_1>copy_row_2)
    {
        int t;
        t = copy_row_1;
        copy_row_1 = copy_row_2;
        copy_row_2 = t;
    }



    if(paste_col_1>paste_col_2)
    {
        int t;
        t = paste_col_1;
        paste_col_1 = paste_col_2;
        paste_col_2 = t;
    }

    if(paste_row_1>paste_row_2)
    {
        int t;
        t = paste_row_1;
        paste_row_1 = paste_row_2;
        paste_row_2 = t;
    }



    for(i=copy_col_1;i<=copy_col_2;i++)
    {
        for(j=copy_row_1;j<=copy_row_2;j++)
        {
            int current_color;
            int current_pasting_x, current_pasting_y;

            current_color = coordinates[j][i];

            current_pasting_x = paste_col_1 + (i-copy_col_1);

            current_pasting_y = paste_row_1 + (j-copy_row_1);

            if(coordinates[current_pasting_y][current_pasting_x] != current_color)
            {
                changed_pixels++;
            }

            coordinates[current_pasting_y][current_pasting_x] = current_color;

        }
    }

    /* Printing result*/

    for(j=MIN;j<MAX;j++)   
    {
        for(i=MIN;i<MAX;i++)
        {
            printf("%i ",coordinates[j][i]);
        }
        printf("\n");
    }
    printf("%i\n",changed_pixels);

}


void rotate_paste()
{
    char direction;
    int degree;
    int copy_row_1, copy_col_1, copy_row_2, copy_col_2;
    int paste_row_1, paste_col_1, paste_row_2, paste_col_2;
    int i,j;
    int changed_pixels=0;

    scanf(" %c",&direction);
    scanf("%i",&degree);
    scanf("%i %i %i %i",&copy_row_1, &copy_col_1, &copy_row_2, &copy_col_2);
    scanf("%i %i %i %i",&paste_row_1, &paste_col_1, &paste_row_2, &paste_col_2);


    for(i=copy_col_1;i<=copy_col_2;i++)
    {
        for(j=copy_row_1;j<=copy_row_2;j++)
        {
            int current_color;
            int current_pasting_x, current_pasting_y;

            current_color = coordinates[j][i];

            if((direction=='L' && degree==90) || (direction=='R' && degree==270))
            {
                current_pasting_x = paste_col_1 + (j-copy_row_1);

                current_pasting_y = paste_row_2 - (i-copy_col_1);
            }


            else if((direction=='L' && degree==180) || (direction=='R' && degree==180))
            {
                current_pasting_x = paste_col_2 - (i-copy_col_1);

                current_pasting_y = paste_row_2 - (j-copy_row_1);
            }


            else if((direction=='L' && degree==270) || (direction=='R' && degree==90))
            {
                current_pasting_x = paste_col_2 - (j-copy_row_1);

                current_pasting_y = paste_row_1 + (i-copy_col_1);
            }


            else if((direction=='L' && degree==0) || (direction=='R' && degree==0))
            {
                current_pasting_x = paste_col_1 + (i-copy_col_1);

                current_pasting_y = paste_row_1 + (j-copy_row_1);
            }




            if(coordinates[current_pasting_y][current_pasting_x] != current_color)
            {
                changed_pixels++;
            }

            coordinates[current_pasting_y][current_pasting_x] = current_color;

        }
    }

    /* Printing result*/

    for(j=MIN;j<MAX;j++)   
    {
        for(i=MIN;i<MAX;i++)
        {
            printf("%i ",coordinates[j][i]);
        }
        printf("\n");
    }
    printf("%i\n",changed_pixels);

}


int main()
{
    char operation;

    /* Initilazing colors  */

    int i,j;
    for(j=MIN;j<MAX;j++)   
    {
        for(i=MIN;i<MAX;i++)
        {
            scanf("%d", &coordinates[j][i]);
        }

    }




    scanf(" %c",&operation); 

    switch(operation)
    {

        /* Bucket Fill */
        case 'F': 
        {
            bucket_fill();
            break;
        }

        /* Copy Paste */
        case 'P':
        {
            copy_paste();
            break;
        }

        /* Copy Rotate Paste */
        case 'R':
        {
            rotate_paste();
            break;
        }
    }
    return 0;
}