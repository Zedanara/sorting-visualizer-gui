#pragma once
#include <string>
#include <vector>

namespace sv::database {

    struct HistoryEntry {
        int index;
        std::string algorithmName;
        std::string timestamp;
        int dataSize;

        std::string toLine() const;
        static HistoryEntry fromLine(const std::string& line);
    };

    class HistoryDatabase {
    private:
        std::string m_filename;
        std::vector<HistoryEntry> m_entries;
        const size_t MAX_ENTRIES = 15;

        void saveToFile() const;

    public:
        HistoryDatabase(const std::string& filename);

        bool load(); // Zwraca true, jeśli plik istnieje i nie jest pusty
        bool addEntry(const std::string& algorithmName, int dataSize);
        void removeLast();
        void removeByIndex(int index);
        void clearAll();

        const std::vector<HistoryEntry>& getEntries() const;
        bool hasDuplicate(const std::string& algorithmName) const;
        bool isFull() const;
    };

}