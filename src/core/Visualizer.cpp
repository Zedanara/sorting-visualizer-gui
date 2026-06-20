#include "sv/core/Visualizer.hpp"
#include "imgui.h"

namespace sv::core {

    void Visualizer::drawBars(const std::vector<int>& data, std::pair<int, int> highlighted) {
        if (data.empty()) return;

        // Pobranie listy rysowania z Dear ImGui
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // Lewy górny róg obszaru roboczego
        ImVec2 canvas_size = ImGui::GetContentRegionAvail(); // Dostępna przestrzeń w oknie
        
        // Zabezpieczenie przed zbyt małym oknem
        if (canvas_size.x < 50.0f) canvas_size.x = 50.0f;
        if (canvas_size.y < 50.0f) canvas_size.y = 50.0f;

        // Znalezienie maksymalnej wartości do skalowania wysokości słupków
        float max_val = 0;
        for (int v : data) {
            if (v > max_val) max_val = static_cast<float>(v);
        }
        if (max_val == 0.0f) max_val = 1.0f; 

        // Obliczenie szerokości pojedynczego słupka
        float bar_width = canvas_size.x / data.size();

        for (size_t i = 0; i < data.size(); ++i) {
            float bar_height = (data[i] / max_val) * canvas_size.y;
            
            // Koordynaty prostokąta (słupka)
            ImVec2 p_min = ImVec2(canvas_p0.x + i * bar_width, canvas_p0.y + canvas_size.y - bar_height);
            ImVec2 p_max = ImVec2(canvas_p0.x + (i + 1) * bar_width - 1.0f, canvas_p0.y + canvas_size.y);
            
            // Domyślny kolor słupka (motyw niebieski z Theme.cpp)
            ImU32 color = IM_COL32(38, 76, 153, 255); 
            
            // Podświetlenie na żółto elementów aktualnie porównywanych/zamienianych
            if (static_cast<int>(i) == highlighted.first || static_cast<int>(i) == highlighted.second) {
                color = IM_COL32(255, 200, 0, 255);
            }

            // Rysowanie słupka
            draw_list->AddRectFilled(p_min, p_max, color);
        }

        // Przesunięcie kursora ImGui pod obszar rysowania
        ImGui::Dummy(canvas_size); 
    }

}