#include <stdio.h>
enum ev_t { EV_TXCOMPLETE, EV_TXSTART};

struct EventHandlers {
    void (*ev_txcomplete)(ev_t);
    void (*ev_txstart)(ev_t);
};


class TestEvents {
    public:
        TestEvents(){
            handlers.ev_txcomplete = 0;
            handlers.ev_txstart = 0;
        };
        bool setHandler(ev_t event, void (*handler)(ev_t)) {
            switch(event) {
                case EV_TXCOMPLETE:
                    handlers.ev_txcomplete = handler;
                    break;
                case EV_TXSTART:
                    handlers.ev_txstart = handler;
                    break;
                default:
                    return false;
            }
            return true;
        };

        bool handle(ev_t event) {
            switch(event) {
                case EV_TXCOMPLETE:
                    if(!handlers.ev_txcomplete)
                        return false;
                    handlers.ev_txcomplete(event);
                    break;
                case EV_TXSTART:
                    if(!handlers.ev_txstart)
                        return false;
                    handlers.ev_txstart(event);
                    break;
                default:
                    return false;
            }
            return true;
        };
    private:
        EventHandlers handlers;
};

void myfunc(ev_t event) {
    printf("myfunc called\n");
}

void myfunc2(ev_t event) {
    printf("myfunc2 called\n");
}

int main() {
    TestEvents t;
    t.setHandler(EV_TXCOMPLETE, myfunc);
    t.setHandler(EV_TXSTART, myfunc2);
    t.handle(EV_TXSTART);
    t.handle(EV_TXCOMPLETE);
}
