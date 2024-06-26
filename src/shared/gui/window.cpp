#include "window.hpp"

#include <utility>
#include "gui.hpp"

namespace openhack::gui {
    Window::Window(const std::string &title, std::function<void()> onDraw) {
        m_title = title;
        m_drawCallback = std::move(onDraw);
        m_position = ImVec2(0, 0);
        m_drawPosition = m_position;
        m_size = ImVec2(MIN_SIZE);
        m_isOpen = true;
    }

    void Window::draw() {
        if (!isOnScreen())
            return;

        ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
        auto scale = config::getGlobal<float>("UIScale");

        // Calculate distance to the bottom to make window fit the screen
        auto screenSize = ImGui::GetIO().DisplaySize;
        auto maxSizeH = MAX_SIZE.y * scale;
        auto bottomMargin = config::get<float>("menu.windowSnap");
        if (m_position.y + m_size.y > screenSize.y - bottomMargin - 1) // -1 to prevent flickering
            maxSizeH = screenSize.y - m_position.y - bottomMargin;

        ImGui::SetNextWindowSizeConstraints({MIN_SIZE.x * scale, MIN_SIZE.y * scale},
                                            {MAX_SIZE.x * scale, maxSizeH});

        ImGui::SetNextWindowCollapsed(!m_isOpen, ImGuiCond_Always);

        if (gui::beginWindow(m_title.c_str(), nullptr, flags)) {
            m_drawCallback();
        }

        // Allow moving the window
        if (ImGui::IsMouseDragging(0) && ImGui::IsWindowHovered()) {
            m_position = ImGui::GetWindowPos();

            m_drawPosition = m_position;

            config::setGlobal("draggingWindow", true);
        }

        m_size = ImGui::GetWindowSize();
        m_isOpen = !ImGui::IsWindowCollapsed();

        ImGui::SetWindowPos(m_drawPosition);

        gui::endWindow();
    }

    bool Window::isOpen() const { return m_isOpen; }

    void Window::setOpen(bool open) { m_isOpen = open; }

    bool Window::isOnScreen() const {
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        return m_position.x + m_size.x >= 0 &&
               m_position.y + m_size.y >= 0 &&
               m_position.x < screenSize.x &&
               m_position.y < screenSize.y;
    }

    const std::string &Window::getTitle() const { return m_title; }

    void Window::setTitle(const std::string &title) { m_title = title; }

    const ImVec2 &Window::getPosition() const { return m_position; }

    void Window::setPosition(const ImVec2 &position) { m_position = position; }

    const ImVec2 &Window::getDrawPosition() const { return m_drawPosition; }

    void Window::setDrawPosition(const ImVec2 &position) { m_drawPosition = position; }

    const ImVec2 &Window::getSize() const { return m_size; }

    void Window::setSize(const ImVec2 &size) { m_size = size; }

    animation::MoveAction *
    Window::createMoveAction(ImVec2 target, double duration, animation::EasingFunction easing, bool setRealPosition) {
        auto *action = animation::MoveAction::create(duration, &m_drawPosition, target, easing);
        if (setRealPosition)
            m_position = target;
        return action;
    }
}