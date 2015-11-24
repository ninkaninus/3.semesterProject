#include <iostream>
#include <ApplikationsLayer.h>
#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "ui_gui.h"

class Gui : public QMainWindow
{
	Q_OBJECT

public:
	Gui(QWidget *parent = 0);
	void stringtoQString();
	~Gui();

	private slots:
	void on_sendButton_clicked();
	void on_textEdit_returnPressed();

private:
	ApplikationsLayer AppObj;
	QString qsData;
	std::string data;
	Ui::GuiClass ui;
};

#endif // GUI_H
