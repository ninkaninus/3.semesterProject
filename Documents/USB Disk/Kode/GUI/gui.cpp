#include "gui.h"
#include <string>
Gui::Gui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.textEdit->setFocus();
}

void Gui::stringToQString()
{
	data = qsData.toLocal8Bit().constData();
}

void Gui::transmitInfo()
{
	//AppObj.send(data);
}

void Gui::showOnGui()
{
		qsData = ui.textEdit->text();
		ui.textVindue->insertPlainText("Me: ");
		ui.textVindue->insertPlainText(qsData);
		ui.textVindue->insertPlainText("\n");
		ui.textEdit->clear();
}

void Gui::commands()
{
	stringToQString();
}

void Gui::on_textEdit_returnPressed()
{
	on_sendButton_clicked();
}

void Gui::on_sendButton_clicked()
{
	commands();
	if (ui.textEdit->text() != "")
	{
		showOnGui();
		transmitInfo();
	}
	ui.textEdit->setFocus();
}

Gui::~Gui()
{
}