#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QtCharts/QChartView>
#include "observer.h"
#include "ChartFactory.h"
#include "ReaderFactory.h"

class MainWindow : public QWidget, public IObserver {
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<ChartFactory> chartFactory,
               std::shared_ptr<ReaderFactory> readerFactory,
               QWidget *parent = nullptr);
    ~MainWindow();

    void onGraphChanged() override;

private slots:
    void onGrayscaleToggled(bool checked);
    void onFolderSelect();
    void onFileDoubleClicked(const QModelIndex &index);
    void onChartTypeChanged(const QString &chartType);
    void onPrintClicked();

private:
    QPushButton *loadFolderButton;
    QTreeView *fileTree;
    QFileSystemModel *fileModel;
    QComboBox *chartSelector;
    QCheckBox *grayscaleCheck;
    QPushButton *printButton;
    QLabel *statusLabel;

    QtCharts::QChartView *chartView = nullptr;

    std::shared_ptr<ChartFactory> chartFactory;
    std::shared_ptr<ReaderFactory> readerFactory;

    QString currentFilePath;
};


#endif // MAINWINDOW_H
