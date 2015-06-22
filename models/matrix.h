#ifndef MATRIX_H
#define MATRIX_H

#include <QAbstractItemModel>

class Matrix : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Matrix(int pHeight, int pWidth, QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        bool setData(const QModelIndex &index, const QVariant &value, int role);
        bool rowFind(int row, int number);
        bool columnFind(int column, int number);
        Qt::ItemFlags flags(const QModelIndex &index) const;
        virtual bool insertOriginalValue(int x , int y, int value);
    private slots:
        void onSummaryChange();
    protected:
        int matrix[100][100];
        int height;
        int width;
    
};

#endif // MATRIX_H
