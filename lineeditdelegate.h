#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H
#include <QStyledItemDelegate>
class LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LineEditDelegate(QObject *parent = NULL);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
private:
    static QRegExp s_AuthorFormat;
    static QRegExp s_JournalFormat;
    static QRegExp s_pageFormat;

};

#endif // LINEEDITDELEGATE_H
