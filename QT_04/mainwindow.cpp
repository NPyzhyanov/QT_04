#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>
#include <QString>
#include <QVariant>
#include <memory>
#include <cmath>

#include "converter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    converter = std::make_unique<Converter>();
    
    ui->gb_quantities->setTitle("Величина");
    ui->rb_q1->setText(QString::fromStdString(converter->get_quantity_name(0)));
    ui->rb_q2->setText(QString::fromStdString(converter->get_quantity_name(1)));
    ui->rb_q3->setText(QString::fromStdString(converter->get_quantity_name(2)));
    ui->gb_quantities->setEnabled(false);
    
    QPixmap eq_pm("../icons/equals.png");
    equals_icon.addPixmap(eq_pm);
    QPixmap sw_pm("../icons/swap.png");
    swap_icon.addPixmap(sw_pm);
    ui->pb_swap->setCheckable(true);
    ui->pb_swap->setIcon(swap_icon);
    ui->le_output->setReadOnly(true);
    set_units_zone_enabled(false);
    
    ui->cb_in_prefix->addItems(prefixes);
    ui->cb_in_prefix->setCurrentText("");
    ui->cb_out_prefix->addItems(prefixes);
    ui->cb_out_prefix->setCurrentText("");
    
    ui->tl_norobot_header->setText("Подтвердите, что вы не робот");
    ui->pb_norobot->setText("Я не робот");
    ui->bar_norobot_indicator->setMinimum(0);
    ui->bar_norobot_indicator->setMaximum(10);
    ui->bar_norobot_indicator->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_units_zone_enabled(bool state)
{
    ui->le_input->setEnabled(state);
    ui->cb_in_prefix->setEnabled(state);
    ui->cb_in_unit->setEnabled(state);
    ui->pb_swap->setEnabled(state);
    ui->le_output->setEnabled(state);
    ui->cb_out_prefix->setEnabled(state);
    ui->cb_out_unit->setEnabled(state);
}

void MainWindow::on_pb_norobot_clicked()
{
    ui->bar_norobot_indicator->setValue(ui->bar_norobot_indicator->value() + 1);
    
    if (ui->bar_norobot_indicator->value() >= ui->bar_norobot_indicator->maximum())
    {
        norobot_verification_finished(!ui->gb_quantities->isEnabled());
        ui->pb_norobot->setText("Я не робот");
        ui->bar_norobot_indicator->setValue(0);
    }
    else if (ui->bar_norobot_indicator->value() == ui->bar_norobot_indicator->maximum() / 2)
    {
        ui->pb_norobot->setText("Я НЕ РОБОТ");
    }
    else
    {
        ui->pb_norobot->setText(ui->pb_norobot->text().append("!"));
    }
}

void MainWindow::norobot_verification_finished(bool first_verification)
{
    if (!first_verification)
    {
        return;
    }
    ui->gb_quantities->setEnabled(true);
    set_units_zone_enabled(true);
    
    ui->tl_norobot_header->setText("Поздравляем! Похоже, вы не робот.");
}


void MainWindow::on_pb_swap_toggled(bool checked)
{
    if (checked)
    {
        ui->pb_swap->setIcon(equals_icon);
    }
    else
    {
        ui->pb_swap->setIcon(swap_icon);
    }
    
    QString current_output = ui->le_output->text();
    int output_prefix_index = ui->cb_out_prefix->currentIndex();
    int output_unit_index = ui->cb_out_unit->currentIndex();
    
    ui->cb_out_prefix->setCurrentIndex(ui->cb_in_prefix->currentIndex());
    ui->cb_out_unit->setCurrentIndex(ui->cb_in_unit->currentIndex());
    
    ui->le_input->setText(current_output);
    ui->cb_in_prefix->setCurrentIndex(output_prefix_index);
    ui->cb_in_unit->setCurrentIndex(output_unit_index);
    
    update_result();
}

void MainWindow::update_combo_boxes(const int &order_number)
{
    ui->cb_in_unit->clear();
    ui->cb_out_unit->clear();
    QStringList list;
    std::vector<std::string> units = converter->get_units_names(order_number);
    for (auto it = units.begin(); it != units.end(); it++)
    {
        list.append(QString::fromStdString(*it));
    }
    
    ui->cb_in_unit->addItems(list);
    ui->cb_out_unit->addItems(list);
}

void MainWindow::on_rb_q1_clicked()
{
    update_combo_boxes(0);
}

void MainWindow::on_rb_q2_clicked()
{
    update_combo_boxes(1);
}

void MainWindow::on_rb_q3_clicked()
{
    update_combo_boxes(2);
}

void MainWindow::update_result()
{
    int chosen_button = check_buttons();
    int chosen_source_unit = ui->cb_in_unit->currentIndex();
    int chosen_destination_unit = ui->cb_out_unit->currentIndex();
    int chosen_source_prefix = ui->cb_in_prefix->currentIndex();
    int chosen_destination_prefix = ui->cb_out_prefix->currentIndex();
    
    bool converted_to_double = false;
    double user_input = (ui->le_input->text()).toDouble(&converted_to_double);
    
    if (chosen_button == -1 || chosen_source_unit == -1 || chosen_destination_unit == -1 || chosen_source_prefix == -1 || chosen_destination_prefix == -1 || !converted_to_double)
    {
        ui->le_output->setText("");
        return;
    }
    
    double conversion_rate = converter->get_conversion_rate(chosen_button, chosen_source_unit, chosen_destination_unit);
    int exponent = prefix_index_to_exponent(ui->cb_in_prefix->currentIndex()) - prefix_index_to_exponent(ui->cb_out_prefix->currentIndex());
    
    ui->le_output->setText(QString::number(conversion_rate * user_input * pow(10, exponent)));
}

unsigned int MainWindow::check_buttons()
{
    if (ui->rb_q1->isChecked()) { return 0; }
    if (ui->rb_q2->isChecked()) { return 1; }
    if (ui->rb_q3->isChecked()) { return 2; }
    return -1;
}

int MainWindow::prefix_index_to_exponent(int index)
{
    switch (index)
    {
    case 0: return 12;
    case 1: return 9;
    case 2: return 6;
    case 3: return 3;
    case 4: return 0;
    case 5: return -3;
    case 6: return -6;
    case 7: return -9;
    case 8: return -12;
    default: break;
    }
    return -999;
}

void MainWindow::on_le_input_editingFinished()
{
    update_result();
}

void MainWindow::on_cb_in_prefix_currentIndexChanged(int index)
{
    update_result();
}

void MainWindow::on_cb_in_unit_currentIndexChanged(int index)
{
    update_result();
}

void MainWindow::on_cb_out_prefix_currentIndexChanged(int index)
{
    update_result();
}

void MainWindow::on_cb_out_unit_currentIndexChanged(int index)
{
    update_result();
}

