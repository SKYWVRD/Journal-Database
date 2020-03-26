#ifndef MODEL_H
#define MODEL_H

#include <model.h>
#include <QtGui>


class Model
{
public:
    Model();
    QStandardItemModel* returnModel() const;

    void addItem(QString author, int year, QString title,
                 QString journal, int volume, int issue,
                 QString pages);
    //Function adds an item to the model

    void removeItem(int i);
    //Function Removes an item from the model

private:
    QStandardItemModel* myModel;
    int rowCount = 0;
    int columnNumber = 7;

};

#endif // MODEL_H
