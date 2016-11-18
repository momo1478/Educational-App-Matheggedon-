#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_signUpButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_loginButton_clicked();

    void on_playToolButton_clicked();

    void on_logOutPushButton_clicked();

    void on_statsPushButton_clicked();

    void on_leaderboardPushButton_clicked();

    void on_stats_backToolButton_clicked();

    void on_leaderboard_backToolButton_clicked();

    void on_startScreenPushButton_clicked();

    void on_restartPushButton_clicked();

    void on_endGamePushButton_clicked();

    void pageChanged(int);

private:
    Ui::MainWindow *ui;

    void setupConnectAndActions();
};

#endif // MAINWINDOW_H