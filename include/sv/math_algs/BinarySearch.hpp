#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"

namespace sv::math_algs {

    class BinarySearch : public sv::sorting::ISortAlgorithm {
    private:
        std::vector<int> m_data;
        int m_low, m_high, m_mid;
        int m_target = 0;
        int m_comparisons = 0;
        bool m_finished = false;
        bool m_found = false;

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

        // Unikalne metody dla Binary Search
        void setTarget(int target);
        int getTarget() const;
        bool isFound() const;
    };

}