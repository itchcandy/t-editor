#include <QtPrintSupport>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    text = new QTextEdit();
    setCentralWidget(text);
    createAction();
    createMenu();
    createToolBar();
    createStatusBar();
    createDockWidget();

    connect(text->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    setCurrentFile("");
}

void MainWindow::createAction()
{
    //Filemenu actions
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip("Create a new file");
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an existing file");
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip("Save the document to disk");
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip("Save the document under a new name");
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    printAct = new QAction(tr("&Print"), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip("Print the document");
    connect(printAct, SIGNAL(triggered()), this, SLOT(printFile()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("Exit Application");
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    //Editmenu actions
    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut selected text"));
    connect(cutAct, SIGNAL(triggered()), text, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy selected text"));
    connect(copyAct, SIGNAL(triggered()), text, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste text from clipboard"));
    connect(pasteAct, SIGNAL(triggered()), text, SLOT(paste()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    connect(undoAct, SIGNAL(triggered()), text, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    connect(redoAct, SIGNAL(triggered()), text, SLOT(redo()));

    //Viewmenu actions
    wordWrapAct = new QAction(tr("&Word wrap"), this);
    wordWrapAct->setStatusTip(tr("Toggle word wrap"));
    connect(wordWrapAct, SIGNAL(triggered()), this, SLOT(wordWrap()));

    hideToolAct = new QAction(tr("Toggle &Toolbar"), this);
    hideToolAct->setStatusTip(tr("Toggle Toolbar visibility"));
    connect(hideToolAct, SIGNAL(triggered()), this, SLOT(hideToolBar()));

    //Find pushbuttons
    findAct = new QAction(tr("&Find"), this);
    findAct->setShortcuts(QKeySequence::Find);
    findAct->setStatusTip(tr("Find in document"));
    connect(findAct, SIGNAL(triggered()), this, SLOT(findShow()));

    findNextButton = new QPushButton(tr("Next"));
    connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNext()));

    findPrevButton = new QPushButton(tr("Prev"));
    connect(findPrevButton, SIGNAL(clicked()), this, SLOT(findPrev()));

    replaceThisButton = new QPushButton(tr("Replace"));
    connect(replaceThisButton, SIGNAL(clicked()), this, SLOT(replaceThis()));

    replaceAllButton = new QPushButton(tr("All"));
    connect(replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));

    //Helpmenu actions
    aboutAct = new QAction(tr("&Help"), this);
    aboutAct->setStatusTip(tr("About T editor"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createDockWidget()
{
    findText = new QLineEdit(this);
    findText->setPlaceholderText(tr("Find"));
    replaceText = new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace"));
    findButtonLayout = new QHBoxLayout();
    findButtonLayout->addWidget(findNextButton);
    findButtonLayout->addWidget(findPrevButton);
    replaceButtonLayout = new QHBoxLayout();
    replaceButtonLayout->addWidget(replaceThisButton);
    replaceButtonLayout->addWidget(replaceAllButton);

    doc = new QDockWidget();
    findWidget = new QWidget(doc);
    findLayout = new QVBoxLayout(findWidget);
    findLayout->addWidget(findText);
    findLayout->addLayout(findButtonLayout);
    findLayout->addWidget(replaceText);
    findLayout->addLayout(replaceButtonLayout);
    findLayout->setAlignment(Qt::AlignTop);
    findWidget->setLayout(findLayout);
    doc->setWidget(findWidget);
    addDockWidget(Qt::RightDockWidgetArea, doc);
    doc->hide();
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(wordWrapAct);
    viewMenu->addAction(hideToolAct);
    viewMenu->addAction(findAct);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About T editor"), tr("T editor (or simply \'T\') is a minimal text editor"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::documentWasModified()
{
    setWindowModified(text->document()->isModified());
}

void MainWindow::findNext()
{
    text->find(findText->text());
}

void MainWindow::findPrev()
{
    text->find(findText->text(), QTextDocument::FindBackward);
}

void MainWindow::findShow()
{
    doc->show();
}

void MainWindow::hideToolBar()
{
    if(fileToolBar->isVisible())
        fileToolBar->hide();
    else
        fileToolBar->show();
}

void MainWindow::loadFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, tr("Application"), tr("Cannot read file %1 : %2").arg(filename).arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    text->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    setCurrentFile(filename);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::maybeSave()
{
    if(text->document()->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"), tr("This document has been modified. Do want to save the changes?"), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        if(ret == QMessageBox::Save)
            return save();
        else if(ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::newFile()
{
    if(maybeSave()){
        text->clear();
        setCurrentFile("");
    }

}

void MainWindow::openFile()
{
    if(maybeSave()){
        QString filename = QFileDialog::getOpenFileName(this);
        if(!filename.isEmpty())
            loadFile(filename);
    }

}

void MainWindow::printFile()
{
    if(!save())
        return;
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintDialog *printDialog = new QPrintDialog(&printer, text);
    printDialog->setWindowTitle(tr("Print Document"));
    if(printDialog->exec()==QDialog::Accepted)
        text->print(&printer);
    delete printDialog;
}

void MainWindow::replaceThis()
{
    if(!QString::compare(text->textCursor().selectedText(), findText->text(), Qt::CaseInsensitive)){
        text->insertPlainText(replaceText->text());
    }
}

void MainWindow::replaceAll()
{
    if(!QString::compare(text->textCursor().selectedText(), findText->text(), Qt::CaseInsensitive)){
        text->insertPlainText(replaceText->text());
    }
    while(text->find(findText->text())){
        text->insertPlainText(replaceText->text());
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
        return saveAs();
    return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setWindowModality(Qt::WindowModal);
    QStringList files;
    if(dialog.exec()){
        files = dialog.selectedFiles();
    }
    else
        return false;
    return saveFile(files.at(0));
}

bool MainWindow::saveFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, tr("Application"), tr("Cannot write to file %1 : %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << text->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    setCurrentFile(filename);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &filename)
{
    curFile = filename;
    text->document()->setModified(false);
    setWindowModified(false);

    QString showname = curFile;
    if(filename.isEmpty()){
        showname = "untitled";
    }
    setWindowFilePath(showname);
}

void MainWindow::wordWrap()
{
    if(text->wordWrapMode()==QTextOption::NoWrap)
        text->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    else
        text->setWordWrapMode(QTextOption::NoWrap);
}

MainWindow::~MainWindow()
{

}
