#include "sudoku.h"
#include <QDebug>
#include <QColor>
#include <QTest>
#include <QFont>

Sudoku::Sudoku(QObject *parent) :
    Matrix(9,9,parent)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            original[i][j]=false;
        }
    }
}

bool Sudoku::insertOriginalValue(int x, int y, int value)
{
    bool inserted = false;
    if(canBeInserted(x,y,value))
    {
        matrix[x][y]= value;
        inserted = true;
        original[x][y] = true;
    }
    emit layoutChanged();
    return inserted;
}

bool Sudoku::canBeInserted(int x, int y, int value)
{
    return !( columnFind(y,value) || (rowFind(x,value) || findInSquare(x,y,value))) && value <10 && value>=0;
}

bool Sudoku::findInSquare(int x, int y, int value)
{
    int xStart=x/3;
    xStart = xStart*3;

    int yStart=y/3;
    yStart = yStart*3;
    bool founded= false;
    for (int i = xStart ; i < xStart+3 && !founded; i++)
    {
        for (int j = yStart ; j < yStart+3 && !founded; j++)
        {
            founded = matrix[i][j] == value;
        }
    }
    return founded;
}

QString Sudoku::toString()
{
    QString output="";
    for (int i = 0 ; i < 9 ; i++)
    {
        for (int j = 0 ; j < 9; j++)
        {
            output.append(QString::number(matrix[i][j]));
//            if(matrix[i][j]==0)
//            {
//                return "";//TODO corregir esto
//            }
        }
    }
    return output;
}

void Sudoku::solve()
{
    bool posible=true , unfinish= true;
    int x=-3 ,y=-3 ;
    while(posible && unfinish)
    {
        emit layoutChanged();
//        QTest::qWait(100);
        if(x<0)
        {
            if(x==-1)
            {
                unfinish=false;
            }
            else
            {
                if(x==-2)
                {
                    posible=false;
                }
                else
                {
                    nextStep(&x,&y);
                }
            }

        }
        else
        {


                bool inserted = false;
                int j=1;
                while( !inserted   && matrix[x][y]+j<10)
                {
                    if(canBeInserted(x,y,matrix[x][y]+j))
                    {
                        matrix[x][y]=matrix[x][y]+j;
                        inserted= true;
                    }
                    j++;
                }
                if(inserted)
                {
                    nextStep(&x,&y);
                }
                else
                {
                    matrix[x][y]= 0;
                    previusStep(&x,&y);

                }
        }


    }

}

void Sudoku::nextStep(int *x, int* y)
{
    if(*x==-3)
    {
        *x=0;
        *y=0;
    }
    else
    {


        *x=*x+1;


        *y = *y +  *x/9;

        *x = *x%9;
    }
    if(*y<9 && (original[*x][*y]))
    {
        nextStep(x,y);
    }
    else
    {
        if(*y>=9)
        {
            *x=-1;
            *y=-1;
        }
    }
}

void Sudoku::previusStep(int *x, int *y)
{
    if(*y==0 && *x==0)
    {
        *x=-2;
        *y=-2;
    }
    else
    {
        if(*x-1>=0)
        {
            *x=*x-1;
        }
        else
        {
            *x=8;
            *y=*y-1;
        }
        if((original[*x][*y]))
        {
            previusStep(x,y);
        }
    }

}
QVariant Sudoku::data(const QModelIndex &index, int role) const
{
    QVariant data;
    int row = index.row();
    int column = index.column();
    if(role == Qt::DisplayRole)
    {
        if( row < height    &&  column < width)
        {
            data = QVariant(matrix[row][column]);
            if(matrix[row][column]==0)
              {
                data= QVariant();

              }
        }
        else
        {
            data = QVariant(0);

        }
    }
    if(role == Qt::TextColorRole && original[row][column]==true)
      return QVariant::fromValue(QColor(Qt::green));
    if(role == Qt::FontRole && original[row][column]==true)
    {
        QFont fuente;
        fuente.setBold(true);
        fuente.setBold(true);
        return QVariant::fromValue(fuente);
    }
    if(role ==Qt::TextAlignmentRole)
    {
        return (Qt::AlignCenter);
    }
    if(role ==Qt::BackgroundColorRole)
    {
        bool output= (((row>=0 && row<3) || (row<9 && row>=6)) && column>=3 && column<6)
                || (((column>=0 && column<3) || (column<9 && column>=6)) && row>=3 && row<6);
        if(output)
        {
            return QColor(Qt::gray);
        }
        else
        {
            return QColor(Qt::darkGray);
        }
    }

    return data;
}
