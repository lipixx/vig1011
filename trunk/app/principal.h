#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <dialegmaterials.h>

namespace Ui {
    class Principal;
}

class Principal : public QWidget {
    Q_OBJECT
public:
    Principal(QWidget *parent = 0);
    ~Principal();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::Principal *ui;
    DialegMaterials dm;

public slots:
    void setFilferrosCheckBox(bool);

private slots:
    void showMatDialog();
};

#endif // PRINCIPAL_H
