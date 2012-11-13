/*
 * TicTaeToeSearch.cpp
 *
 *  Created on: May 17, 2012
 *      Author: shuheng
 */

#include <gtkmm.h>
#include "TicTaeToeWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  TicTacToeWindow mainWindow;

  int a[] = {7};
  int b[] = {4};



  Gtk::Main::run(mainWindow);


  return EXIT_SUCCESS;
}
