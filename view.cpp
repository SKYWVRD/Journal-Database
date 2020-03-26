#include "view.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpacerItem>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QTableView>

#include <QDate>
#include <QMessageBox>

#include "spinboxdelegate.h"
#include "lineeditdelegate.h"


View::View(QWidget *parent):QDialog(parent)
{

    setWindowTitle("Journals");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setFixedHeight(425);
    setFixedWidth(800);

    authorEntry = new QLineEdit;
    yearEntry = new QSpinBox;
    yearEntry->setRange(0, QDate::currentDate().year());
    titleEntry = new QLineEdit;
    journalNameEntry = new QLineEdit;
    volumeEntry = new QSpinBox;
    volumeEntry->setRange(0, 9999);
    issueEntry = new QSpinBox;
    issueEntry->setRange(0, 9999);
    pagesEntry = new QLineEdit;
    addButton = new QPushButton("Add");
    removeButton = new QPushButton("Remove");
    filterEntry = new QLineEdit;
    columnChoice = new QComboBox;
    columnChoice->addItem("Author");
    columnChoice->addItem("Year");
    columnChoice->addItem("Title");
    columnChoice->addItem("Journal");
    columnChoice->addItem("Volume");
    columnChoice->addItem("Issue");
    filterButton = new QPushButton("Find");
    filterResetButton = new QPushButton("Reset");

    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox = new QHBoxLayout;
    QFormLayout* layout1 = new QFormLayout;
    QFormLayout* layout2 = new QFormLayout;
    QFormLayout* layout3 = new QFormLayout;

    layout1->addRow(tr("Author"), authorEntry);
    layout1->addRow(tr("Year"), yearEntry);
    layout1->addRow(tr("Title"), titleEntry);
    layout1->addRow(tr("Journal"),journalNameEntry);
    layout1->addRow(tr("Volume"), volumeEntry);
    layout1->addRow(tr("Issue"), issueEntry);
    layout1->addRow(tr("Pages"), pagesEntry);
    layout1->addRow(addButton);
    layout1->addRow(removeButton);
    layout2->addRow(filterEntry);
    layout2->addRow(columnChoice);
    layout2->addRow(filterButton);
    layout2->addRow(filterResetButton);


    vbox->addLayout(layout1);
    vbox->addSpacing(50);
    vbox->addLayout(layout2);

    hbox->addLayout(vbox);


    journalView = new QTableView;
    journalModel = newModel.returnModel();
    //journalView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    journalView->setModel(journalModel);
    journalView->setFixedWidth(650);
    journalView->setSortingEnabled(true);

    journalView->setItemDelegateForColumn(0, new LineEditDelegate(this));
    journalView->setItemDelegateForColumn(3, new LineEditDelegate(this));
    journalView->setItemDelegateForColumn(6, new LineEditDelegate(this));

    journalView->setItemDelegateForColumn(1, new SpinBoxDelegate(this));
    journalView->setItemDelegateForColumn(4, new SpinBoxDelegate(this));
    journalView->setItemDelegateForColumn(5, new SpinBoxDelegate(this));


    layout3->addRow(journalView);

    hbox->addLayout(layout3);

    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeEntry()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addEntry()));
    connect(filterButton, SIGNAL(clicked()), this, SLOT(filterEntries()));
    connect(filterResetButton, SIGNAL(clicked()), this, SLOT(resetFilter()));


    setLayout(hbox);

}

void View::removeEntry()
{
    newModel.removeItem(journalView->selectionModel()->currentIndex().row());
}

void View::addEntry()
{
    bool validAuthorEntry = false;
    bool validJournalEntry = false;
    bool validPageEntry = false;

    if(s_AuthorFormat.exactMatch(authorEntry->text()))
        validAuthorEntry = true;

    if(s_JournalFormat.exactMatch(journalNameEntry->text()))
        validJournalEntry = true;

    if(s_pageFormat.exactMatch(pagesEntry->text()))
        validPageEntry = true;

    if(validAuthorEntry && validJournalEntry && validPageEntry)
    {
        newModel.addItem(authorEntry->text(), yearEntry->value(), titleEntry->text(),
                     journalNameEntry->text(), volumeEntry->value(),
                     issueEntry->value(), pagesEntry->text());
        authorEntry->setText("");
        yearEntry->setValue(0);
        titleEntry->setText("");
        journalNameEntry->setText("");
        volumeEntry->setValue(0);
        issueEntry->setValue(0);
        pagesEntry->setText("");
    }

    //Prompt for user if he does not put in correct author format
    if(!validAuthorEntry)
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
        authorEntry->setText("");
    }

    //Prompt for user if he does not put in correct Journal format
    if(!validJournalEntry)
    {
        QMessageBox msgBox;
        msgBox.setText("Incorrect Journal Format");
        msgBox.setInformativeText("Please Use Format such as:\n"
                                  "\n"
                                  "- Popular Mechanics 2019\n"
                                  "- 20 Lonely Scientists\n"
                                  "\n"
                                  "Mixed letters and numbers in words are not allowed\n"
                                  "Capatalize all new words");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        journalNameEntry->setText("");
    }

    //Prompt for user if he does not put in correct Page format
    if(!validPageEntry)
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
        pagesEntry->setText("");
    }

}

void View::filterEntries()
{
    filterProxy = new QSortFilterProxyModel(this);
    filterProxy->setSourceModel(journalModel);

    /*Check which value was chosen in filter choice and then
     * choose the correspending column */

    if(columnChoice->currentText() == "Author")
        filterProxy->setFilterKeyColumn(0);
    else if(columnChoice->currentText() == "Year")
        filterProxy->setFilterKeyColumn(1);
    else if(columnChoice->currentText() == "Title")
        filterProxy->setFilterKeyColumn(2);
    else if(columnChoice->currentText() == "Journal")
        filterProxy->setFilterKeyColumn(3);
    else if(columnChoice->currentText() == "Volume")
        filterProxy->setFilterKeyColumn(4);
    else if(columnChoice->currentText() == "Issue")
        filterProxy->setFilterKeyColumn(5);

    //Set the filter to filter on string found in QLineEdit
    filterProxy->setFilterFixedString(filterEntry->text());
    journalView->setModel(filterProxy);

}

void View::resetFilter()
{
    //free up memory by deleting pointer and set model back to original
    if(filterProxy != NULL)
    {
        delete filterProxy;
        filterProxy = NULL;
        journalView->setModel(journalModel);
    }

}

//Regular Expressions used for input validation

QRegExp View::s_AuthorFormat(
        "[A-Z][A-Z]\\s{1}[A-Z][a-z]*(-?[A-Z][a-z]*)?[a-z]");

QRegExp View::s_JournalFormat(
        "([A-Z][a-z]*|[1-9][1-9]*)(\\s{1}([A-Z][a-z]*|[1-9][1-9]*))*");

QRegExp View::s_pageFormat(
        "[1-9][0-9]*-[1-9][0-9]*");
