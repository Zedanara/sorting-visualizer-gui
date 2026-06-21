#pragma once

#include <vector>
#include <utility>

namespace sv::core {

    class Visualizer {
    public:
        // Rysuje tablicę jako pionowe słupki.
        // highlighted - indeksy elementów do podświetlenia (np. porównywane)
        static void drawBars(const std::vector<int>& data, std::pair<int, int> highlighted);
        // Rysuje tablicę jako siatkę kwadratów z liczbami (np. dla Sita Eratostenesa)
        static void drawGrid(const std::vector<int>& data, std::pair<int, int> highlighted);
    };

}