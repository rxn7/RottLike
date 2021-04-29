#include "Engine/StateMachine/State.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Client.hpp"
#include "./LocalPlayer.hpp"
#include "./FpsTimer.hpp"

class GameState : public RottEngine::State{
public:
    GameState();
    ~GameState();

    void processEvent(const sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    LocalPlayer* mp_player;
    FpsTimer m_fps_timer;
    RottEngine::Client mp_client;
    sf::Clock m_tick_rate_clock;
};