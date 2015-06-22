#ifndef SUDOKU_H
#define SUDOKU_H

#include "matrix.h"
#include <QString>


class Sudoku : public Matrix
{
    Q_OBJECT
public:
    explicit Sudoku(QObject *parent = 0);

    bool insertOriginalValue(int x , int y, int value);

    bool canBeInserted(int x , int y, int value);

    bool findInSquare(int x , int y, int value);

    QString toString();

    void solve();

    void nextStep(int *x, int *y);

    void previusStep(int *x, int *y);
    QVariant data(const QModelIndex &index, int role) const;

private:
    bool original[9][9];
};

#endif // SUDOKU_H
