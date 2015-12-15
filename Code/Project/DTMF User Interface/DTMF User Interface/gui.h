#include "Main\Main\ApplicationLayer.h"
#include "Main\Main\DataLinkReceive.h"

#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include <QThread>
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
	QString qsData;
	string data;
	Ui::GuiClass ui;
};

#endif // GUI_H
