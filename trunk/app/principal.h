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
    void setStatusLlums();
    void resetLights();
    void actualitzaParamsObj(double,double);

private slots:
    void showMatDialog();
    void showLightDialog();
};

#endif // PRINCIPAL_H
