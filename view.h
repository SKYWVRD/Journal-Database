#ifndef VIEW_H
#define VIEW_H
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QRegExpValidator>

#include "model.h"

class QLineEdit;
class QSpinBox;
class QPushButton;
class QLabel;
class QComboBox;


class View : public QDialog
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);

protected slots:
    void addEntry(); //This will add entrys to the table
    void removeEntry(); //This will remove entrys from teh table
    void filterEntries(); //this will filter based on a criteria
    void resetFilter(); //this will reset any filters on the table

private:
    QLineEdit* authorEntry;
    QSpinBox* yearEntry;
    QLineEdit* titleEntry;
    QLineEdit* journalNameEntry;
    QSpinBox* volumeEntry;
    QSpinBox* issueEntry;
    QLineEdit* pagesEntry;
    QPushButton* addButton;
    QPushButton* removeButton;
    QLineEdit* filterEntry;
    QComboBox* columnChoice;
    QPushButton* filterButton;
    QPushButton* filterResetButton;
    QStandardItemModel* journalModel;
    QTableView* journalView;

    Model newModel;

    QSortFilterProxyModel* filterProxy = NULL;

    static QRegExp s_AuthorFormat;
    static QRegExp s_JournalFormat;
    static QRegExp s_pageFormat;

};

#endif // VIEW_H
