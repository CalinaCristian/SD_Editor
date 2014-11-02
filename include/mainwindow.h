#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollBar>
#include <QTextCursor>
#include <SpacePressEater.h>
#include <backend.h>

namespace Ui {
    class MainWindow;
}

class SpacePressEater;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class SpacePressEater;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendNewText();
    bool selectWordAtCursor();
    void moveCursorAtBeginOfWord();
    QString getText();

    QTextEdit *textArea;
    SpacePressEater *spe;
    Backend *sv;

private:
    Ui::MainWindow *ui;
    static int height;
    static int width;

private slots:
    void Cut();
    void Copy();
    void Paste();
    void Undo();
    void Redo();
};

#endif // MAINWINDOW_H
