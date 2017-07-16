#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
    class Widget;
}

class QStandardItemModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_actionStart_magic_number_triggered();
    void on_btnTry_clicked();
    void calcRowSums();
    void calcColSums();
    void calcDiagonalSums();
    bool checkIfMagic() const;
    int getValueAt(int row, int col) const;
    void setValueAt(int row, int col, int val);

private:
    static const QString TITLE;
    int m_matrixSize;
    int m_sumMainDiagonal, m_sumSecondaryDiagonal;
    Ui::Widget *ui;
    QStandardItemModel *m_model;
};

#endif // WIDGET_H
