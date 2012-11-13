/*
 * TicTaeToeWindow.h
 *
 *  Created on: May 17, 2012
 *      Author: shuheng
 */

#ifndef TICTAETOEWINDOW_H_
#define TICTAETOEWINDOW_H_

#include <gtkmm.h>
#include "TicTacToeControl.h"

class TicTacToeWindow : public Gtk::Window
{
public:
	TicTacToeWindow();
	virtual ~TicTacToeWindow();

private:
	//Child widgets:
	Gtk::VBox m_vbox;
	Gtk::HBox m_hbox;
	TicTacToeControl m_tttcontrol;
	Gtk::Button m_resetbutton;
	Gtk::Button m_aboutbutton;
	Gtk::Button m_changesizebutton;
	Gtk::Label m_status;

	// Signal handlers:
	void on_aboutbutton_clicked();
	void on_gameEnded(int);
	void on_changesizebutton_clicked();
};

#endif /* TICTAETOEWINDOW_H_ */
