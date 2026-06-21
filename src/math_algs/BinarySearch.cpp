#include "sv/math_algs/BinarySearch.hpp"
#include <algorithm>

namespace sv::math_algs {

    void BinarySearch::init(std::vector<int> data) {
        m_data = std::move(data);
        // Binary search działa TYLKO na posortowanych danych
        std::sort(m_data.begin(), m_data.end()); 
        
        m_low = 0;
        m_high = m_data.size() - 1;
        m_mid = -1;
        m_comparisons = 0;
        m_finished = m_data.empty();
        m_found = false;

        // Ustawiamy domyślny cel wyszukiwania (środkowy element), jeśli nie ustawiono innego
        if (!m_data.empty() && m_target == 0) {
            m_target = m_data[m_data.size() / 2];
        }
    }

    bool BinarySearch::step() {
        if (m_finished) return false;

        if (m_low <= m_high) {
            m_comparisons++;
            m_mid = m_low + (m_high - m_low) / 2;
            
            if (m_data[m_mid] == m_target) {
                m_found = true;
                m_finished = true;
            } else if (m_data[m_mid] < m_target) {
                m_low = m_mid + 1; // Szukamy w prawej połowie
            } else {
                m_high = m_mid - 1; // Szukamy w lewej połowie
            }
        } else {
            m_finished = true; // Nie znaleziono
        }
        
        return !m_finished;
    }

    void BinarySearch::setTarget(int target) { m_target = target; }
    int BinarySearch::getTarget() const { return m_target; }
    bool BinarySearch::isFound() const { return m_found; }

    const std::vector<int>& BinarySearch::getData() const { return m_data; }
    std::pair<int, int> BinarySearch::getHighlightedIndices() const { return m_finished && !m_found ? std::pair<int,int>{-1, -1} : std::pair<int,int>{m_mid, m_low}; }
    int BinarySearch::getComparisonsCount() const { return m_comparisons; }
    int BinarySearch::getSwapsCount() const { return 0; }
    std::string BinarySearch::getName() const { return "Binary Search"; }
    std::string BinarySearch::getComplexityBest() const { return "O(1)"; }
    std::string BinarySearch::getComplexityAverage() const { return "O(log n)"; }
    std::string BinarySearch::getComplexityWorst() const { return "O(log n)"; }
    bool BinarySearch::isFinished() const { return m_finished; }

}