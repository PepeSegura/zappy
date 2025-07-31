# zappy
Network-based multiplayer strategy game server written in C++17.

## Game Overview
Zappy is a resource management and team-based strategy game where:

- **Players** belong to different teams and compete on a 2D grid-based map
- **Objective** appears to be leveling up through "incantations" (rituals) that require specific combinations of resources and multiple players
- **Survival** element where players must regularly consume food (every 126 ticks) or die

## Key Game Mechanics
- **Movement**: Players can move forward, turn left/right (`Avance`, `Droite`, `Gauche`)
- **Resource Management**: Collect/drop items (`Prend`, `Pose`) including food and 6 types of minerals (linemate, deraumere, sibur, mendiane, phiras, thystame)
- **Vision**: Players can see their surroundings (`Voir`)
- **Communication**: Broadcast messages and expel other players
- **Leveling**: Progress through incantation rituals requiring specific resource combinations and player counts
- **Team Mechanics**: Players can fork (reproduce) and check team connection numbers

## Technical Architecture
- **Server**: TCP-based server handling multiple concurrent clients
- **Tick-based**: Game runs on a timing system with configurable tick rates
- **Map System**: 2D grid where each tile can contain resources and players
- **Command Queue**: Asynchronous command processing with time-based action execution

This is an implementation of the classic École 42 "Zappy" project - a complex multiplayer game often used to teach network programming, AI client development, and real-time game server architecture.
