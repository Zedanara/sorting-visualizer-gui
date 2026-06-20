#include "sv/sorting/InsertionSort.hpp"
#include <algorithm>

namespace sv::sorting {

    void InsertionSort::init(std::vector<int> data) {
        m_data = std::move(data);
        m_i = 1;
        m_j = 1;
        m_comparisons = 0;
        m_swaps = 0;
        m_finished = (m_data.size() <= 1);
    }

    bool InsertionSort::step() {
        if (m_finished) return false;

        if (m_i < m_data.size()) {
            // Porównujemy element z jego poprzednikiem
            m_comparisons++;
            if (m_j > 0 && m_data[m_j - 1] > m_data[m_j]) {
                std::swap(m_data[m_j], m_data[m_j - 1]);
                m_swaps++;
                m_j--; // Cofamy się, dopóki element jest mniejszy
            } else {
                // Element jest na swoim miejscu, bierzemy następny z nieposortowanych
                m_i++;
                m_j = m_i;
            }
        } else {
            m_finished = true;
        }
        return !m_finished;
    }

    const std::vector<int>& InsertionSort::getData() const { return m_data; }
    
    std::pair<int, int> InsertionSort::getHighlightedIndices() const { 
        if (m_finished) return {-1, -1};
        // Podświetlamy aktualnie sprawdzany element i jego sąsiada
        return {m_j, m_j > 0 ? m_j - 1 : 0}; 
    }
    
    int InsertionSort::getComparisonsCount() const { return m_comparisons; }
    int InsertionSort::getSwapsCount() const { return m_swaps; }
    std::string InsertionSort::getName() const { return "Insertion Sort"; }
    std::string InsertionSort::getComplexityBest() const { return "O(n)"; }
    std::string InsertionSort::getComplexityAverage() const { return "O(n^2)"; }
    std::string InsertionSort::getComplexityWorst() const { return "O(n^2)"; }
    bool InsertionSort::isFinished() const { return m_finished; }
}