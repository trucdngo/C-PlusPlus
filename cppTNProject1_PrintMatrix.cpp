
/*
 UCSC Extension, C++ Comprehensive, Spring 2016
 Project #1
 Project Name: Print a square matrix with sum of each row, each column,
 and the two main diagonals are all equal
 Compiler: XCode Version 7.2
 Due Date: May 1, 2016
 Student: Truc ngo
 truc.dinh.ngo@gmail.com
 */

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

class MagicSquare {
private:
    int matrixSize;
    int matrixDiagonalSum;
    int** matrixPointer;
public:
    void printProgramIntroduction();
    void initializeMatrix(int n);
    void buildMatrix();
    void printMatrix();
    void freeMatrix();
};

void MagicSquare::printProgramIntroduction() {
    cout << "\nMagic Squares: This program produces an NxN matrix where\n"
    << "N is some positive odd integer.  The matrix contains the \n"
    << "values 1 to N*N.  The sum of each row, each column, and \n"
    << "the two main diagonals are all equal.  Not only does this \n"
    << "program produces the matrix, it also computes the totals for\n"
    << "each row, column, and two main diagonals.\n";
    cout << "\n";
    cout << "\nBecause of display constraints, this program can work with\n"
    << "values up to 13 only.\n\n";
    cout << "Enter a positive, odd integer (-1 to exit program):\n";
}


void MagicSquare::initializeMatrix(int n) {
    /* update member variable */
    matrixSize = n;
    
    /* create a array of pointers-to-pointers; array_size = matrix_size */
    int **pnMatrix=0;
    //pnMatrix = new int*[matrixSize];
    //fixed
    pnMatrix = new int*[matrixSize+1];
    
    /* each of the pointer points to array of int; array_size = matrix_size */
    for (int row=0; row<= matrixSize; row++)
        //pnMatrix[row] = new int[matrixSize];
        pnMatrix[row] = new int[matrixSize+1];
    
    /* Initialize matrix, row, col, and otherdiag       */
    /* Initialize matrix with all zeroes.               */
    for (int row=0; row<= matrixSize; row++)
        for (int col=0; col <= matrixSize; col++)
            *(pnMatrix[row] + col) = 0;
    
    /* update member variable */
    matrixPointer = pnMatrix;
}



void MagicSquare::buildMatrix() {
    cout << "testing : value of matrix size is "  << matrixSize << endl;
    int value = 0;
    int otherdiag = 0;
    int** pnMatrix = matrixPointer;
    

    /*  Values will reside within  */
    /*  rows 1 to matrix_size*matrix_size and  */
    /*  columns 1 to matrix_size*matrix_size.  */
    /*  Row totals will reside in matrix[row][0], where row is the row number */
    /*  Column totals will reside in matrix[0][col], where col is the column number. */
    
    int row = 1;                      /* First value gets to sit on */
    int col = matrixSize/2 + 1;       /* 1st row, middle of matrix. */
    /*  Loop for every value up to matrix_size*matrix_size, and position value in matrix */
    for (value = 1; value <= matrixSize*matrixSize; value++)
    {                                     /*  Loop for all values.      */
        if (*(pnMatrix[row] + col) > 0)   /*  If some value already     */
        {                                 /*  present, then             */
            row += 2;                     /*  move down 1 row of prev.  */
            if (row > matrixSize)         /*  If exceeds side, then     */
                row -= matrixSize;        /*  go to other side.         */
            
            col--;                        /*  move left 1 column.       */
            if (col < 1)                  /*  If exceeds side, then     */
                col = matrixSize;         /*  go to other side.         */
        }
        
        *(pnMatrix[row] + col) = value;   /* Assign value to location.  */
        /* Add to totals  */
        *(pnMatrix[0] + col) += value;    /* Add to its column total.   */
        *(pnMatrix[row]) += value;        /* Add to its row total.      */

        if (row == col)                   /* Add to diagonal total if   */
        *(pnMatrix[0]) += value;          /* it falls on the diagonal.  */
        
        if (row+col == matrixSize+1)      /* Add to other diagonal if   */
            otherdiag += value;           /* it falls on the line.      */
        
        /* Determine where new row and col are  */
        row--;
        if (row < 1)                      /* If row exceeds side then   */
            row = matrixSize;             /*  goto other side.          */
        col++;
        if (col > matrixSize)             /* If col exceeds side then   */
            col = 1;                      /* goto other side.           */
    }                                     /* End of getting all values. */
    
    /* for testing: print matrix */
    /*
    for (row=0; row<= matrixSize; row++) {
        for (col=0; col <= matrixSize; col++)
            cout << pnMatrix[row][col];
        cout << "\n";
    }*/
    
    /* update member variable */
    matrixDiagonalSum = otherdiag;
}

void MagicSquare::freeMatrix() {
    for (int row=0; row<= matrixSize; row++)
        delete [] matrixPointer[row];
    delete [] matrixPointer;
}

void MagicSquare::printMatrix() {
  
    cout << "\nThe number you selected was: " << matrixSize;
    cout << ", and the matrix is:\n\n";
    for (int row = 1 ; row <= matrixSize; row++)     /* Loop: print a row at a time*/
    {
        cout << "     ";       /* Create column for diag.total*/
        for (int col = 1; col <= matrixSize; col++)
            cout << setw(5) << *(matrixPointer[row] + col);               /* Print values found in a row */
            cout << "  = " << setw(5)  << *(matrixPointer[row]) << endl;  /* Print total of row.         */
    }
    
    /* Print out the totals for each column, starting with diagonal total. */
    for (int col = 0; col <= matrixSize; col++)         /* Print line separating the    */
        cout << "-----";                                /*  value matrix and col totals */
    cout << endl << setw(5) << matrixDiagonalSum;       /* Print out the diagonal total */
    for (int col = 1; col <= matrixSize; col++)
        cout << setw(5) << *(matrixPointer[0] + col);   /* Print out the column totals  */
    cout << setw(5) << *(matrixPointer[0]) << endl ;    /* Print out the other diagonal */

}


int main() {
    
    int input = 0;
    MagicSquare ms;
    ms.printProgramIntroduction();
    while (cin >> input || !cin.eof())
    {
        
        /* If input = -1, then exit program. */
        if (input == -1)
            break;

        /* Validity check for input: Must be a positive odd integer < 13. */
        if (input <= 0)
        {
            cout << "Sorry, but the integer has to be positive.\n";
            cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
            continue;
        }
        else if (input > 13)
        {
            cout << "Sorry, but the integer has to be less than 15.\n";
            cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
            continue;
        }
        else if ((input%2) == 0)
        {
            cout << "Sorry, but the integer has to be odd.\n";
            cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
            continue;
        }
        ms.initializeMatrix(input);
        ms.buildMatrix();
        ms.printMatrix();
        ms.freeMatrix();
        cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
        
    }
    cout << "Bye Bye!" << endl;
}


