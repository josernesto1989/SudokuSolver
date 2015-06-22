#include "matrix.h"

Matrix::Matrix(int pHeight, int pWidth, QObject *parent) :
    QAbstractItemModel(parent)
{
    height = qMin( 100 , pHeight);
    width = qMin( 100 , pWidth);
    for(int i = 0 ; i<height ;  i++)
    {
        for(int j = 0 ; j<width ;  j++)
        {
            matrix[i][j]=0;

        }
    }

}



QModelIndex Matrix::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row,column);
}
QModelIndex Matrix::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}
int Matrix::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return height;
}
int Matrix::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return width;
}
QVariant Matrix::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if(role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();
        if( row < height    &&  column < width)
        {
            data = QVariant(matrix[row][column]);
        }
        else
        {
            data = QVariant(0);

        }
    }
    return data;
}
bool Matrix::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    return insertOriginalValue(index.row(), index.column(), value.toInt());
}

QVariant Matrix::headerData ( int section, Qt::Orientation orientation, int role) const
{
    QVariant d = QAbstractItemModel::headerData(section,orientation,role);
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
            d = QString::number(section+1);
    }

    return d;

}


/*!
 * \brief Matrix::onSummaryChange emite la señal layoutChanged()
 * para actualizar la vista
 */
void Matrix::onSummaryChange()
{
    emit layoutChanged();
}

bool Matrix::rowFind(int row, int number)
{
    bool founded = row>= height  || row < 0 ;
    for (int i = 0; i < width  && !founded; i++)
    {
        founded = matrix[row][i]==number ;
    }
    return founded;
}

bool Matrix::columnFind(int column, int number)
{
    bool founded = column>= width  || column < 0 ;
    for (int i = 0; i < width  && !founded; i++)
    {
        founded = matrix[i][column]==number ;
    }
    return founded;
}

bool Matrix::insertOriginalValue(int x, int y, int value)
{
    matrix[x][y]=value;
    return true;
}

Qt::ItemFlags Matrix::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    Qt::ItemFlags flags= Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return flags;
}
