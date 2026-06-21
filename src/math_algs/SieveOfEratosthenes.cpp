#include "sv/math_algs/SieveOfEratosthenes.hpp"
#include <cmath>

namespace sv::math_algs {

    void SieveOfEratosthenes::init(std::vector<int> /*data*/) {
        // Ignorujemy dane wejściowe, generujemy własną tablicę od 0 do limitu
        m_data.resize(m_limit + 1);
        for(int i = 0; i <= m_limit; i++) {
            m_data[i] = i;
        }
        m_data[0] = -1; // 0 i 1 nie są pierwsze (oznaczamy ujemnymi)
        m_data[1] = -1;

        m_p = 2;
        m_i = m_p * m_p;
        m_operations = 0;
        m_finished = false;
    }

    bool SieveOfEratosthenes::step() {
        if (m_finished) return false;
        
        if (m_p * m_p <= m_limit) {
            if (m_data[m_p] > 0) { // Jeśli m_p jest liczbą pierwszą
                if (m_i <= m_limit) {
                    m_operations++;
                    m_data[m_i] = -std::abs(m_data[m_i]); // Wykreślamy (zmieniamy na ujemną)
                    m_i += m_p;
                    return true;
                } else {
                    m_p++;
                    m_i = m_p * m_p;
                    return true;
                }
            } else {
                m_p++;
                m_i = m_p * m_p;
                return true;
            }
        }

        m_finished = true;
        return false;
    }

    void SieveOfEratosthenes::setLimit(int limit) { m_limit = limit;}
    int SieveOfEratosthenes::getLimit() const { return m_limit;}

    const std::vector<int>& SieveOfEratosthenes::getData() const { return m_data;}
    std::pair<int, int> SieveOfEratosthenes::getHighlightedIndices() const { return m_finished ? std::pair<int, int>{-1, -1} : std::pair<int, int>{m_p, m_i <= m_limit ? m_i : -1}; }
    int SieveOfEratosthenes::getComparisonsCount() const { return m_operations; }
    int SieveOfEratosthenes::getSwapsCount() const { return 0; }
    std::string SieveOfEratosthenes::getName() const { return "Sieve of Eratosthenes"; }
    std::string SieveOfEratosthenes::getComplexityBest() const { return "O(n log log n)"; }
    std::string SieveOfEratosthenes::getComplexityAverage() const { return "O(n log log n)"; }
    std::string SieveOfEratosthenes::getComplexityWorst() const { return "O(n log log n)"; }
    bool SieveOfEratosthenes::isFinished() const { return m_finished; }
    
}