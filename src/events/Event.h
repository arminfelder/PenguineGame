//
// Created by armin on 27.12.18.
//

#ifndef GAME_EVENT_H
#define GAME_EVENT_H

namespace Events {
    enum class EventTypes{
        Input,
        Collision,
        Health,
        None,
        EntityMoved

    };

    class Event {
    public:
        Event(Events::EventTypes pType);
        Events::EventTypes getType();
    private:
        Events::EventTypes type;
    };
}

#endif //GAME_EVENT_H