//-------------------------------------------
//pagestaff.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//员工信息录入界面逻辑
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelmanagement.h"
#include "ui_hotelmanagement.h"

#include <QMessageBox>

//初始化员工信息管理界面
void HotelManagement::initPageStaff()
{
    ui->comboBoxSexPgS1->addItem("男");
    ui->comboBoxSexPgS1->addItem("女");
    ui->comboBoxSexPgS2->addItem("男");
    ui->comboBoxSexPgS2->addItem("女");

    ui->editConfirmPasswdPgS1->setEchoMode(QLineEdit::Password);
    ui->editConfirmPasswdPgS2->setEchoMode(QLineEdit::Password);
    ui->editPasswdPgS1->setEchoMode(QLineEdit::Password);
    ui->editPasswdPgS2->setEchoMode(QLineEdit::Password);
    ui->editUserNamePgS1->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));

    ui->dateEditBirthPgS1->setDisplayFormat("yyyy/MM/dd");
    ui->dateEditBirthPgS2->setDisplayFormat("yyyy/MM/dd");

    updatePageStaff();
}

//更新员工管理界面
void HotelManagement::updatePageStaff()
{
    m_staffService->updateStaffList();
    QVector<QMap<QString, QString>> staffList = m_staffService->getStaffList();

    ui->comboBoxUserNamePgS2->clear();

    for(int i  = 0; i < staffList.size(); i++)
    {
        ui->comboBoxUserNamePgS2->addItem(staffList[i]["userName"]);
    }

    ui->comboBoxUserNamePgS2->setCurrentIndex(-1);

    ui->editNamePgS2->clear();
    ui->editEmailPgS2->clear();
    ui->editPhonePgS2->clear();
    ui->editPasswdPgS2->clear();
    ui->editAddressPgS2->clear();
    ui->editConfirmPasswdPgS2->clear();
}

//重置按钮点击事件
void HotelManagement::on_btnResetPgS1_clicked()
{
    ui->editNamePgS1->clear();
    ui->editEmailPgS1->clear();
    ui->editPhonePgS1->clear();
    ui->editPasswdPgS1->clear();
    ui->editAddressPgS1->clear();
    ui->editUserNamePgS1->clear();
    ui->editConfirmPasswdPgS1->clear();
}

//用户名下拉菜单选择事件
void HotelManagement::on_comboBoxUserNamePgS2_activated(const QString &arg1)
{
    QVector<QMap<QString, QString>> staffList = m_staffService->getStaffList();
    for(int i  = 0; i < staffList.size(); i++)
    {
        if(staffList[i]["userName"] == arg1)
        {
            ui->editNamePgS2->setText(staffList[i]["name"]);
            ui->editEmailPgS2->setText(staffList[i]["email"]);
            ui->editPhonePgS2->setText(staffList[i]["phoneNumber"]);
            ui->editPasswdPgS2->setText(staffList[i]["passwd"]);
            ui->editAddressPgS2->setText(staffList[i]["address"]);
            ui->editConfirmPasswdPgS2->setText(staffList[i]["passwd"]);
            QString birthday = staffList[i]["birthday"];

            QStringList list = birthday.split('/');
            if(!birthday.isEmpty())
                ui->dateEditBirthPgS2->setDate(QDate(list[0].toInt(),list[1].toInt(),list[2].toInt()));
        }
    }
}

//登记按钮点击事件
void HotelManagement::on_btnRegisterPgS1_clicked()
{
    QMap<QString, QString> staff;
    staff["userName"] = ui->editUserNamePgS1->text();
    staff["passwd"] = ui->editPasswdPgS1->text();
    staff["name"] = ui->editNamePgS1->text();
    staff["phoneNumber"] = ui->editPhonePgS1->text();
    staff["sex"] = ui->comboBoxSexPgS1->currentText();
    staff["birthday"] = ui->dateEditBirthPgS1->text();
    staff["address"] = ui->editAddressPgS1->text();
    staff["email"] = ui->editEmailPgS1->text();

    if(staff["userName"] != "" && staff["passwd"] != "" && staff["name"] != "" && staff["phoneNumber"] != ""
            && staff["sex"] != "" && staff["birthday"] != ""&& staff["address"] != "" && staff["email"] != "")
    {
        if(staff["passwd"].size() < 8)
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("密码长度太短"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
            return;
        }
        if(ui->editPasswdPgS1->text() == ui->editConfirmPasswdPgS1->text())
        {
            bool ok = m_staffService->addStaff(staff);
            if(!ok)
            {
                QMessageBox::information(this,
                    tr("提示"),
                    tr("员工注册失败"),
                    QMessageBox::Ok | QMessageBox::Cancel,
                    QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(this,
                    tr("提示"),
                    tr("注册成功"),
                    QMessageBox::Ok | QMessageBox::Cancel,
                    QMessageBox::Ok);
                on_btnResetPgS1_clicked();
                updatePageStaff();
            }
        }
        else
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("两次密码输入不一致"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("信息输入不完整"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
}

//删除员工按钮点击事件
void HotelManagement::on_btnDeletePgS2_clicked()
{
    QString userName = ui->comboBoxUserNamePgS2->currentText();

    if(userName == "admin")
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("管理员账户无法删除"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }

    bool ok = m_staffService->isExist(userName);
    if(ok)
    {
        ok = m_staffService->deleteStaff(userName);
        if(ok)
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("删除成功"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
            updatePageStaff();
        }
        else
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("删除失败"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("该员工不存在"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
}

//修改员工信息按钮点击事件
void HotelManagement::on_btnChangePgS2_clicked()
{
    QMap<QString, QString> staff;
    staff["userName"] = ui->comboBoxUserNamePgS2->currentText();
    staff["passwd"] = ui->editPasswdPgS2->text();
    staff["name"] = ui->editNamePgS2->text();
    staff["phoneNumber"] = ui->editPhonePgS2->text();
    staff["sex"] = ui->comboBoxSexPgS2->currentText();
    staff["birthday"] = ui->dateEditBirthPgS2->text();
    staff["address"] = ui->editAddressPgS2->text();
    staff["email"] = ui->editEmailPgS2->text();

    if(staff["userName"] != "" && staff["passwd"] != "" && staff["name"] != "" && staff["phoneNumber"] != ""
            && staff["sex"] != "" && staff["birthday"] != ""&& staff["address"] != "" && staff["email"] != "")
    {
        if(staff["passwd"].size() < 8)
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("密码长度太短"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
            return;
        }
        if(ui->editPasswdPgS1->text() == ui->editConfirmPasswdPgS1->text())
        {
            m_staffService->deleteStaff(staff["userName"]);
            bool ok = m_staffService->addStaff(staff);
            if(!ok)
            {
                QMessageBox::information(this,
                    tr("提示"),
                    tr("员工信息修改失败"),
                    QMessageBox::Ok | QMessageBox::Cancel,
                    QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(this,
                    tr("提示"),
                    tr("修改成功"),
                    QMessageBox::Ok | QMessageBox::Cancel,
                    QMessageBox::Ok);
                updatePageStaff();
            }
        }
        else
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("两次密码输入不一致"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("信息输入不完整"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
}

//员工信息搜索框回车事件
void HotelManagement::on_editSearchStaff_returnPressed()
{
    QString item = ui->editSearchStaff->text();

    QVector<QMap<QString, QString>> list = m_staffService->searchStaff(item);

    if(list.empty())
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("未找到结果"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
    else
    {
        showStaff(list);
    }
}

//根据list显示staff表
void HotelManagement::showStaff(QVector<QMap<QString, QString>> &list)
{
    m_modelStaff = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("姓名,用户名,手机号,性别,生日,地址,邮箱").simplified().split(",");
    m_modelStaff->setHorizontalHeaderLabels(labels);

    //定义item
    QStandardItem* item;
    for(int i = 0;i < list.size();i++){
        item = new QStandardItem(list[i]["name"]);
        m_modelStaff->setItem(i,0,item);
        item = new QStandardItem(list[i]["userName"]);
        m_modelStaff->setItem(i,1,item);
        item = new QStandardItem(list[i]["phoneNumber"]);
        m_modelStaff->setItem(i,2,item);
        item = new QStandardItem(list[i]["sex"]);
        m_modelStaff->setItem(i,3,item);
        item = new QStandardItem(list[i]["birthday"]);
        m_modelStaff->setItem(i,4,item);
        item = new QStandardItem(list[i]["address"]);
        m_modelStaff->setItem(i,5,item);
        item = new QStandardItem(list[i]["email"]);
        m_modelStaff->setItem(i,6,item);
    }


    ui->tableViewStaff->setModel(m_modelStaff);
    ui->tableViewStaff->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewStaff->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#455364;}");
    ui->tableViewStaff->verticalHeader()->hide();
    ui->tableViewStaff->show();
}
