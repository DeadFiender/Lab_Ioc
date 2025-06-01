#ifndef PRINTER_H
#define PRINTER_H

#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtCharts/QChartView>

class Printer {
public:
    void printToPdf(QtCharts::QChartView* chartView, const QString& path, bool gray = false) {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(path);
        printer.setColorMode(gray ? QPrinter::GrayScale : QPrinter::Color);
        QPainter painter(&printer);
        chartView->render(&painter);
        painter.end();
    }
};

#endif // PRINTER_H
