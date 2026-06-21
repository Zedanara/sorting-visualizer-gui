#define _CRT_SECURE_NO_WARNINGS
#include "sv/database/HistoryDatabase.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace sv::database {

    std::string HistoryEntry::toLine() const {
        return std::to_string(index) + ";" + algorithmName + ";" + timestamp + ";" + std::to_string(dataSize);
    }

    HistoryEntry HistoryEntry::fromLine(const std::string& line) {
        HistoryEntry entry;
        std::stringstream ss(line);
        std::string item;
        
        if (std::getline(ss, item, ';')) entry.index = std::stoi(item);
        if (std::getline(ss, item, ';')) entry.algorithmName = item;
        if (std::getline(ss, item, ';')) entry.timestamp = item;
        if (std::getline(ss, item, ';')) entry.dataSize = std::stoi(item);
        
        return entry;
    }

    HistoryDatabase::HistoryDatabase(const std::string& filename) : m_filename(filename) {}

    bool HistoryDatabase::load() {
        m_entries.clear();
        std::ifstream file(m_filename);
        if (!file.is_open()) return false;

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                m_entries.push_back(HistoryEntry::fromLine(line));
            }
        }
        return !m_entries.empty();
    }

    void HistoryDatabase::saveToFile() const {
        std::ofstream file(m_filename, std::ios::trunc); // trunc nadpisuje plik od nowa
        if (!file.is_open()) return;

        for (const auto& entry : m_entries) {
            file << entry.toLine() << "\n";
        }
    }

    bool HistoryDatabase::addEntry(const std::string& algorithmName, int dataSize) {
        if (hasDuplicate(algorithmName)) return false;
        
        if (m_entries.size() >= MAX_ENTRIES) {
            // Usuwamy najstarszy wpis, jeśli przekroczono limit
            m_entries.erase(m_entries.begin()); 
        }

        // Generowanie aktualnego czasu (timestamp)
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");

        // Obliczanie nowego indeksu
        int newIndex = m_entries.empty() ? 1 : m_entries.back().index + 1;

        m_entries.push_back({newIndex, algorithmName, ss.str(), dataSize});
        saveToFile();
        return true;
    }

    void HistoryDatabase::removeLast() {
        if (!m_entries.empty()) {
            m_entries.pop_back();
            saveToFile();
        }
    }

    void HistoryDatabase::removeByIndex(int index) {
        for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
            if (it->index == index) {
                m_entries.erase(it);
                saveToFile();
                break;
            }
        }
    }

    void HistoryDatabase::clearAll() {
        m_entries.clear();
        saveToFile();
    }

    const std::vector<HistoryEntry>& HistoryDatabase::getEntries() const {
        return m_entries;
    }

    bool HistoryDatabase::hasDuplicate(const std::string& algorithmName) const {
        for (const auto& entry : m_entries) {
            if (entry.algorithmName == algorithmName) return true;
        }
        return false;
    }

    bool HistoryDatabase::isFull() const {
        return m_entries.size() >= MAX_ENTRIES;
    }

}