
#include "QvkMail.h" 

using namespace std;

QvkMail::QvkMail()
{
  
}


QvkMail::QvkMail( QWidget *object )
{
  (void)object;
  
  newDialog = new QDialog;
  newDialog->setModal( true );

  myUiMailDialog.setupUi( newDialog );
  newDialog->show();  
  
  connect( myUiMailDialog.sendPushButton, SIGNAL( clicked() ), this, SLOT( selection() ) );
  connect( myUiMailDialog.cancelPushButton, SIGNAL( clicked() ), this, SLOT( closeDialog() ) ) ;

  
/*  
  dialog = new QDialog( object );
  dialog->setFixedSize( 470, 200 );
  
  QFont qfont = dialog->font();
  qfont.setPixelSize( 12 );
  dialog->setFont( qfont );
  
  QLabel* label = new QLabel( dialog );
  label->setText("");
  label->setGeometry( QRect( 20, 30, 150, 150) );
  label->setAlignment( Qt::AlignCenter );
  label->show();
  QImage* qImage = new QImage( ":pictures/sem_soc_net.png" );
  label->setPixmap( QPixmap::fromImage( *qImage, Qt::AutoColor ) );
  label->setScaledContents( true );
  
  mailRadioButton = new QRadioButton( dialog );
  mailRadioButton->setGeometry( QRect( 200, 60, 200, 21 ) );
  mailRadioButton->setText( tr( "Mail last Video" ) );
  mailRadioButton->setChecked( true );
  
  mailSelectedRadioButton = new QRadioButton( dialog );
  mailSelectedRadioButton->setGeometry( QRect( 200, 90, 300, 21 ) );
  mailSelectedRadioButton->setText( tr( "Mail one or more selected Video" ) );
  
  QPushButton * sendPushbutton = new QPushButton( dialog );
  sendPushbutton->setGeometry( 290, 170, 80, 30 );
  sendPushbutton->setText( tr( "Send" ) );
  sendPushbutton->show();
  connect( sendPushbutton, SIGNAL( clicked() ), this, SLOT( selection() ) );
  
  QPushButton * closePushbutton = new QPushButton( dialog );
  closePushbutton->setGeometry( 380, 170, 80, 30 );
  closePushbutton->setText( tr( "Close" ) );
  closePushbutton->show();
  connect( closePushbutton, SIGNAL( clicked() ), this, SLOT( closeDialog() ) ) ;
  
  dialog->exec();
*/  
}


QvkMail::~QvkMail()
{
}


void QvkMail::closeDialog()
{
  newDialog->close();
}


void QvkMail::selection()
{
  if ( myUiMailDialog.mailRadioButton->isChecked() )
    startMailClientWithLastFile( lastMovie() );

  if ( myUiMailDialog.mailSelectedRadioButton->isChecked() )
    startMailClientWithSelectedFiles( selectedMail() );
}


void QvkMail::startMailClientWithLastFile( QString file )
{
  if ( file > "" )
  {
    // The body String like not Space
    QString bodyString = tr( "You find the Video as attachment" );
  
    QString processString = "xdg-email --utf8 --attach " + file + " --body \"" + bodyString + "\"";
    //QString processString = "xdg-email --utf8 --attach \""  + file + "\"" + " --body \"" + bodyString + "\"";

    qDebug() << "[vokoscreen]" << "startMailClientWithLastFile:" << processString;
  
    QProcess Process;
    Process.startDetached( processString );
    Process.close();
  }

  newDialog->close();
}


void QvkMail::startMailClientWithSelectedFiles( QStringList fileList )
{
   // The body String like not Space
  QString bodyString = tr( "You find the Video as attachment" );

  QString files;
  for ( int i = 1; i <= fileList.count(); i++ )
  {
    files = files + " --attach ";
    files = files + fileList[ i - 1 ] ;
  }
  
  if ( not fileList.empty())
  {
    QString processString = "xdg-email --utf8" + files + " --body \"" + bodyString + "\"";
  
    qDebug() << "[vokoscreen]" << "startMailClientWithSelectedFiles:" << processString;
  
    QProcess Process;
    Process.startDetached( processString );
    Process.close();
  }
  
  newDialog->close();
}


QString QvkMail::lastMovie()
{
#ifdef QT4
  QDir dir( QDesktopServices::storageLocation( QDesktopServices::MoviesLocation ) );
#endif
#ifdef QT5
  QDir dir( QStandardPaths::writableLocation( QStandardPaths::MoviesLocation ) );
#endif
  
  QStringList filters;
  filters << "vokoscreen*";
  QStringList List = dir.entryList( filters, QDir::Files, QDir::Time );
  if ( List.isEmpty() )
     return "";
  else
     return dir.filePath( List.first() );
}


QStringList QvkMail::selectedMail()
{
#ifdef QT4
  QString a = QDesktopServices::storageLocation( QDesktopServices::MoviesLocation );
  
  QStringList files = QFileDialog::getOpenFileNames( newDialog,
                                                     tr( "Select one or more files" ),
                                                     QDesktopServices::storageLocation( QDesktopServices::MoviesLocation ) , 
                                                     "*.*" );
#endif

#ifdef QT5
  QString a = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
  
  QStringList files = QFileDialog::getOpenFileNames( newDialog,
                                                     tr( "Select one or more files" ),
                                                     QStandardPaths::writableLocation( QStandardPaths::MoviesLocation ) , 
                                                     "*.*" );
#endif
  
  return files;
}
