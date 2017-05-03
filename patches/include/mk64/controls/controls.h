typedef struct {
    u16 buttons;
    s8 x, y;
} controllerState;

extern controllerState controller1_state; //XXX others?
extern controllerState *controllers[4]; //XXX are all 4 here?

extern controllerState player1_controllerState;
