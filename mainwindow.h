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
    // Конструктор принимает фабрики графиков и читателей, а также родительский виджет.
    ~MainWindow();

    void onGraphChanged() override;
    // Реализация метода из интерфейса `IObserver`.
    // Вызывается при изменении графика.

private slots:
    void onGrayscaleToggled(bool checked);// Слот для обработки переключения режима ЧБ.
    void onFolderSelect();// Слот для выбора папки с файлами.
    void onFileDoubleClicked(const QModelIndex &index);// Слот для обработки двойного клика по файлу в дереве файлов.
    void onChartTypeChanged(const QString &chartType);// Слот для обработки изменения типа графика.
    void onPrintClicked();// Слот для печати графика в PDF.

private:
    QPushButton *loadFolderButton;
    QTreeView *fileTree;
    QFileSystemModel *fileModel;
    QComboBox *chartSelector;
    QCheckBox *grayscaleCheck;
    QPushButton *printButton;
    QLabel *statusLabel;

    QtCharts::QChartView *chartView = nullptr;// Виджет для отображения графика.

    std::shared_ptr<ChartFactory> chartFactory;
    std::shared_ptr<ReaderFactory> readerFactory;
// Фабрики для управления графиками и читателями данных.
    QString currentFilePath;// Текущий выбранный файл.
};


#endif // MAINWINDOW_H
