#include "sv/sorting/BubbleSort.hpp"
#include <algorithm>

namespace sv::sorting {

    void BubbleSort::init(std::vector<int> data) {
        m_data = std::move(data);
        m_i = 0;
        m_j = 0;
        m_comparisons = 0;
        m_swaps = 0;
        m_finished = (m_data.size() <= 1);
    }

    // Wykonuje tylko jeden krok pętli przy każdym wywołaniu
    bool BubbleSort::step() {
        if (m_finished) return false;

        if (m_i < m_data.size() - 1) {
            if (m_j < m_data.size() - m_i - 1) {
                m_comparisons++;
                if (m_data[m_j] > m_data[m_j + 1]) {
                    std::swap(m_data[m_j], m_data[m_j + 1]);
                    m_swaps++;
                }
                m_j++; // Przejście do następnego elementu
            } else {
                m_i++; // Koniec wewnętrznej pętli, nowa iteracja zewnętrzna
                m_j = 0;
            }
        } else {
            m_finished = true;
        }
        return !m_finished;
    }

    const std::vector<int>& BubbleSort::getData() const { return m_data; }
    
    std::pair<int, int> BubbleSort::getHighlightedIndices() const { 
        if (m_finished) return {-1, -1};
        return {m_j, m_j + 1}; 
    }
    
    int BubbleSort::getComparisonsCount() const { return m_comparisons; }
    int BubbleSort::getSwapsCount() const { return m_swaps; }
    std::string BubbleSort::getName() const { return "Bubble Sort"; }
    std::string BubbleSort::getComplexityBest() const { return "O(n)"; }
    std::string BubbleSort::getComplexityAverage() const { return "O(n^2)"; }
    std::string BubbleSort::getComplexityWorst() const { return "O(n^2)"; }
    bool BubbleSort::isFinished() const { return m_finished; }

}