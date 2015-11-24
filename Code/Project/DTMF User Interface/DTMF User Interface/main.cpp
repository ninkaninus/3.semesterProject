#include "gui.h"

int main(int argc, char *argv[]){
	QApplication program(argc, argv);
	Gui gui;
	gui.show();
	return program.exec();
}
