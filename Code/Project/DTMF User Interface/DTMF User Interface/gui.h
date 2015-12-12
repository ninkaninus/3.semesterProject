#include <iostream>
#include "Transmitter\Transmitter\Transmitter.h"
#include "Main\Main\ApplicationLayer.h"
#include "Main\Main\DataLinkReceive.h"
#include "Main\Main\DataLinkTransmit.h"
#include "Main\Main\PhysicalReceive.h"
#include "Main\Main\PhysicalTransmit.h"
#include "Main\Main\TransportLayer.h"

#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "ui_gui.h"

class Gui : public QMainWindow
{
	Q_OBJECT

public:
	Gui(QWidget *parent = 0);
	void stringToQString();
	void transmitInfo();
	void showOnGui();
	void commands();
	~Gui();

	private slots:
	void on_sendButton_clicked();
	void on_textEdit_returnPressed();

private:
	ApplicationLayer AppObj;
	TransportLayer transObj;
	DataLinkTransmit DLTransmit;
	DTMF::Transmitter transmit;
	QString qsData;
	string data;
	Ui::GuiClass ui;
};

#endif // GUI_H