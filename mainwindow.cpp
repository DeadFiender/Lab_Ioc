#include "mainwindow.h"
#include "ChartFactory.h"
#include "ReaderFactory.h"
#include "printer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>

MainWindow::MainWindow(std::shared_ptr<ChartFactory> chartFactory,
                       std::shared_ptr<ReaderFactory> readerFactory,
                       QWidget *parent)
    : QWidget(parent),
      chartFactory(std::move(chartFactory)),
      readerFactory(std::move(readerFactory))
{
    setWindowTitle("Печать графиков");

    // === Левый блок: дерево файлов ===
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::currentPath());

    fileTree = new QTreeView(this);
    fileTree->setModel(fileModel);
    fileTree->setHeaderHidden(true);
    fileTree->setColumnWidth(0, 220);

    // === Правый блок: элементы управления ===
    loadFolderButton = new QPushButton("Загрузить папку", this);
    chartSelector = new QComboBox(this);
    chartSelector->addItems({ "LineChart", "BarChart", "PieChart", "ScatterChart" });

    grayscaleCheck = new QCheckBox("Чёрно-белый график", this);
    printButton = new QPushButton("Печать графика", this);
    statusLabel = new QLabel("Выберите папку и файл", this);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(loadFolderButton);
    rightLayout->addWidget(chartSelector);
    rightLayout->addWidget(grayscaleCheck);
    rightLayout->addWidget(printButton);
    rightLayout->addWidget(statusLabel);
    rightLayout->addStretch();

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setLayout(rightLayout);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(fileTree);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(1, 1);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
    resize(1000, 600);

    // === Сигналы ===
    connect(loadFolderButton, &QPushButton::clicked, this, &MainWindow::onFolderSelect);
    connect(fileTree, &QTreeView::doubleClicked, this, &MainWindow::onFileDoubleClicked);
    connect(chartSelector, &QComboBox::currentTextChanged, this, &MainWindow::onChartTypeChanged);
    connect(printButton, &QPushButton::clicked, this, &MainWindow::onPrintClicked);
    connect(grayscaleCheck, &QCheckBox::toggled, this, &MainWindow::onGrayscaleToggled);
}

MainWindow::~MainWindow() {
    if (chartView) delete chartView;
}

void MainWindow::onFolderSelect() {
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите папку");
    if (!dir.isEmpty()) {
        fileTree->setRootIndex(fileModel->setRootPath(dir));
        statusLabel->setText("Папка загружена: " + dir);
    }
}

void MainWindow::onFileDoubleClicked(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    if (!filePath.endsWith(".sqlite") && !filePath.endsWith(".json")) {
        statusLabel->setText("Неподдерживаемый формат.");
        return;
    }
    currentFilePath = filePath;
    onChartTypeChanged(chartSelector->currentText());
}

void MainWindow::onChartTypeChanged(const QString &chartType) {
    if (currentFilePath.isEmpty()) return;

    QString ext = QFileInfo(currentFilePath).suffix().toLower();
    auto reader = readerFactory->getReader(ext);
    if (!reader) {
        statusLabel->setText("Формат не поддерживается.");
        return;
    }

    DataModel model = reader->read(currentFilePath);
    if (model.points.isEmpty()) {
        statusLabel->setText("Нет данных для построения.");
        return;
    }

    auto chart = chartFactory->get(chartType.toLower().replace("chart", ""));
    if (!chart) {
        statusLabel->setText("График не найден.");
        return;
    }

    if (chartView) {
        layout()->removeWidget(chartView);
        delete chartView;
        chartView = nullptr;
    }

    chartView = chart->render(model, grayscaleCheck->isChecked());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 300);
    layout()->addWidget(chartView);
    statusLabel->setText("График построен.");
}


void MainWindow::onPrintClicked() {
    if (!chartView) {
        statusLabel->setText("Нет графика для печати.");
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, "Сохранить PDF", "", "*.pdf");
    if (!path.endsWith(".pdf")) path += ".pdf";

    Printer p;
    p.printToPdf(chartView, path, grayscaleCheck->isChecked());
    statusLabel->setText("График сохранён.");
}

void MainWindow::onGraphChanged() {
    statusLabel->setText("График обновлён.");
}

void MainWindow::onGrayscaleToggled(bool checked) {
    if (!currentFilePath.isEmpty()) {
        onChartTypeChanged(chartSelector->currentText());
    }
}



