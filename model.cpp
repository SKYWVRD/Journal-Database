#include "model.h"
#include <QColor>
#include <QSpinBox>

Model::Model()
{
    //Set up all columns in the model
    myModel = new QStandardItemModel(0, columnNumber);
    myModel->setHorizontalHeaderItem( 0, new QStandardItem( "Author" ));
    myModel->setHorizontalHeaderItem( 1, new QStandardItem( "Year" ) );
    myModel->setHorizontalHeaderItem( 2, new QStandardItem( "Title" ) );
    myModel->setHorizontalHeaderItem( 3, new QStandardItem( "Journal" ) );
    myModel->setHorizontalHeaderItem( 4, new QStandardItem( "Volume" ) );
    myModel->setHorizontalHeaderItem( 5, new QStandardItem( "Issue" ) );
    myModel->setHorizontalHeaderItem( 6, new QStandardItem( "Pages" ) );
}

QStandardItemModel* Model::returnModel() const
{
    return myModel;
}

void Model::addItem(QString author, int year, QString title,
                    QString journal, int volume, int issue,
                    QString pages)
{
    //Add all values to respective columns
    QStandardItem* Author = new QStandardItem(QString(author));
    myModel->setItem(this->rowCount,0, Author);
    QStandardItem* Year = new QStandardItem(QString::number(year));
    myModel->setItem(this->rowCount,1, Year);
    QStandardItem* Title = new QStandardItem(QString(title));
    myModel->setItem(this->rowCount,2, Title);
    QStandardItem* Journal = new QStandardItem(QString(journal));
    myModel->setItem(this->rowCount,3, Journal);
    QStandardItem* Volume = new QStandardItem(QString::number(volume));
    myModel->setItem(this->rowCount,4, Volume);
    QStandardItem* Issue = new QStandardItem(QString::number(issue));
    myModel->setItem(this->rowCount,5, Issue);
    QStandardItem* Pages = new QStandardItem(QString(pages));
    myModel->setItem(this->rowCount,6, Pages);

    //Colour row depending on year value
    if(QDate::currentDate().year()-year >= 10)
    {
        for(int i = 0; i < columnNumber; i++)
            myModel->item(rowCount, i)->setBackground(Qt::red);
    }

    else if(QDate::currentDate().year()-year <= 5)
    {
        for(int i = 0; i < columnNumber; i++)
            myModel->item(rowCount, i)->setBackground(Qt::green);

    }
    else
    {
        for(int i = 0; i < columnNumber; i++)
            myModel->item(rowCount, i)->setBackground(Qt::white);
    }

    //Increase number of rows
    this->rowCount++;

}

void Model::removeItem(int index)
{
    myModel->removeRow(index);
    this->rowCount--;
}


