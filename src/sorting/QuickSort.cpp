#include "sv/sorting/QuickSort.hpp"
#include <algorithm>

namespace sv::sorting {

    void QuickSort::init(std::vector<int> data) {
        m_data = std::move(data);
        m_comparisons = 0;
        m_swaps = 0;
        m_finished = (m_data.size() <= 1);
        
        m_stack.clear();
        if (!m_finished) {
            m_stack.push_back({0, m_data.size() - 1});
            m_state = POP_STACK;
        }
    }

    bool QuickSort::step() {
        if (m_finished) return false;

        if (m_state == POP_STACK) {
            if (m_stack.empty()) {
                m_finished = true;
                return false;
            }
            // Pobieramy zakres do posortowania
            auto [low, high] = m_stack.back();
            m_stack.pop_back();
            
            m_low = low;
            m_high = high;
            
            if (m_low < m_high) {
                // Inicjalizacja zmiennych do partycjonowania
                m_pivotIdx = m_high; // Pivot zawsze na końcu dla prostoty
                m_pivot = m_data[m_pivotIdx];
                m_i = m_low - 1;
                m_j = m_low;
                m_state = PARTITION_LOOP;
            }
            return true;
        } 
        
        if (m_state == PARTITION_LOOP) {
            if (m_j <= m_high - 1) {
                m_comparisons++;
                if (m_data[m_j] < m_pivot) {
                    m_i++;
                    std::swap(m_data[m_i], m_data[m_j]);
                    m_swaps++;
                }
                m_j++;
            } else {
                // Koniec partycjonowania, umieszczamy pivot na właściwym miejscu
                std::swap(m_data[m_i + 1], m_data[m_high]);
                m_swaps++;
                int p = m_i + 1;
                
                // Dodajemy nowe zakresy na stos
                m_stack.push_back({m_low, p - 1});
                m_stack.push_back({p + 1, m_high});
                
                m_state = POP_STACK;
            }
        }
        
        return !m_finished;
    }

    const std::vector<int>& QuickSort::getData() const { return m_data; }
    
    std::pair<int, int> QuickSort::getHighlightedIndices() const { 
        if (m_finished) return {-1, -1};
        if (m_state == PARTITION_LOOP) return {m_j, m_pivotIdx};
        return {-1, -1};
    }
    
    int QuickSort::getComparisonsCount() const { return m_comparisons; }
    int QuickSort::getSwapsCount() const { return m_swaps; }
    std::string QuickSort::getName() const { return "Quick Sort"; }
    std::string QuickSort::getComplexityBest() const { return "O(n log n)"; }
    std::string QuickSort::getComplexityAverage() const { return "O(n log n)"; }
    std::string QuickSort::getComplexityWorst() const { return "O(n^2)"; }
    bool QuickSort::isFinished() const { return m_finished; }

}