#include <iostream>
#include <cmath> // for pow()
#include <fstream> // for file operation
#include <iomanip> // for output customization

using namespace std;
int start(void); // The main menu
int input(void); // get an input
void det_menu(void); // main menu for matrix determinant
float det2x2 (float num[2][2]); // 2x2 matrix determinant
float det3x3 (float num[3][3]);// 3x3 matrix determinant
void LU_menu(void); // main menu for LU Factorization
void LU_decomp(float A[4][4], float L[4][4], float U[4][4], float Y[4], int n); // calculates L and U
void interpolation(void); // Least Square Approximation

int main()
{
    int choice;
    choice = start();
    if(choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        cout << "Wrong Input!" << endl;
        main();
        return 0;
    }
    while (choice != 4)
    {
        // start of det calc
        if(choice == 1)
        {
            det_menu();
            return 0;
        }
        // strat of LU Factorization
        else if(choice == 2)
        {
            LU_menu();
            return 0;
        }
        // strat of interpolation
        else if(choice == 3)
        {
            interpolation();
            return 0;
        }
        else // error checking
        {
            cout << "Wrong Input!! Try Again" << endl << endl;
            main();
            return 0;
        }
    }
    cout << "Thanks for using our program" << endl;
        cout << "Made by:\n1.\tSaleh Mohamed Ahmed\t A19EC4058\n2.\tAnas Roubi Abdelsattar\t A19EC4047\n3.\tMajd Alali\t\t A19EC4038\n\n";
    return 0;
}

int start(void)
{
    cout << endl << "-----------------------------" << endl;
    cout << "\tMenu" << endl<< "-----------------------------"<< endl;
    cout << " 1) determinant calculation" << endl;
    cout << " 2) LU Factorization" << endl;
    cout << " 3) Interpolation" << endl;
    cout << " 4) Exit" << endl << endl;
    return input();
}

int input(void)
{
    int n;
    cout << "Input Option:\t";
    cin >> n;
    cout << endl;
    return n;
}

void det_menu(void)
{
    int c;
    cout << endl << "Dimension:" << endl;
    cout << " 1) 2x2 Matrix" << endl;
    cout << " 2) 3x3 Matrix" << endl;
    cout << " 0) Back" << endl;
    c = input();
    // check dimension of matrix
    if(c == 1)
    {
        float elements[2][2];
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                cout << "enter element A"<< i+1 << j+1 <<" :\t";
                cin >> elements[i][j];
            }

        }
        cout << endl << "The determinant is    " << det2x2(elements);
        main();
    }
    else if(c == 2)
    {
        float elements[3][3];
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cout << "enter element A"<< i+1 << j+1 <<" :\t";
                cin >> elements[i][j];
            }

        }
        cout << endl << "The determinant is    " << det3x3(elements) << endl;
        main();
    }
    else if(c == 0)
    {
        main();
        return;
    }
    else // error checking
    {
        cout << "Wrong Dimension!!" << endl << endl;
        det_menu();
        return;
    }
    
}

float det2x2 (float num[2][2])
{
    return num[0][0] * num[1][1] - num[0][1] * num[1][0];
}

float det3x3 (float num[3][3])
{
    float mat1[2][2] = {{num[1][1], num[1][2]}, {num[2][1],num[2][2]}};
    float mat2[2][2] = {{num[1][0], num[1][2]}, {num[2][0],num[2][2]}};
    float mat3[2][2] = {{num[1][0], num[1][1]}, {num[2][0],num[2][1]}};
    return num[0][0] * det2x2(mat1) - num[0][1] * det2x2(mat2) + num[0][2] * det2x2(mat3);
}

//
void LU_menu(void)
{
    int n, i, j, c = 0;
    string order[4] = {"1st", "2nd", "3rd", "4th"};
    char var[4] = {'X', 'Y', 'Z', 'W'};
    float A[4][4], L[4][4], U[4][4], B[4], Y[4], X[4] = {0, 0, 0, 0}, sum;
    
    cout << "*Note: Number of varibales and equations must be the same" << endl;
    cout << "enter the number of variables and equations (n <= 4) or enter 0 to return the main menu: ";
    cin >> n;
    if(n == 0)
    {
        main();
        return;
    }
    if(n < 1 || n > 4) // error checking
    {
        cout << "Wrong Input!";
        LU_menu();
        return;
    }
    cout << "which way do you prefer to give input:\t" << endl;
    cout << " 1) equation coefficients" << endl;
    cout << " 2) augmented matrix" << endl;
    while(c != 1 && c != 2)
    {
        c = input();
        if(c != 1 && c != 2) // error checking
        {
            cout << "Wrong Input!";
        }
    }
    // determine the method of giving input
    if(c == 1)
    {
        cout << "****************************************************************************************"<< endl;
        cout << "Enter the coefficients as follows:" << endl;
        cout << "variables are (x, y, z, w) in order [depeneds on how many you choose]" << endl;
        cout << "****************************************************************************************"<< endl;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                cout << "enter the "<< var[j] <<" coefficient in the " <<order[i] << " equation :\t";
                cin >> A[i][j];
            }
            cout << "enter the constant of the " << order[i] << " equation :\t";
            cin >> B[i];
        }
    }
    if(c == 2)
    {
        cout << "****************************************************************************************"<< endl;
        cout << "Enter the elements of the augmented matrix (" << n + 1 << " elements per row)" << endl;
        for (i = 0; i < n; i++)
        {
            cout << "enter the " << order[i] << " row" << endl;
            for(j = 0; j < n; j++)
            {
                cin >> A[i][j];
            }
            cin >> B[i];
        }
    }
    // write the formula start
    cout << endl << "you have entered: " << endl;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(A[i][j] != 0)
            {
                if(A[i][j] == 1)
                {
                    if(j == 0)
                    {
                        cout << var[j];
                    }
                    else
                    {
                        cout << " + " << var[j];
                    }

                }
                else if(A[i][j] == -1)
                {
                    cout << " - " << var[j];
                }
                else if(A[i][j] > 0)
                {
                    if(j == 0)
                    {
                        cout << A[i][j] << var[j];
                    }
                    else
                    {
                        cout << " + " << A[i][j] << var[j];
                    }
                }
                else
                {
                    cout << " " << A[i][j] << var[j];
                }
            }
        }
        cout << " = " << B[i];
        cout << endl;
    }
    // write the formula end
    cout << endl;
    cout << endl;
    LU_decomp(A, L, U, Y, n); // pass all arrays to function that calculates L and U
    // calculate Y
    for(i = 0; i < n; i++)
    {
        sum = 0;
        for(j = 0; j < n; j++)
        {
            if(j != i)
            {
                sum += L[i][j] * Y[j];
            }
        }
        Y[i] = B[i] - sum;
    }
    // calculate X
    for(i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for(j = n - 1; j >= 0; j--)
        {
            if(j != i)
            {
                sum += U[i][j] * X[j];
            }
        }
        X[i] = (Y[i] - sum)/U[i][i];
    }
    // write the solution
    cout << "the solution is:" << endl;
    for(i = 0; i < n; i++)
    {
        cout << var[i] << " = " << X[i] << ",\t";
    }
    main();
}
void LU_decomp(float A[4][4], float L[4][4], float U[4][4], float Y[4], int n)
{
    int i = 0, j = 0, k = 0;
    float sum;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j) // L main diagonal
            {
                L[i][j] = 1;
            }
            else if(i < j) // L upper part
            {
                L[i][j] = 0;
            }
            else if(i > j) // U lower part
            {
                U[i][j] = 0;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if(i == 0)
        {
            for(k = 0; k < n; k++)
            {
                U[0][k] = A[0][k];
            }
        }
        else
        {
            for(j = 0; j < n; j++)
            {
                if(i > j)
                {
                    sum = 0;
                    for(k = 0; k < n; k++)
                    {
                        if(k != j)
                        {
                            sum += L[i][k] * U[k][j];
                        }
                        L[i][j] = (A[i][j] - sum) / U[j][j];
                    }
                }
            }
            for(j = 0; j < n; j++)
            {
                if(i <= j)
                {
                    sum = 0;
                    for(k = 0; k < i; k++)
                    {
                        if(k != j)
                        {
                            sum += L[i][k] * U[k][j];
                        }
                        U[i][j] = A[i][j] - sum;
                    }
                }
            }
        }
    }
}
void interpolation()
{
    int k, i, j, n = 3;
    string order[4] = {"1st", "2nd", "3rd", "4th"};
    do
    {
        cout << "Enter the number of inputs (k <= 7) or enter 0 to return:\t";
        cin >> k;
    }while(k > 7 || k < 0);
    if(k == 0)
    {
        main();
        return;
    }
    float x_values[k], y_values[k], Xi, sum;
    cout << "Enter Values of X (separated by space):" << endl;
    for(i = 0; i < k; i++)
    {
        cin >> x_values[i];
    }
    cout << "Enter Values of Y (separated by space):" << endl;
    for(i = 0; i < k; i++)
    {
        cin >> y_values[i];
    }
    float sum1 = k, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0, sum7 = 0, sum8 = 0;
    // prepare the table
    for(i = 0; i < k; i++)
    {
        sum2 += x_values[i];
        sum3 += pow(x_values[i], 2);
        sum4 += pow(x_values[i], 3);
        sum5 += pow(x_values[i], 4);
        sum6 += y_values[i];
        sum7 += x_values[i]*y_values[i];
        sum8 += pow(x_values[i], 2) * y_values[i];
    }
    // form the system of linear equations
    float A[4][4] = {{sum1, sum2, sum3}, {sum2, sum3, sum4}, {sum3, sum4, sum5}};
    float L[4][4], U[4][4], Y[4], X[3];
    float B[4] = {sum6, sum7, sum8};
    LU_decomp(A, L, U, Y, 3); // calc L and U by func from Q2
    // calc Y [copied form Q2]
    for(i = 0; i < n; i++)
    {
        sum = 0;
        for(j = 0; j < n; j++)
        {
            if(j != i)
            {
                sum += L[i][j] * Y[j];
            }
        }
        Y[i] = B[i] - sum;
    }
    // calc X [copied form Q2]
    for(i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for(j = n - 1; j >= 0; j--)
        {
            if(j != i)
            {
                sum += U[i][j] * X[j];
            }
        }
        X[i] = (Y[i] - sum)/U[i][i];
    }
    cout << "Enter value of Xi:\t";
    cin >> Xi;
    // write the quadratic function
    if(X[0] != 0)
    {
        cout << "P(x) = " << X[0];
    }
    if(X[1] != 0)
    {
        if(X[1] > 0)
        {
            cout << " + " << X[1] << " X";
        }
        else
        {
            cout << " " << X[1] << " X";
        }
    }
    if(X[2] != 0)
    {
        if(X[2] > 0)
        {
            cout << " + " << X[2] << " X^2";
        }
        else
        {
            cout << " " << X[2] << " X^2";
        }
    }
    cout << endl;
    // write the interpolation answer
    cout << "P(" << Xi << ") = " << X[0] + X[1] * Xi + X[2] * pow(Xi, 2);
    main();
}


