#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QAction *newAct, *openAct, *saveAct, *saveAsAct, *printAct, *exitAct;
    QAction *undoAct, *redoAct, *cutAct, *copyAct, *pasteAct;
    QAction *wordWrapAct, *hideToolAct;
    QAction *aboutAct;
    QMenu *fileMenu, *editMenu, *viewMenu, *helpMenu;
    QString curFile;
    QTextEdit *text;
    QToolBar *fileToolBar, *editToolBar, *findToolBar;

    //Find stuff
    QAction *findAct;
    QDockWidget *doc;
    QLineEdit *findText, *replaceText;
    QPushButton *findNextButton, *findPrevButton, *replaceThisButton, *replaceAllButton;
    QHBoxLayout *findButtonLayout, *replaceButtonLayout;
    QVBoxLayout *findLayout;
    QWidget *findWidget;

public:
    MainWindow();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;

private slots:
    void newFile();
    void openFile();
    bool save();
    bool saveAs();
    void documentWasModified();
    void printFile();
    void wordWrap();
    void about();
    void hideToolBar();
    void findShow();
    void findNext();
    void findPrev();
    void replaceThis();
    void replaceAll();

private:
    void createToolBar();
    void createStatusBar();
    void createMenu();
    void createAction();
    void createDockWidget();
    void loadFile(const QString&);
    bool maybeSave();
    bool saveFile(const QString&);
    void setCurrentFile(const QString&);
};

#endif // MAINWINDOW_H
