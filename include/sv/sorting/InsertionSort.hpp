#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"

namespace sv::sorting {

    class InsertionSort : public ISortAlgorithm {
    private:
        std::vector<int> m_data;
        int m_i = 1;
        int m_j = 1;
        int m_comparisons = 0;
        int m_swaps = 0;
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
    };

}