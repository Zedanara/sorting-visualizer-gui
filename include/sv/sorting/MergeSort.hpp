#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"
#include <vector>

namespace sv::sorting {

    class MergeSort : public ISortAlgorithm {
    private:
        // Struktura przechowująca pojedynczą "klatkę" animacji
        struct Frame {
            std::vector<int> data;
            std::pair<int, int> highlighted;
            int comps;
            int swaps;
        };

        std::vector<int> m_currentData;
        std::vector<Frame> m_frames;
        size_t m_currentFrame = 0;
        bool m_finished = false;

        // Metody pomocnicze do nagrywania rekurencji
        void recordFrame(int h1, int h2);
        void merge(std::vector<int>& arr, int left, int mid, int right, int& comps, int& swaps);
        void mergeSortRecursive(std::vector<int>& arr, int left, int right, int& comps, int& swaps);

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