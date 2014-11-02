#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SpacePressEater.h"

#include <iostream>

int MainWindow::height = 640;
int MainWindow::width = 480;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SD editor");
    this->resize(this->height, this->width);

    sv = new Backend();

    //Cut button
    QPushButton *cut = new QPushButton("cut", this);
    cut->setGeometry(1, 16, 35, 25);
    connect(cut, SIGNAL(clicked()), this, SLOT(Cut()));

    //Copy button
    QPushButton *copy = new QPushButton("copy", this);
    copy->setGeometry(37, 16, 35, 25);
    connect(copy, SIGNAL(clicked()), this, SLOT(Copy()));

    //Paste button
    QPushButton *paste = new QPushButton("paste", this);
    paste->setGeometry(73, 16, 35, 25);
    connect(paste, SIGNAL(clicked()), this, SLOT(Paste()));

    //Undo button
    QPushButton *undo = new QPushButton("undo", this);
    undo->setGeometry(108, 16, 35, 25);
    connect(undo, SIGNAL(clicked()), this, SLOT(Undo()));

    //Redo button
    QPushButton *redo = new QPushButton("redo", this);
    redo->setGeometry(144, 16, 35, 25);
    connect(redo, SIGNAL(clicked()), this, SLOT(Redo()));

    //Text area
    this->textArea = new QTextEdit(this);
    this->textArea->setGeometry(1, 50, 638, 429);

    // SpacePressEater
    this->spe = new SpacePressEater(this);
    textArea->installEventFilter(this->spe);
}

QString MainWindow::getText() {
    QString text = this->textArea->toPlainText();
    return text;
}

void MainWindow::moveCursorAtBeginOfWord() {
    QTextCursor cursor = this->textArea->textCursor();
    cursor.setPosition(0);
}

// Function that gets called each time we get a space_button press
// Sends to the backend the last piece of added text
void MainWindow::sendNewText()
{
    const QString text = this->textArea->toPlainText();
    int start = text.lastIndexOf(' ', this->textArea->textCursor().position() - 2) + 1;

    if (this->textArea->textCursor().position() == 1)
        start = 0;

    int len = text.indexOf(' ', start + 1) - start;
    len = this->textArea->textCursor().position() - 1 - start;

    sv->Add(start, text.mid(start, len).toUtf8().constData());
}

bool MainWindow::selectWordAtCursor()
{
    int old_pos = -1;
    const QString text = this->textArea->toPlainText();
    QTextCursor cursor = this->textArea->textCursor();

    // Don't erase the first word
    old_pos = cursor.position();
    cursor.movePosition(QTextCursor::Left);

    // We're on the first position in text, don't select anything
    if (old_pos == cursor.position()) {
        return false;
    }

    // Use StartOfWord and EndOfWord selection only when we have
    // a valid word (lenght > 0)
    if (cursor.position() - 1 >= -1 && ' ' != text.at(cursor.position() - 1)) {

        // Position the cursor
        cursor.movePosition(QTextCursor::StartOfWord);
        cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    }

    // We should select only words that have 1 space after them
    // (That have been submitted already)
    old_pos = cursor.position();
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    std::cout << cursor.anchor() << " " << cursor.position() << " \n";

    if (old_pos == cursor.position()) {
        return false;
    }


    // Since we can't alter the text cursor in the text area directly we need
    // to replace the cursor with ours
    QTextCursor &x = cursor;
    this->textArea->setTextCursor(x);

    return true;
}

void MainWindow::Cut()
{
    QTextCursor cursor = this->textArea->textCursor();
    int start = cursor.selectionStart();
    int stop = cursor.selectionEnd();

    sv->Cut(start, stop);
    this->textArea->setText(sv->GetText());
}

void MainWindow::Copy()
{
    QTextCursor cursor = this->textArea->textCursor();
    int start = cursor.selectionStart();
    int stop = cursor.selectionEnd();

    sv->Copy(start, stop);
    this->textArea->setText(sv->GetText());
}

void MainWindow::Paste()
{
    QTextCursor cursor = this->textArea->textCursor();
    int position = cursor.position();

    sv->Paste(position);
    this->textArea->setText(sv->GetText());
}

void MainWindow::Undo()
{
    sv->Undo();
    this->textArea->setText(sv->GetText());
}

void MainWindow::Redo()
{
    sv->Redo();
    this->textArea->setText(sv->GetText());
}

MainWindow::~MainWindow()
{
    delete ui;
}
