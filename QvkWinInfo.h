#ifndef QvkAlsa_H
#define QvkAlsa_H

#include <QObject>
#include "qxtwindowsystem.h"
#include <QDialog>
#include <QMainWindow>

//class QvkWinInfo: public QMainWindow
class QvkWinInfo: public QDialog
{ 
Q_OBJECT
public:
  QvkWinInfo();
  virtual ~QvkWinInfo();

  
public slots:
  QString x();
  QString y();
  QString width();
  QString height();
  QString WinID();
  WId getWinID();

  
private slots: 
   void selectWindow();
   void mousePosition();

   
signals:
  void windowChanged();
  
  
protected:  
  
  
private:
  QTimer *windowTimer;
  QTimer *mouseTimer;
  
  WId lastWinID;
  WId newWinID;
  
  QString myX;
  QString myY;
  QString myWidth;
  QString myHeight;
  void paintEvent(QPaintEvent *event);
  
};

#endif