#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Parser.h"
#include "Scene.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusLabel = new QLabel( this );
    m_statusLabel->setText( "" );
    m_statusLabel->setAlignment( Qt::AlignLeft );
    ui->statusBar->addPermanentWidget( m_statusLabel, 1 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open"), QDir::currentPath( ),tr( "Obj File (*.obj)" ) );
    if (fileName.isEmpty()) {
        return;
    }

    QString all;
    try {
        readData( fileName , all );
    } catch ( const FileError &e ) {
        QMessageBox::information( this, tr( "Information" ), QString::fromUtf8( e.what() ) );
        return;
    } catch ( ... ) {
        QMessageBox::information( this, tr( "Information" ), tr( "Uncaught exception." ) );
        return;
    }

    QList<QVector3D> points;
    QList<QVector3D> indexes;
    Parser parser;

    try {
        parser.parseData( all, points, indexes );
    } catch ( const LogicError &e ) {
        QMessageBox::information( this, tr( "Information" ), QString::fromUtf8( e.what() ) );
        return;
    } catch ( ... ) {
        QMessageBox::information( this, tr( "Information" ), tr( "Uncaught exception." ) );
        return;
    }

    ui->sceneWidget->setPointsAndIndexes( points, indexes );

    m_statusLabel->setText( fileName );
}

void MainWindow::readData(const QString &fileName, QString &all)
throw (FileOpenError, FileReadError)
{
    QFile file( fileName );

    if ( !file.open( QIODevice::ReadOnly ) ) {
        throw FileOpenError( fileName.toStdString( ) );
    }

    QTextStream stream( &file );
    all = stream.readAll( );
    if (stream.status() != QTextStream::Ok) {
        throw FileReadError( fileName.toStdString( ), 0 );
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
