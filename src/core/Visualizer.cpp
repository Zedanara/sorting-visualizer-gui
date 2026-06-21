#include "sv/core/Visualizer.hpp"
#include "imgui.h"
#include <string>
#include <algorithm>

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

    void Visualizer::drawGrid(const std::vector<int>& data, std::pair<int, int> highlighted) {
        if (data.size() <= 2) return;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p_min = ImGui::GetCursorScreenPos();
        ImVec2 avail = ImGui::GetContentRegionAvail();

        int cols = 10; // 10 kolumn w siatce
        int elements = data.size() - 2; // Ignorujemy 0 i 1
        int rows = (elements + cols - 1) / cols;
        
        float cell_size = std::min(avail.x / cols, avail.y / rows) - 6.0f;
        if (cell_size < 20.0f) cell_size = 20.0f;

        for (size_t i = 2; i < data.size(); ++i) {
            int c = (i - 2) % cols;
            int r = (i - 2) / cols;

            ImVec2 p1 = ImVec2(p_min.x + c * (cell_size + 6), p_min.y + r * (cell_size + 6));
            ImVec2 p2 = ImVec2(p1.x + cell_size, p1.y + cell_size);

            ImU32 color = IM_COL32(38, 76, 153, 255); // Domyślny (niebieski)
            if (data[i] < 0) color = IM_COL32(60, 60, 65, 255); // Wykreślone (szary)
            
            if ((int)i == highlighted.first) color = IM_COL32(0, 255, 0, 255); // Aktualna l. pierwsza (zielony)
            else if ((int)i == highlighted.second) color = IM_COL32(255, 200, 0, 255); // Aktualna wielokrotność (żółty)

            draw_list->AddRectFilled(p1, p2, color, 4.0f);

            // Rysowanie liczby w środku kwadratu
            std::string text = std::to_string(std::abs(data[i]));
            ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
            ImVec2 text_pos = ImVec2(p1.x + (cell_size - text_size.x) * 0.5f, p1.y + (cell_size - text_size.y) * 0.5f);
            draw_list->AddText(text_pos, IM_COL32(255, 255, 255, 255), text.c_str());
        }

        ImGui::Dummy(ImVec2(avail.x, rows * (cell_size + 6))); 
    }

}