#ifndef DIALEGMATERIALS_H
#define DIALEGMATERIALS_H

#include <QWidget>
#include <glwidget.h>

namespace Ui {
    class DialegMaterials;
}

class DialegMaterials : public QWidget
{
    Q_OBJECT

public:
    explicit DialegMaterials(QWidget *parent = 0);
    ~DialegMaterials();

    void updateData();
    void initialize(GLWidget *glw);

private:
    Ui::DialegMaterials *ui;
    GLWidget *glwidget;
    Color nouColor, backupColor;
    int idActual;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void accepta();
    void updateR(int);
    void updateG(int);
    void updateB(int);
    void updateA(int);
};

#endif // DIALEGMATERIALS_H
