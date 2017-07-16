#include "widget.h"
#include "ui_widget.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QInputDialog>
#include "intergeritemdelegate.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),m_matrixSize(0), m_sumMainDiagonal(0),
    m_sumSecondaryDiagonal(0), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(TITLE);
    m_model = new QStandardItemModel(this);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ui->actionStart_magic_number);
    ui->tableView->setModel(m_model);
    ui->tableView->setItemDelegate(new IntergerItemDelegate(this));
}

Widget::~Widget()
{
    delete ui;
}

const QString Widget::TITLE = "TeMagicSquare";

void Widget::on_actionStart_magic_number_triggered()
{
    m_matrixSize = QInputDialog::getInt(this, "Start", "Specify matrix size:", 3,
                                        2, 50, 1);
    m_model->clear();
    //qDebug() << "matrix size = " << m_matrixSize;
    m_model->setRowCount(m_matrixSize + 1);
    m_model->setColumnCount(m_matrixSize + 1);
    m_model->setHorizontalHeaderItem(m_matrixSize, new QStandardItem(QStringLiteral("Sum")));
    m_model->setVerticalHeaderItem(m_matrixSize, new QStandardItem(QStringLiteral("Sum")));
    ui->tableView->hideRow(m_matrixSize);
    ui->tableView->hideColumn(m_matrixSize);
    ui->lblDiagonalSums->setText("");
}

void Widget::on_btnTry_clicked()
{
    if(m_matrixSize == 0) return;
     //Las sumas de los elementos de cada fila
     calcRowSums();
     //Las sumas de los elemntos de cada columna
     calcColSums();
     //Las sumas de los elemtos de la diagonal de la matrix principal y la diagonal secundaria
     calcDiagonalSums();
     ui->tableView->showRow(m_matrixSize);
     ui->tableView->showColumn(m_matrixSize);
     ui->lblDiagonalSums->setText(QString::fromStdString("Diagonal elements sums: "
                                                         "main %1 secondary %2").
                                                         arg(m_sumMainDiagonal).
                                                         arg(m_sumSecondaryDiagonal));
     if(checkIfMagic())
     {
         QMessageBox::information(this, "Congratulations!", "This is magic square!");
     }
     else
     {
         QMessageBox::critical(this, "What a pity!", "This is not magic square!");
     }
}

void Widget::calcRowSums()
{
    const int rowCount = m_model->rowCount();
    const int colCount = m_model->columnCount();
    for(int r = 0; r < rowCount - 1; ++r)
    {
        int sum = 0;
        for(int c = 0; c < colCount - 1; ++c)
        {
            sum += getValueAt(r, c);
        }
        setValueAt(r, colCount - 1, sum);
    }
}

void Widget::calcColSums()
{
    const int rowCount = m_model->rowCount();
    const int colCount = m_model->columnCount();
    for(int c = 0; c < colCount - 1; ++c)
    {
        int sum = 0;
        for(int r = 0; r < rowCount - 1; ++r)
        {
            sum += getValueAt(r, c);
        }
        setValueAt(rowCount - 1, c, sum);
    }
}

void Widget::calcDiagonalSums()
{
    const int size = m_model->rowCount();
    int sumMainDiagonal = 0, sumSecondaryDiagonal = 0;
    for(int i = 0; i < size - 1; ++i)
    {
        sumMainDiagonal += getValueAt(i, i);
        sumSecondaryDiagonal += getValueAt(i, size - 2 - i);
    }
    m_sumMainDiagonal = sumMainDiagonal;
    m_sumSecondaryDiagonal = sumSecondaryDiagonal;
}

bool Widget::checkIfMagic() const
{
    bool result = true;
    int size = m_model->rowCount() - 1;
    int val = getValueAt(size, 0);
    for(int i = 0; i < size; ++i)
    {
        if(getValueAt(size, i) != val)
        {
            result = false;
            break;
        }
        if(getValueAt(i, size) != val)
        {
            result = false;
            break;
        }
        if(result)
        {
            if(m_sumMainDiagonal != val ||
               m_sumSecondaryDiagonal != val)
            {
                result = false;
            }
        }
    }
    return result;
}

int Widget::getValueAt(int row, int col) const
{
    auto pItem = m_model->item(row, col);
    return pItem == nullptr ? 0 : pItem->text().toInt();
}

void Widget::setValueAt(int row, int col, int val)
{
    if(row >= 0 && row < m_model->rowCount() &&
       col >= 0 && col < m_model->columnCount())
    {
        m_model->setItem(row, col, new QStandardItem(QString::number(val)));
    }
}
