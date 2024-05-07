#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <memory>
#include "converter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pb_norobot_clicked();
    void on_pb_swap_toggled(bool checked);
    void on_rb_q1_clicked();
    void on_rb_q2_clicked();
    void on_rb_q3_clicked();
    void on_le_input_editingFinished();
    void on_cb_in_prefix_currentIndexChanged(int index);
    void on_cb_in_unit_currentIndexChanged(int index);
    void on_cb_out_prefix_currentIndexChanged(int index);
    void on_cb_out_unit_currentIndexChanged(int index);
    
private:
    Ui::MainWindow *ui;
    
    QIcon equals_icon;
    QIcon swap_icon;
    
    std::unique_ptr<Converter> converter = nullptr;
    
    void set_units_zone_enabled(bool state);
    void norobot_verification_finished(bool first_verification);
    void update_combo_boxes(const int &order_number);
    void update_result();
    unsigned int check_buttons();
    int prefix_index_to_exponent(int index);
    
    const QStringList prefixes = {
        u8"\u00b710\u00b9\u00b2 (тера)",
        u8"\u00B710\u2079 (гига)",
        u8"\u00B710\u2076 (мега)",
        u8"\u00B710\u00b3 (кило)",
        "",
        u8"\u00B710\u207b\u00b3 (милли)",
        u8"\u00B710\u207b\u2076 (микро)",
        u8"\u00B710\u207b\u2079 (нано)",
        u8"\u00B710\u207b\u00b9\u00b2 (пико)"
    };
};
#endif // MAINWINDOW_H
