#include "sv/sorting/CountingSort.hpp"
#include <algorithm>

namespace sv::sorting {

    void CountingSort::init(std::vector<int> data) {
        m_frames.clear();
        m_currentFrame = 0;
        m_finished = (data.size() <= 1);
        m_currentData = data;
        
        if (m_finished) return;

        int ops = 0;
        std::vector<int> temp = data;
        m_frames.push_back({temp, {-1, -1}, ops});

        // Szukanie wartości maksymalnej
        int max_val = temp[0];
        for (int i = 1; i < temp.size(); i++) {
            ops++;
            if (temp[i] > max_val) max_val = temp[i];
            m_frames.push_back({temp, {i, -1}, ops});
        }

        if (max_val > 1000) max_val = 1000; 

        std::vector<int> count(max_val + 1, 0);
        std::vector<int> output(temp.size());

        // Zliczanie wystąpień
        for (int i = 0; i < temp.size(); i++) {
            ops++;
            count[temp[i]]++;
            m_frames.push_back({temp, {i, -1}, ops});
        }

        // Sumy prefiksowe
        for (int i = 1; i <= max_val; i++) {
            count[i] += count[i - 1];
        }

        // NAPRAWIONY FRAGMENT: Tworzymy niezmienne źródło (source), z którego tylko czytamy
        std::vector<int> source = temp;

        // Budowanie tablicy wyjściowej
        for (int i = source.size() - 1; i >= 0; i--) {
            ops++;
            int val = source[i];
            int pos = count[val] - 1;
            
            output[pos] = val;
            count[val]--;
            
            // Do wizualizacji bezpiecznie modyfikujemy temp
            temp[pos] = val; 
            m_frames.push_back({temp, {pos, -1}, ops});
        }

        temp = output;
        m_frames.push_back({temp, {-1, -1}, ops});
    }

    bool CountingSort::step() {
        if (m_finished || m_frames.empty()) return false;
        if (m_currentFrame < m_frames.size() - 1) m_currentFrame++;
        else m_finished = true;
        return !m_finished;
    }

    const std::vector<int>& CountingSort::getData() const { return m_frames.empty() ? m_currentData : m_frames[m_currentFrame].data; }
    std::pair<int, int> CountingSort::getHighlightedIndices() const { return m_frames.empty() || m_finished ? std::pair<int,int>{-1, -1} : m_frames[m_currentFrame].highlighted; }
    int CountingSort::getComparisonsCount() const { return m_frames.empty() ? 0 : m_frames[m_currentFrame].ops; }
    int CountingSort::getSwapsCount() const { return 0; }
    std::string CountingSort::getName() const { return "Counting Sort"; }
    std::string CountingSort::getComplexityBest() const { return "O(n + k)"; }
    std::string CountingSort::getComplexityAverage() const { return "O(n + k)"; }
    std::string CountingSort::getComplexityWorst() const { return "O(n + k)"; }
    bool CountingSort::isFinished() const { return m_finished; }

}