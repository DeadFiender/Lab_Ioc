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
    // Создание модели файловой системы и установка корневого пути (текущая директория)

    fileTree = new QTreeView(this);
    fileTree->setModel(fileModel);
    fileTree->setHeaderHidden(true);
    fileTree->setColumnWidth(0, 220);
    // Настройка виджета для отображения дерева файлов:
    // - Установка модели.
    // - Скрытие заголовка.
    // - Установка ширины первого столбца.

    // === Правый блок: элементы управления ===
    loadFolderButton = new QPushButton("Загрузить папку", this);
    chartSelector = new QComboBox(this);
    chartSelector->addItems({ "LineChart", "BarChart", "PieChart", "ScatterChart" });
    // Создание кнопки для выбора папки и выпадающего списка для выбора типа графика.

    grayscaleCheck = new QCheckBox("Чёрно-белый график", this);
    printButton = new QPushButton("Печать графика", this);
    statusLabel = new QLabel("Выберите папку и файл", this);
    // Создание чекбокса для режима ЧБ, кнопки печати и метки состояния.

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(loadFolderButton);
    rightLayout->addWidget(chartSelector);
    rightLayout->addWidget(grayscaleCheck);
    rightLayout->addWidget(printButton);
    rightLayout->addWidget(statusLabel);
    rightLayout->addStretch();
    // Создание вертикального макета для правой части интерфейса

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setLayout(rightLayout);
    // Создание виджета для правой части и установка макета.

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(fileTree);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(1, 1);
    // Создание разделителя для левой и правой частей интерфейса.

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
    resize(1000, 600);
    // Создание горизонтального макета для всего окна и установка его как основного макета.
    // Установка начального размера окна.

    // === Сигналы ===
    connect(loadFolderButton, &QPushButton::clicked, this, &MainWindow::onFolderSelect);
    // Подключение сигнала нажатия кнопки "Загрузить папку" к слоту `onFolderSelect`.
    connect(fileTree, &QTreeView::doubleClicked, this, &MainWindow::onFileDoubleClicked);
    // Подключение сигнала двойного клика по файлу в дереве к слоту `onFileDoubleClicked`.
    connect(chartSelector, &QComboBox::currentTextChanged, this, &MainWindow::onChartTypeChanged);
    // Подключение сигнала изменения выбранного типа графика к слоту `onChartTypeChanged`.
    connect(printButton, &QPushButton::clicked, this, &MainWindow::onPrintClicked);
    // Подключение сигнала нажатия кнопки "Печать графика" к слоту `onPrintClicked`.
    connect(grayscaleCheck, &QCheckBox::toggled, this, &MainWindow::onGrayscaleToggled);
    // Подключение сигнала переключения чекбокса к слоту `onGrayscaleToggled`.
}

MainWindow::~MainWindow() {
    if (chartView) delete chartView;// Удаление виджета графика при уничтожении окна.
}

void MainWindow::onFolderSelect() {
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите папку");
    if (!dir.isEmpty()) {
        fileTree->setRootIndex(fileModel->setRootPath(dir));
        statusLabel->setText("Папка загружена: " + dir);
        // Открытие диалога выбора папки и обновление дерева файлов.
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
    // Обработка двойного клика по файлу:
    // - Проверка расширения файла.
    // - Сохранение пути к файлу и обновление графика.
}

void MainWindow::onChartTypeChanged(const QString &chartType) {
    if (currentFilePath.isEmpty()) return;

    QString ext = QFileInfo(currentFilePath).suffix().toLower();
    auto reader = readerFactory->getReader(ext);
    if (!reader) {
        statusLabel->setText("Формат не поддерживается.");
        return;
    }
    // Получение reader данных для текущего файла.

    DataModel model = reader->read(currentFilePath);
    if (model.points.isEmpty()) {
        statusLabel->setText("Нет данных для построения.");
        return;
    }
    // Чтение данных из файла.

    auto chart = chartFactory->get(chartType.toLower().replace("chart", ""));
    if (!chart) {
        statusLabel->setText("График не найден.");
        return;
    }
    // Получение рендера графика.

    if (chartView) {
        layout()->removeWidget(chartView);
        delete chartView;
        chartView = nullptr;
    }
    // Удаление предыдущего графика, если он существует.

    chartView = chart->render(model, grayscaleCheck->isChecked());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 300);
    layout()->addWidget(chartView);
    statusLabel->setText("График построен.");
    // Отрисовка нового графика и добавление его в интерфейс.
}


void MainWindow::onPrintClicked() {
    if (!chartView) {
        statusLabel->setText("Нет графика для печати.");
        return;
    }
    // Проверка наличия графика.

    QString path = QFileDialog::getSaveFileName(this, "Сохранить PDF", "", "*.pdf");
    if (!path.endsWith(".pdf")) path += ".pdf";
    // Выбор пути для сохранения PDF.

    Printer p;
    p.printToPdf(chartView, path, grayscaleCheck->isChecked());
    statusLabel->setText("График сохранён.");
    // Экспорт графика в PDF.
}

void MainWindow::onGraphChanged() {
    statusLabel->setText("График обновлён.");
    // Обновление статусной метки при изменении графика.
}

void MainWindow::onGrayscaleToggled(bool checked) {
    if (!currentFilePath.isEmpty()) {
        onChartTypeChanged(chartSelector->currentText());
        // Перестроение графика при изменении режима ЧБ.
    }
}



