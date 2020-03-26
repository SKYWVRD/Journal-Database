#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QDate>
#include <QPainter>
#include <QMessageBox>

LineEditDelegate::LineEditDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *LineEditDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);

    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    bool validInput = false;
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();

    if(index.column() == 0)
        if(s_AuthorFormat.exactMatch(value))
            validInput = true;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Incorrect Author Format");
            msgBox.setInformativeText("Please Use Format such as:\n"
                                      "\n"
                                      "- SA Boonzaier\n"
                                      "- D Paul-Hucks");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }

    else if(index.column() == 3)
        if(s_JournalFormat.exactMatch(value))
            validInput = true;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Incorrect Journal Format");
            msgBox.setInformativeText("Please Use Format such as:\n"
                                      "\n"
                                      "- Popular Mechanics 2019\n"
                                      "- 20 Lonely Scientists\n"
                                      "\n"
                                      "Mixed letters and numbers in words are not allowed\n"
                                      "Capatalize all new words");;
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }

    else if(index.column() == 6)
        if(s_pageFormat.exactMatch(value))
            validInput = true;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Incorrect Page Format");
            msgBox.setInformativeText("Please Use Format such as:\n"
                                      "\n"
                                      "- 1-2\n"
                                      "- 10-12");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }




    if(validInput)
        model->setData(index, value, Qt::EditRole);

}

void LineEditDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

void LineEditDelegate::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    painter->fillRect(option.rect,Qt::green);
    QStyledItemDelegate::paint(painter,option,index);

}

QRegExp LineEditDelegate::s_AuthorFormat(
        "[A-Z][A-Z]\\s{1}[A-Z][a-z]*(-?[A-Z][a-z]*)?[a-z]");

QRegExp LineEditDelegate::s_JournalFormat(
        "([A-Z][a-z]*|[1-9][1-9]*)(\\s{1}([A-Z][a-z]*|[1-9][1-9]*))*");

QRegExp LineEditDelegate::s_pageFormat(
        "[1-9][0-9]*-[1-9][0-9]*");


