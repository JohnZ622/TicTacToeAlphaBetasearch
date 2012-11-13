/*
 * TicTacToeWindow.cpp
 *
 *  Created on: May 17, 2012
 *      Author: shuheng
 */

#include "TicTaeToeWindow.h"
#include <gdk/gdk.h>
#include <iostream>

void TicTacToeWindow::on_gameEnded(int status) {
	switch (status)
	{
		case 1 :
			m_status.set_label("Player X has won");
			break;
		case -1 :
			m_status.set_label("Player O has won");
			break;
		case 0 :
			m_status.set_label("Game tied");
			break;
		case -2 :
			m_status.set_label("");
	}
}

TicTacToeWindow::TicTacToeWindow()
: m_resetbutton("Reset"),
  m_aboutbutton("About"),
  m_changesizebutton("Change Size"),
  m_hbox(true),
  m_vbox(false, 8)
{
	set_title("Tic Tac Toe Using Uniformed Search with Pruning");

	// Window geometry setting
	set_border_width(0);
	Gdk::Geometry myGeometry;
	myGeometry.min_width = 200;
	myGeometry.min_height = 250;
	myGeometry.min_aspect = 4.0/5.0;
	myGeometry.max_aspect = 4.0/5.0;
	set_geometry_hints(*this, myGeometry, Gdk::HINT_MIN_SIZE | Gdk::HINT_ASPECT);
	set_default_size(400, 500);

	m_vbox.pack_start(m_tttcontrol, Gtk::PACK_EXPAND_WIDGET);
	m_vbox.pack_start(m_status, Gtk::PACK_SHRINK, 2);
	m_vbox.pack_end(m_hbox, Gtk::PACK_SHRINK, 2);
	m_hbox.pack_start(m_resetbutton);
	m_hbox.pack_start(m_changesizebutton);
	m_hbox.pack_end(m_aboutbutton);


	m_aboutbutton.signal_clicked().connect(sigc::mem_fun(this, &TicTacToeWindow::on_aboutbutton_clicked));
	m_resetbutton.signal_clicked().connect(sigc::mem_fun(m_tttcontrol, &TicTacToeControl::reset));
	m_changesizebutton.signal_clicked().connect(sigc::mem_fun(this, &TicTacToeWindow::on_changesizebutton_clicked));
	m_tttcontrol.signal_game_ended().connect(sigc::mem_fun(this, &TicTacToeWindow::on_gameEnded));
	add(m_vbox);
	show_all_children();


}

void TicTacToeWindow::on_changesizebutton_clicked(){
	// delete m_tttcontrol;
}

void TicTacToeWindow::on_aboutbutton_clicked()
{
Gtk::MessageDialog dialog(*this, "This application is written by Shuheng John Zheng");
dialog.run();
}

TicTacToeWindow::~TicTacToeWindow()
{
}
