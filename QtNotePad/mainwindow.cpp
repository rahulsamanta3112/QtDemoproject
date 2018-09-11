#include "mainwindow.h"
#include "ui_mainwindow.h"

// Rahul Added ...

#include<QTextStream>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>

// For  Font ........
#include<QFontDialog>
#include<QFont>

// For Color .....
#include<QColorDialog>
#include<QColor>

// For Print ..
#include<QPrinter>
#include<QPrintDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
   file_path = "";
   ui->textEdit->setText("");

}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name =  QFileDialog::getOpenFileName(this,"Open File");
    QFile file (file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
          QMessageBox::warning(this,"..","File Is not Open");

          return;
    }

    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    //QString file_name =  QFileDialog::getSaveFileName(this,"Open File");
    QFile file (file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
          QMessageBox::warning(this,"..","File Is not Open");

          return;
    }

    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
        ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
          ui->textEdit->copy();
}

void MainWindow::on_actionPsate_triggered()
{
       ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name =  QFileDialog::getSaveFileName(this,"Open File");
    QFile file (file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
          QMessageBox::warning(this,"..","File Is not Open");

          return;
    }

    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionundo_triggered()
{
          ui->textEdit->undo();
}

void MainWindow::on_actionabout_triggered()
{
    QString about_text ;
    about_text ="Author : Embdes";
    about_text+= "Date : 05/09/2018";
    about_text+= "(C) QTNotePad (R)";
    QMessageBox ::about(this,"About QTNotePad",about_text);
}

void MainWindow::on_actionFont_triggered()
{
      bool ok ;
       QFont font = QFontDialog::getFont(&ok,this);
       if(ok){
              ui->textEdit->setFont(font);
       }
       else return;
}

void MainWindow::on_actionColor_triggered()
{
       QColor color = QColorDialog::getColor(Qt::white,this,"Chose Color");

       if (color.isValid()){

          ui->textEdit->setTextColor(color);

       }
}

void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Chose Color");

    if (color.isValid()){

       ui->textEdit->setTextBackgroundColor(color);

    }
}

void MainWindow::on_actionWindow_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Chose Color");

    if (color.isValid()){

       ui->textEdit->setPalette(QPalette(color));

    }
}

void MainWindow::on_actionPrint_triggered()
{
     QPrinter printer;
     printer.setPrinterName("name");
     QPrintDialog dialog (&printer,this);
     if(dialog.exec() == QDialog::Rejected)
         return;
     ui->textEdit->print(&printer);
}
