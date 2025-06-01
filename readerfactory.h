#ifndef READERFACTORY_H
#define READERFACTORY_H

#include <QString>
#include <QVector>
#include <memory>
#include <QHash>
#include <QStringList>
#include <memory>
#include "IDataReader.h"

class ReaderFactory {
public:
    ReaderFactory(const QVector<std::shared_ptr<IDataReader>>& readers) {
        for (const auto& r : readers) {
            m_map[r->get()] = r;
            m_extensions.append(r->get());
            // Регистрация читателей в карте и списке поддерживаемых расширений.
        }
        m_extensions.removeDuplicates();
        // Удаление дубликатов из списка расширений
    }

    std::shared_ptr<IDataReader> getReader(const QString& ext) const {
        return m_map.value(ext.toLower(), nullptr);
        // Получение читателя по расширению файла.
    }

    QStringList getSupportedExtensions() const {
        return m_extensions;
        // Возвращение списка поддерживаемых расширений.
    }

private:
    QHash<QString, std::shared_ptr<IDataReader>> m_map;
    // Карта для хранения читателей по расширениям.
    QStringList m_extensions;
    // Список поддерживаемых расширений
};


#endif // READERFACTORY_H
