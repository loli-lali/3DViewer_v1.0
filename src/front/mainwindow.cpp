#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->ui->pushButton_vert_color->setDisabled(true);
  this->ui->horizontalSlider_vert_size->setDisabled(true);
}

MainWindow::~MainWindow() { delete ui; }

/* ----------  функции для возвращения к дефолтным значениям ------------ */

void MainWindow::set_to_default_moves() {
  this->ui->glwidget->X_move = 0;
  this->ui->glwidget->X_move_prev = 0;
  this->ui->glwidget->Y_move = 0;
  this->ui->glwidget->Y_move_prev = 0;
  this->ui->glwidget->Z_move = 0;
  this->ui->glwidget->Z_move_prev = 0;
}

void MainWindow::set_to_default_rotations() {
  this->ui->glwidget->X_rotate = 0;
  this->ui->glwidget->Y_rotate = 0;
  this->ui->glwidget->Z_rotate = 0;
}

void MainWindow::set_to_deafult_scale() {
  this->ui->glwidget->scale_obj = 1;
  this->ui->glwidget->scale_obj_prev = 1;
}

void MainWindow::set_to_default() {
  set_to_default_moves();
  set_to_default_rotations();
  set_to_deafult_scale();
}

/* ----------  функции для приравнивания старого значения к нынешнему
 * ------------ */
/* чтобы лишний раз ничего не двигалось когда происходит update при нажатии на
 * другую кнопку */

void MainWindow::equalize_move() {
  ui->glwidget->X_move_prev = ui->glwidget->X_move;
  ui->glwidget->Y_move_prev = ui->glwidget->Y_move;
  ui->glwidget->Z_move_prev = ui->glwidget->Z_move;
}

void MainWindow::equalize_rotation() {
  ui->glwidget->X_rotate_prev = ui->glwidget->X_rotate;
  ui->glwidget->Y_rotate_prev = ui->glwidget->Y_rotate;
  ui->glwidget->Z_rotate_prev = ui->glwidget->Z_rotate;
}

void MainWindow::equalize_scale() {
  ui->glwidget->scale_obj_prev = ui->glwidget->scale_obj;
}

void MainWindow::equalize_all() {
  equalize_move();
  equalize_rotation();
  equalize_scale();
}

/* ----------  тут начинаются слоты для кнопочек ------------ */

void MainWindow::on_pushButton_file_clicked() {

  QString str = QFileDialog::getOpenFileName(0, "Выбрать", "", "*.obj");

  if (str.isEmpty() != true) {
    QFileInfo fileinfo(str);
    this->ui->glwidget->filename = fileinfo.absoluteFilePath();
    ui->label_filename->setWordWrap(true);
    ui->label_filename->setText("Выбран файл:\t" +
                                this->ui->glwidget->filename);

    QByteArray ba = this->ui->glwidget->filename.toLatin1();
    char *file_str = ba.data();

    data_t *newData = (data_t *)calloc(1, sizeof(data_t));

    *newData = readCount(file_str);
    readData(file_str, newData);
    this->ui->glwidget->file_added = 1;

    ui->glwidget->res = newData;

    QString v_n = QString::number(newData->countOfVertexes);
    QString f_n = QString::number(newData->countOfFacets);
    this->ui->label_v_num->setText("Количество вершин:\t" + v_n);
    this->ui->label_f_num->setText("Количество граней:\t" + f_n);

    set_to_default();
    ui->doubleSpinBox_x_move->setValue(0);
    ui->doubleSpinBox_y_move->setValue(0);
    ui->doubleSpinBox_z_move->setValue(0);
    ui->doubleSpinBox_x_rotate->setValue(0);
    ui->doubleSpinBox_y_rotate->setValue(0);
    ui->doubleSpinBox_z_rotate->setValue(0);
    ui->doubleSpinBox_scale->setValue(1);
    ui->glwidget->update();
    ui->glwidget->scale_obj = 1;
  }
}

void MainWindow::on_doubleSpinBox_x_move_valueChanged(double arg1) {
  this->ui->glwidget->X_move_prev = this->ui->glwidget->X_move;
  this->ui->glwidget->X_move = arg1;

  ui->glwidget->Y_move_prev = ui->glwidget->Y_move;
  ui->glwidget->Z_move_prev = ui->glwidget->Z_move;
  equalize_scale();
  equalize_rotation();

  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_y_move_valueChanged(double arg1) {
  this->ui->glwidget->Y_move_prev = this->ui->glwidget->Y_move;
  this->ui->glwidget->Y_move = arg1;

  ui->glwidget->X_move_prev = ui->glwidget->X_move;
  ui->glwidget->Z_move_prev = ui->glwidget->Z_move;
  equalize_scale();
  equalize_rotation();
  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_z_move_valueChanged(double arg1) {
  this->ui->glwidget->Z_move_prev = this->ui->glwidget->Z_move;
  this->ui->glwidget->Z_move = arg1;

  ui->glwidget->Y_move_prev = ui->glwidget->Y_move;
  ui->glwidget->X_move_prev = ui->glwidget->X_move;
  equalize_scale();
  equalize_rotation();
  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_x_rotate_valueChanged(double arg1) {
  arg1 = degree_to_rad(arg1);
  this->ui->glwidget->X_rotate_prev = this->ui->glwidget->X_rotate;
  this->ui->glwidget->X_rotate = arg1;

  ui->glwidget->Y_rotate_prev = ui->glwidget->Y_rotate;
  ui->glwidget->Z_rotate_prev = ui->glwidget->Z_rotate;
  equalize_move();
  equalize_scale();
  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_y_rotate_valueChanged(double arg1) {
  arg1 = degree_to_rad(arg1);
  this->ui->glwidget->Y_rotate_prev = this->ui->glwidget->Y_rotate;
  this->ui->glwidget->Y_rotate = arg1;

  ui->glwidget->X_rotate_prev = ui->glwidget->X_rotate;
  ui->glwidget->Z_rotate_prev = ui->glwidget->Z_rotate;
  equalize_move();
  equalize_scale();
  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_z_rotate_valueChanged(double arg1) {
  arg1 = degree_to_rad(arg1);
  this->ui->glwidget->Z_rotate_prev = this->ui->glwidget->Z_rotate;
  this->ui->glwidget->Z_rotate = arg1;

  ui->glwidget->Y_rotate_prev = ui->glwidget->Y_rotate;
  ui->glwidget->X_rotate_prev = ui->glwidget->X_rotate;
  equalize_move();
  equalize_scale();
  ui->glwidget->update();
}

void MainWindow::on_comboBox_proection_currentIndexChanged(int index) {
  this->ui->glwidget->proection_type = index;
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_comboBox_edge_type_currentIndexChanged(int index) {
  this->ui->glwidget->edge_type = index;
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_pushButton_back_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  equalize_all();
  if (color.isValid()) {
    this->ui->glwidget->back_color = color;
  }
  ui->glwidget->update();
}

void MainWindow::on_comboBox_vert_type_currentIndexChanged(int index) {
  this->ui->glwidget->vert_type = index;
  if (index == 0) {
    this->ui->pushButton_vert_color->setDisabled(true);
    this->ui->horizontalSlider_vert_size->setDisabled(true);
  } else {
    this->ui->pushButton_vert_color->setEnabled(true);
    this->ui->horizontalSlider_vert_size->setEnabled(true);
  }
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_horizontalSlider_vert_size_valueChanged(int value) {
  this->ui->glwidget->vert_size = value;
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_horizontalSlider_edge_thick_valueChanged(int value) {
  this->ui->glwidget->edge_thickness = value;
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_pushButton_edge_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    this->ui->glwidget->edge_color = color;
  }
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_pushButton_vert_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    this->ui->glwidget->vert_color = color;
  }
  equalize_all();
  ui->glwidget->update();
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  if (arg1 <= 0) {
    this->ui->doubleSpinBox_scale->setValue(1);
  } else {
    this->ui->glwidget->scale_obj_prev = this->ui->glwidget->scale_obj;
    this->ui->glwidget->scale_obj = arg1;
  }
  equalize_move();
  equalize_rotation();
  ui->glwidget->update();
}
