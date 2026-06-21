#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"

namespace sv::math_algs {

    class SieveOfEratosthenes : public sv::sorting::ISortAlgorithm {
    private:
        std::vector<int> m_data; 
        int m_limit = 100;
        int m_p = 2;
        int m_i = 4;
        int m_operations = 0;
        bool m_finished = false;

    public:
        void init(std::vector<int> data) override;
        bool step() override;
        
        const std::vector<int>& getData() const override;
        std::pair<int, int> getHighlightedIndices() const override;
        
        int getComparisonsCount() const override;
        int getSwapsCount() const override;
        std::string getName() const override;
        std::string getComplexityBest() const override;
        std::string getComplexityAverage() const override;
        std::string getComplexityWorst() const override;
        bool isFinished() const override;

        void setLimit(int limit);
        int getLimit() const;
    };

}