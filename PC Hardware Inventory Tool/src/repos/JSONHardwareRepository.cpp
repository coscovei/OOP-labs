#include "JSONHardwareRepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <stdexcept>

JSONHardwareRepository::JSONHardwareRepository(const QString& jsonPath)
    : jsonPath_(jsonPath)
{
    loadFromFile();
}

JSONHardwareRepository::~JSONHardwareRepository()
{
    saveToFile();
}

void JSONHardwareRepository::loadFromFile()
{
    storage_.clear();
    nextId_ = 1;

    QFile file(jsonPath_);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // If missing, create an empty array
        QFile newFile(jsonPath_);
        if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            newFile.write("[]");
            newFile.close();
        }
        return;
    }

    QByteArray content = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(content, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        throw std::runtime_error(
            "Failed to parse JSON file: " + parseError.errorString().toStdString());
    }
    if (!doc.isArray()) {
        throw std::runtime_error("JSON root is not an array");
    }

    for (const auto& value : doc.array()) {
        if (!value.isObject()) continue;
        QJsonObject obj = value.toObject();

        int id = obj.value("id").toInt();
        QString category     = obj.value("category").toString();
        QString brand        = obj.value("brand").toString();
        QString model        = obj.value("model").toString();
        QString serialNumber = obj.value("serialNumber").toString();
        QString location     = obj.value("location").toString();
        int quantity         = obj.value("quantity").toInt();
        QString notes        = obj.value("notes").toString();

        HardwareItem item(id, category, brand, model,
                          serialNumber, location, quantity, notes);
        storage_.push_back(item);
        nextId_ = std::max(nextId_, id + 1);
    }
}

void JSONHardwareRepository::saveToFile() const
{
    QJsonArray arr;
    for (const auto& item : storage_) {
        QJsonObject obj;
        obj.insert("id", item.getId());
        obj.insert("category", item.getCategory());
        obj.insert("brand", item.getBrand());
        obj.insert("model", item.getModel());
        obj.insert("serialNumber", item.getSerialNumber());
        obj.insert("location", item.getLocation());
        obj.insert("quantity", item.getQuantity());
        obj.insert("notes", item.getNotes());
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile file(jsonPath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Cannot write JSON file: " + jsonPath_.toStdString());
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

void JSONHardwareRepository::add(const HardwareItem& item)
{
    HardwareItem copy = item;
    if (copy.getId() <= 0) {
        copy.setId(nextId_++);
    } else {
        for (const auto& existing : storage_) {
            if (existing.getId() == copy.getId()) {
                throw std::runtime_error("ID conflict while adding to JSON repository");
            }
        }
        nextId_ = std::max(nextId_, copy.getId() + 1);
    }
    storage_.push_back(copy);
    saveToFile();
}

void JSONHardwareRepository::remove(int id)
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [id](const HardwareItem& item) { return item.getId() == id; });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in JSON repository");
    }
    storage_.erase(it);
    saveToFile();
}

void JSONHardwareRepository::update(const HardwareItem& item)
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [&item](const HardwareItem& existing) {
                               return existing.getId() == item.getId();
                           });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in JSON repository");
    }
    *it = item;
    saveToFile();
}

HardwareItem JSONHardwareRepository::findById(int id) const
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [id](const HardwareItem& item) { return item.getId() == id; });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in JSON repository");
    }
    return *it;
}

std::vector<HardwareItem> JSONHardwareRepository::getAll() const
{
    return storage_;
}
