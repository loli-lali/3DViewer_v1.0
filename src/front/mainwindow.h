#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QSettings>
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveSettings();
    void loadSettings();
    void set_to_default();
    void set_to_default_moves();
    void set_to_default_rotations();
    void set_to_deafult_scale();
    void equalize_move();
    void equalize_rotation();
    void equalize_scale();
    void equalize_all();


signals:
    void back_color(int index);

private slots:
    void on_pushButton_file_clicked();

    void on_doubleSpinBox_y_move_valueChanged(double arg1);

    void on_doubleSpinBox_z_move_valueChanged(double arg1);

    void on_doubleSpinBox_x_rotate_valueChanged(double arg1);

    void on_doubleSpinBox_y_rotate_valueChanged(double arg1);

    void on_doubleSpinBox_z_rotate_valueChanged(double arg1);

    void on_comboBox_proection_currentIndexChanged(int index);

    void on_comboBox_edge_type_currentIndexChanged(int index);

    void on_pushButton_back_color_clicked();

    void on_comboBox_vert_type_currentIndexChanged(int index);

    void on_horizontalSlider_vert_size_valueChanged(int value);

    void on_horizontalSlider_edge_thick_valueChanged(int value);

    void on_pushButton_edge_color_clicked();

    void on_pushButton_vert_color_clicked();


    void on_doubleSpinBox_scale_valueChanged(double arg1);

    void on_doubleSpinBox_x_move_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
