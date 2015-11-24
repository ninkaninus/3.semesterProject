#include "gui.h"
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <string>
Gui::Gui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Gui::stringtoQString()
{
	data = qsData.toLocal8Bit().constData();
}


Gui::~Gui()
{

}

void Gui::on_textEdit_returnPressed()
{
	on_sendButton_clicked();
}

void Gui::on_sendButton_clicked()
{
	if (ui.textEdit->text() != "")
	{	qsData = ui.textEdit->text();
		ui.textVindue->insertPlainText("Me: ");
		ui.textVindue->insertPlainText(qsData);
		ui.textVindue->insertPlainText("\n");
		ui.textEdit->clear();
		stringtoQString();
		AppObj.dataToBoolean(data);
	}
	ui.textEdit->setFocus();
}

