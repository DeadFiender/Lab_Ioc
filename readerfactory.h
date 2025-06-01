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
        }
        m_extensions.removeDuplicates();
    }

    std::shared_ptr<IDataReader> getReader(const QString& ext) const {
        return m_map.value(ext.toLower(), nullptr);
    }

    QStringList getSupportedExtensions() const {
        return m_extensions;
    }

private:
    QHash<QString, std::shared_ptr<IDataReader>> m_map;
    QStringList m_extensions;
};


#endif // READERFACTORY_H
