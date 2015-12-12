#include "gui.h"
#include <string>
Gui::Gui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Gui::stringToQString()
{
	data = qsData.toLocal8Bit().constData();
}

void Gui::transmitInfo()
{
	//AppObj.dataToBoolean(data);

	//transObj.newInput(AppObj.returnData());

	//transObj.getPayload(0);
	//DLTransmit.assembleFrame(transObj.returnPayload(), 0, transObj.returnMaxIndex());
	//transmit.transmit(DLTransmit.returnPayload());

	//transObj.getPayload(1);
	//DLTransmit.assembleFrame(transObj.returnPayload(), 1, 16);
	//transmit.transmit(DLTransmit.returnPayload());
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
		//transmitInfo();
	}
	ui.textEdit->setFocus();
}

Gui::~Gui()
{
}