#ifndef ACTIVATION_H
#define ACTIVATION_H

class Activation {
public:
    Activation() {}
    virtual ~Activation() {}
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual bool isactivated() const = 0;
};

#endif
